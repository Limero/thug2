# Issue 01 — FPR frame layout quirk (frame 8 bytes smaller)

**Status: FRAME SOLVED (M4.92) — `volatile double _dummy;` workaround reproduces the game's exact frame.** The remaining
match-blockers for the exemplars are *separate* issues: the xoris int→float
conversion idiom and FP-constant pool routing (issue 14). Pure-FPR functions
that do not convert ints to doubles may now be matchable outright.

**Affected:** every function that saves FPRs (prologue contains `stfd`) —
**782 of 8,729 wip drafts (425 with 16-aligned frames, 357 with 8-aligned)**,
e.g. fn_80003594, fn_800035FC.

## The problem (as originally diagnosed)

Functions that save floating-point registers come out **8 bytes smaller** from
every available ngccc build than they are in the game binary, even though the
instruction stream *between* prologue and epilogue is otherwise identical.

Game binary (`main.dol`): the function reserves a 0x20-byte frame and saves float register f31 to frame offset 0x18, so the double slot is 16-aligned near the top of the frame.

Compiled with ngccc (all ProDG versions) WITHOUT the workaround: the function reserves only a 0x18-byte frame and saves f31 to frame offset 0x10, sitting 8 bytes lower than the game layout.

Empirical rule (verified on both exemplars):
- **want frame = ngccc-native frame + 8** whenever the function has a stack
  double slot / saves FPRs.
- The 16-aligned vs 8-aligned split (425 vs 357 in the draft population) is
  **pure arithmetic, not a per-function compiler decision**: native frames
  that are 8-aligned get +8 → 16-aligned (e.g. 24→32), native frames that are
  already 16-aligned get +8 → 24 (8-aligned). The game's compiler consistently
  allocates 8 bytes MORE headroom than ngccc for these frames.

## THE FIX (verified byte-for-byte)

Add a **`volatile double` local** as the function's first local:

```c
float fn_800035FC(float arg)
{
    volatile double _dummy;   // <-- forces the game's frame layout
    ...
}
```

With this one line, ngccc 3.7 emits the **exact game prologue** for both
variants:

- fn_80003594 (16-aligned half): `stwu r1,-0x20; stfd f31,0x18(r1); stw r0,0x24(r1)` ✓
- fn_800035FC (8-aligned half):  `stwu r1,-0x18; stfd f31,0x10(r1); stw r0,0x1c(r1)` ✓

### Mechanism (what was actually tested)

- `volatile double _dummy;` → **works** (forces a live stack double slot).
- `__attribute__((aligned(16))) double` **alone** → does nothing (optimized
  away, no frame effect).
- The `volatile` is what matters: it forces the double to stay on the stack,
  which pushes the frame up to satisfy double alignment — landing exactly on
  the game's `+8` layout. The game's 8-byte "dead zone" between locals and the
  FPR save area is reproduced because the dummy occupies that space without
  moving any real local (locals anchor to r1+8, FPR saves anchor to the frame
  top — the gap absorbs the extra 8 bytes).
- The fix generalizes to **both halves** of the 16/8 split (verified on one
  function from each class).

## What still blocks the exemplars (separate issues)

fn_80003594 (masked-diff count: 25 insns → 8 masked diffs, all downstream of):

1. **xoris int→float idiom** — want converts an `s32` to `float` via the
   unsigned magic-subtract trick (`lis r11; lfd magic; fsubs f0,f0,f1`), ngccc
   3.7 always emits the direct signed conversion. No C shape (including
   `(float)(unsigned int)x`, separate magic vars, etc.) reproduces `xoris`.
2. **FP-pool routing (issue 14)** — want loads its magic from
   `lbl_8028FB80` (a `.rodata2` constant); the standalone compile synthesizes
   its own pool constant at `0(r11)`. In the real build this becomes a
   .rodata-vs-.rodata2 routing question.

fn_800035FC: prologue/epilogue byte-identical; body is 200B vs want 208B
(one polynomial-association shape difference + constant relocations).

## M5.0a — "global -mps-float instead of the dummy" DISPROVEN (tested)

With ProDG 3.9.3's `-mps-float` forcing 16-byte frames for every
FPR-saving function, one might hope the dummy becomes unnecessary (and the
flag can go global). **It cannot — the 16/8 split is orthogonal to PS
usage.** Whole-DOL scan (293 game functions whose prologue is
`stwu; ...; stfd at frame-8`):

- 160 have **16-aligned** frames (+8 quirk): only **63** contain PS ops
  (97 are plain scalar FPR functions — the dummy is their only fix).
- 133 have **8-aligned** (native) frames: **59 of them contain PS ops**.

So global `-mps-float` would break all 133 native-framed FPR functions
(including 59 PS functions whose game frames are correctly native), and it
would only auto-fix 63 of the 160 quirk functions. Even *per-file*
`-mps-float` is wrong: PS functions straddle both frame classes (63 vs 59),
proving the game was not compiled with `-mps-float` per-file either. The
game's actual rule is "+8 when the source has a stack double" — which is
exactly what the `volatile double` dummy reproduces and what `-mps-float`
over-applies. Verified side evidence: adding `-mps-float` to `cflags_game`
changed 14 matched functions (native-frame FPR functions overshooting by
+8) and the DOL no longer matched; reverted. **Conclusion: the dummy fix
stays; `-mps-float` remains per-object only, for PS functions.**

## What was tried before the fix (historical, all failed on the frame)

- All five ProDG builds (3.5, 3.5b140, 3.7, 3.8.1, 3.9.3), C and C++ mode.
- All `-m` CPU/ABI flags, all `-malign-*`/alignment flags, `-G0..-G16`,
  `-msdata=eabi/sysv/default`.
- `-fno-omit-frame-pointer`: produces the game's frame sizes but forces
  `mr r31,r1` memory-spilling → wrong codegen elsewhere.
- Global-alignment flags can't be used anyway: they would pad GPR-only frames,
  which already match.

## Verified byte-identical (context)

- Leaf functions (no saved registers) — e.g. the RNG cluster.
- GPR-only functions (stmw/stw r30/r31, no stfd): both compilers agree on
  `frame = 8 + 4·nGPR + locals + 4`.
- No-FPR functions with stack doubles (frame 16, slot at 8).

## How to use this in the matching pipeline

For ANY wip draft whose want starts `stwu …; …; stfd …`:
1. Add `volatile double _dummy;` as the first local (only if the body doesn't
   already produce a stack double — if the want has the 16-aligned variant and
   the C already has a `double`, try `volatile` on that double instead).
2. Recompile / re-diff. The frame diff should vanish.
3. If the body was already correct, the function becomes EXACT and can be
   promoted; if not, the remaining diffs are the body, not the frame.

Expected population: ~782 drafts (of 8,729) — the single largest parked class.

## Research directions for an external AI (if the mechanism ever needs a compiler-level fix)

1. In GCC 2.95.x `rs6000.c`, the frame-layout path `rs6000_compute_frame_info`:
   find where the `+8` headroom for FPR frames is decided. The game's compiler
   (an SN Systems ProDG build, likely between 3.5 and 3.7, late 2002–early
   2003) allocates 8 bytes more than ngccc 3.7 for any frame with a stack
   double. The user hypothesis that it is a 16-byte-alignment patch triggered
   by "any FPR saved" is **partially correct**: the +8 exists for all FPR
   frames, and 16-alignment is just where +8 lands arithmetically — so the
   patch is better described as "always add a double-alignment slot's worth of
   headroom when doubles can appear".
   > **Day-0 A/B caveat (2026-08, cross-clone):** the "+8" frame difference is
   > the one class where a distinct game build is genuinely implicated — all
   > five installed ProDG builds (3.5–3.9.3) emit the smaller frame, and
   > Sims2DECOMP confirms the four point-versions are codegen-identical
   > (609 fns x 4, zero flips). That is exactly why the `volatile double`
   > dummy fix (a SOURCE-level +8) is the right solution and version swaps
   > would not work. Do not re-attribute this class to a point version.
2. Compare against Super Mario Sunshine / Wind Waker decomp `compilers/`
   directories (development timelines align with SN-TDEV builds).
3. This is now a *nice-to-have*: the volatile-double workaround makes the
   compiler-level hunt unnecessary for matching purposes.

## M5.0b — full-FPR-pool sweep with auto-dummy: no new EXACTs (bodies too far off)

`tools/test_wip_drafts.py` now auto-injects the dummy at test time for any
FPR want that lacks one (dual-test as-is + with-dummy, keep best;
`want_fpr_frame()` classifies the want from the DOL prologue). A sweep of
the standard-prologue FPR draft pool (170 pad8 + 144 native, i.e. every
non-promoted draft whose want saves FPRs with a standard prologue) found
**no new EXACTs** — 169/170 pad8 and 143/144 native are DIFF. The single NEAR, fn_8011C03C (85.2%),
is **not matchable with 3.9.3**: its last 3 words (`or. r0,r3,r3; li r3,0;
blt` + `mr r3,r0` vs the game's `or. r3,r3,r3; bge`) are a compiler-build
scheduling difference reproduced at every `-O` level and with
`-fno-schedule-insns*`/`-O1`. **Conclusion: the dummy is necessary but not
sufficient** — the FPR pool's blocker is the m2c body quality, not the
frame. Re-run the auto-dummy sweep only after the m2c drafts for FPR
functions are improved.

## 2026-09-13 — `want_fpr_frame()` FIXED: 8-aligned want frames are AMBIGUOUS

The auto-injector's classifier now is:

- `frame % 16 == 8` (8-aligned want) → **`ambig8`** — try BOTH as-is and
  with the dummy, keep the better verdict.
- `frame % 16 == 0` and `stfd == frame-8` → **`pad8`** — the +8 quirk;
  inject.
- otherwise (no `stfd` in the prologue window, or a non-`stwu` prologue) →
  `None`, tested as-is only.

**Why 8-aligned is ambiguous.** The +8 rule says want = native + 8, so an
8-aligned want (e.g. `0x18`) is either (a) a **quirk** on a native-16
function (`0x10` + 8 → `0x18`) or (b) a genuinely native 8-aligned function
whose frame lands there on its own (a source that already has its own stack
double, a PS function, etc.). The DOL alone cannot distinguish them, so the
harness must try both ways and keep the higher score — a dummy that
overshoots a native frame loses the dual test.

**The bug that was actually fixed.** The old classifier required
`stfd == frame-8` and otherwise returned `None`, so **multi-double prologues
— whose first `stfd` sits below frame-8 — were never dummy-tested at all**.
Example: `fn_800036C8` (`stwu -0x68`; four `stfd`s, first at `0x48`) returned
`None` and is an 8-aligned want. The `stfd` scan now covers the whole 64-byte
prologue window (16 insns), not just the first 8. Non-promoted population
after the fix: **137 `pad8` + 318 `ambig8`** (was 137 `pad8` + 112 `native`,
i.e. ~206 drafts that had never been dummy-tested).

**Validation (byte-level).** `src/fn_8011A7FC.c` (140B, promoted EXACT
2026-09-13; want `stwu -0x18` + `stfd f31,0x10(r1)`, no stack double in the
source, so want's `0x18` IS the +8 quirk) re-tested with its
`volatile double _dummy;` line stripped:

- as-is → 82.9% NEAR (frame 8 short)
- with the auto-injected dummy → **100% EXACT**

So the case the old tooling made you fix by hand is now caught automatically.
`tools/score_addrs.py` inherits the fix (it calls the same classifier).

**Tie rule.** The dummy only wins when STRICTLY better (`p1 > p0`). A genuine
frame change always moves the `stwu` immediate and every stack offset, so an
equal score means the dummy changed nothing (`-mps-float` already forced the
frame, the draft already has its own stack double, etc.) and the as-is variant
is the honest winner. This removes false `[dummy]` tags — `fn_800FDE38` was
being tagged `[dummy]` on a 51.5%/51.5% tie.

**Sweep result (2026-09-13).** All 318 non-promoted `ambig8` drafts re-run
with the fixed classifier: **0 EXACT** (292 DIFF, 24 NEAR, 2 compile FAIL).
So the frame fix is necessary but not sufficient in this pool either — its
blocker is m2c body quality (matches the M5.0b conclusion for `pad8`). The
dual test *is* doing real work, though: `fn_8021546C` (`ambig8`, frame `0x28`)
moves 91.5% → **93.9%** with the dummy, and the three drafts where the dummy
hurt (55.9%→4.2%, 66.1%→8.9%, 62.5%→5.6%) correctly keep their as-is score.

**Rule of thumb (still useful when reading raw diffs):** for any FPR-saving
draft whose compiled frame is exactly 8 bytes smaller than want AND `stfd`
sits at frame-8 in both, the dummy is required. `ambig8` drafts now get that
verified automatically; a draft must still *carry* the dummy itself to be
promoted (the test-time injection is not written back into the draft).
`fn_8011A7FC`'s winning body is the reference: FP-param reuse
(`farg0 = farg0 * c / d;`) + explicit dummy + callee protos.

## Addendum 2026-10-02 (w75/0x80044960) — the hole can be at the TOP of the
## locals, so the first-local dummy is the wrong fix

The `volatile double _dummy;`-as-first-local rule above reproduces a frame that
is `native + 8` **when the extra 8 bytes land at the bottom of the local area**
(the save area just moves up; every `addi/lwz/stw ...,0xNN(r1)` offset is
unchanged). It is *wrong* for the other shape, which also occurs:

`fn_80044960` (380 B) wants `stwu r1,-0xa8; stfd f31,0xa0; stmw r24,0x80;
stw r0,0xac` with locals at `+0x08` (0x60-byte buffer), `+0x68`, `+0x6C`,
`+0x70` — i.e. ngccc's native offsets are *already right* and only the **8
bytes at `+0x74`** (above the last local, below the save area) are missing.
Injecting the dummy as the first local moves the buffer to `+0x10` and every
scalar with it (verified: the harness's auto-injection cannot win, so the row
stays DIFF), because ngccc allocates an extra local **ahead of** the 4-byte
scalars: with `char sp8[0x60]; s32 sp68; f32 sp6C; s32 sp70; volatile double
pad;` the double lands at `+0x68` and pushes all three scalars up 8.

**Rule:** if `want_offset(first local) == got_offset(first local)` and the
frame is 8 short, the hole is at the TOP of the local area — do **not** add a
dummy. Instead declare the locals as ONE object of the size the want implies
(`typedef struct { char word[0x60]; char *cursor; f32 width; s32 height;
char pad[8]; } Loc;`). A single local is allocated as a unit, so the scalars
stay at `+0x68/+0x6C/+0x70` and the unused `pad` grows the frame to `0xA8`.
Verified byte-exact (no `[dummy]` tag) on 0x80044960. Same trick fixes any
"8 bytes short at the top of the frame" want; check
`addi/stfd/stmw` offsets before reaching for the dummy.

**Bonus finding from the same function (add-operand order):** GCC canonicalises
`ptr + int` so the pointer lands in input 1 of the emitted `add`, and the
destination follows input 1. A want reading `add rX, rInt, rPtr` (the
`+8` mirror of the usual `add rX, rPtr, rInt`) is only reachable by making the
expression a plain *integer* plus — `(s32)ptr + int` (or viewing the array base
as `s32 *` and indexing it). Swapping the two C operands alone does nothing:
GCC canonicalises both spellings to pointer-first.

**Extension (0x80042924, 436B, 2.1% -> 36.7%): the "ONE object of the size the
want implies" lever also grows the frame when the object is passed BY ADDRESS to
a call, and it beats the `+8` dummy for gaps larger than 8.** That want's frame
is `0x68` = outgoing-arg area (the two out-params of `fn_800586CC` at `8(r1)` /
`0xc(r1)`) + `0x20` of unused frame + `4*nGPR` + `8*nFPR`, i.e. a **0x20** hole
between the arg area and the first `stmw` — four times the `+8` the dummy buys,
and the dummy is actively wrong here (it moves the outgoing args to
`0x10/0x14`). Declaring the pair as one struct instead of two scalars
(`typedef struct { f32 width; f32 height; char unused[0x20]; } Metrics;`,
passed as `&out.width, &out.height`) lands the object at `0x08..0x30`, keeps
`addi r5, r1, 8` / `addi r6, r1, 0xc` exactly, and reproduces
`stwu -0x68 / stmw r26,0x30 / stfd f28,0x48 / stw r0,0x6c` verbatim. Confirms
the layout order this doc keeps implying: **declared locals always land BELOW the
outgoing-arg area**, so a `volatile` pad can size the frame but always drags the
outgoing args up with it (0x28/0x2c); only a *struct big enough to swallow the
arg area itself* raises the frame without moving the arg setup.

**Also worth repeating here: the m2c `// FLAG: -Os` header on FPR drafts is
poison — delete it.** `tools/fill_wip_drafts.py` guesses a size-optimisation
flag, and at `-Os` ngccc re-materialises every float through the double
conversion idiom (`lis 0x4330` + `xoris` + `lfd` + `fsub` + `frsp`), which is the
single biggest score loss on this family: 2.1% as-is vs 23.9% with the default
`-O2 -G0 -mcpu=750 -fno-common`. Keep a `// FLAG:` line in the draft but write
`none` in it, so `gen_leaves.draft_flags` (token filter `^-[A-Za-z]…`) adds
nothing.

## Where to look in the repo

- Exemplar drafts: `src/wip/fn_80003594.c`, `src/wip/fn_800035FC.c`,
  `src/wip/fn_80042924.c` (0x20 hole filled by one 0x28 local object)
- Verification scripts (historical, in `/tmp`): `/tmp/test_fpr_dummy*.py`,
  `/tmp/test_conv.py`, `/tmp/test_exact.py`, `/tmp/scan_fpr_frames2.py`
- Counting tooling: `tools/find_int_fns.py`, `tools/classify_fns.py`
- History: `docs/gamecube-decomp-plan.md` §5.3, `AGENTS.md` §4c
