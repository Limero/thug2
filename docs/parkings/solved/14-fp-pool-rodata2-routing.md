# Issue 14 — FP constant pool lands in `.rodata` instead of `.rodata2`

**Status: STALE — RESOLVED (verified 2026-08-29): object-level fixup
`tools/fix_fp_pool.py`, no source rewrite needed. All 14 blocked functions
promoted byte-exact (800B7280, 80114E4C, 80130CB8, 801594D4, 8015958C,
80159618, 80186F60, 8018CD64, 80195E0C, 80195F98, 80196740, 801A0FF0,
801A17C8, 80215B28, 802327E0) — DOL byte-identical. Do not re-open; kept
for the routing analysis and the superseded union-form workaround.**

## The fix: tools/fix_fp_pool.py (object surgery)

ngccc's pool constant is unavoidable for a bare cast, but the game's DOL
already holds that exact double in its `.rodata2` region with an `lbl_`
symbol — and each function's ORIGINAL bytes point at one specific address
there. `tools/fix_fp_pool.py` (hooked into the `ngccc` ninja rule after
configure, and into `promote_wip.py`'s `obj_has_payload`) reads the original
lis+lfd pair from the DOL at each reloc site, retargets the object's
R_PPC_ADDR16_HA/LO relocs from `.rodata` to the `lbl_` at that exact address,
and zeroes the `.rodata` section. The object links text-only and the DOL stays
byte-identical. Key detail: the reloc offset points at the 2-byte immediate
field, so the instruction site is `(roff - 2) & ~3`; the `lbl_` MUST be the
one at want's address (the first value match, e.g. lbl_8028FB80, gives the
right VALUE but the wrong bytes).

Prior partial workaround (kept for reference): the union-form source rewrite
dodges the pool but changes codegen (frame/scheduling), so it is NOT
byte-exact — the object fixup supersedes it. `80114E4C` was a separate
`.bss` case: m2c emitted `static s32 sp8` for a stack temp; the local form
fixes it.

## Source workaround (M8.xx — dodges the pool entirely)

The blocker only exists when you let **ngccc synthesize** the cast: a bare
`(f32)(s32_expr)` makes the compiler build its own `0x43300000`/`0x80000000`
pool constants into module `.rodata`. The GAME never did that — it built the
conversion by hand, referencing its own `.rodata2` doubles. Reproduce that
literally and no new constants are emitted at all:

```c
union { u32 w[2]; f64 d; } cvt;
cvt.w[1] = (u32)iv ^ 0x80000000;
cvt.w[0] = 0x43300000;
fv = (f32)(cvt.d - *(f64 *)&lbl_80299940); /* real .rodata2 double (2^52 magic) */
```

- `lbl_80299940` / `lbl_80299948` are genuine game symbols
  (`symbols.txt`: `.rodata2 ... data:double`) — reference them, don't invent
  literals.
- Working draft with two live sites: `src/wip/fn_800D03DC.c` (verified `fn_800D03DC.o` → no `.rodata`, with WANT's load-immediate-shifted of the 0x4330 high half plus floating load reproduced at 0x800D0518).
- **Verified 2026-08-29:** `test_plain.c` `(f32)(f64)iv` → `.rodata 8B 4330000080000000` with `R_PPC_ADDR16_HA/LO` on **all five** ProDG builds and all `-G*`/`-msdata` combos; `test_workaround.c` / `fn_800D03DC.o` / `test_802327E0_workaround.o` → **no `.rodata`** (headers `.text` only on 3.8+/3.9, size-0 on 3.5/3.7) with relocs to `lbl_80299940`. DOL sec7 `0x8028E040+0x1B20` has 0 magics, sec8 `0x8028FB60+0x22840` has 279×`4330_80000000` +128×`4330_00000000`. Always rewrite to the union form BEFORE parking — tool is `SN_NGC_PATH=... wibo ngccc -O2 -G0 -mcpu=750` + `readelf -S`.
- The dead end in "What was tried" below still applies to any source shape
  that makes GCC synthesize the constant.

## The problem

The int→double cast idiom emits a **2^52 magic constant**
(`0x4330000080000000`) into the floating-point constant pool. In the game's
DOL this constant lives in **section 8 (`.rodata2`, VA 0x8028FB60+)**; in
every object compiled with ngccc it lands in **section 7 (`.rodata`)** —
shifting the DOL by 8 bytes and breaking byte-identity.

Exemplar fn_802327E0: masked-EXACT (all instructions match once relocations
are masked), but the `(f32)(f64)(s32)` int→double cast makes ngccc emit the
2^52 magic into `.rodata` (DOL section 7) while the original has it in
section 8 at 0x802B08D8.

## What was tried (all failed — investigated conclusively at M4.62)

1. `-G4/-G8/-G16` and `-msdata=eabi/sysv/default` on **all five** ProDG
   builds (3.5/3.5b140/3.7/3.8.1/3.9.3): pool always lands in `.rodata`.
2. dtk split claims:
   - `.rodata start:0x802B08D8` → rejected ("Section .rodata
     (0x8028E040..0x8028FB60) does not contain range").
   - `.rodata2` claim does not match the object's actual `.rodata` section
     name.
3. `extern lbl_802B08D8` arithmetic: cannot reproduce the single-`fsub`
   int→f64 form — the compiler always synthesizes its own pool constant
   (union/pointer tricks yield +0xC..+0x20 offsets instead).
4. The dtk ldscript GROUP routes all module `.rodata` into section 7; dtk
   cannot place module `.rodata` into section 8's VA range.

## Why it's parked

- The routing is controlled by the **linker script / dtk section routing**,
  not by C source, compiler flags, or split claims.
- It blocks **every int→double cast in the game** — dozens of copies of
  `0x4330000080000000` sit in section 8, so this is high-value to solve.

## Research directions for an external AI

1. **DOL section 8 is `.rodata2`** — find how the original linker script
   routed FP-pool constants there (GameCube SDK linkers commonly place
   `__float_const`/`__fptype` pools or `.sdata2`/`.rodata2` by symbol name).
   If dtk can be told to emit module constants into a `.rodata2`-named
   section (via `-section` directives or a per-object `.ld` fragment), the
   whole class un-parks.
2. Investigate dtk-template's `config/<version>/ldscript` and `splits.txt`
   support for a second read-only section: the DOL header has 18 sections;
   section 8 (0x8028FB60+) is the FP pool. Adding a `.rodata2` split claim
   whose *object section name* matches (renaming the object's `.rodata` to
   `.rodata2` via `objcopy --rename-section`) may work.
3. Check whether `ngccc` has a flag to name its FP pool section (some GCC
   ports use `-ffunction-sections`-adjacent `.rodata.cst8`); renaming the
   emitted section to `.rodata2` before linking may route it correctly.

## Where to look

- History: `AGENTS.md` §4n ("The FP-pool `.rodata2` dead end (802327E0 — do
  NOT re-open)") — note: the draft was later deleted when the range was
  reverted to asm coverage at M4.64 (commit da1375fd); the *issue* remains
  open for the whole int→double class.
- DOL sections: `readelf -S orig/G2TE52/sys/main.dol` (section 7 `.rodata`
  0x8028E040..0x8028FB60, section 8 `.rodata2` 0x8028FB60+).
- Constants: dozens of `0x4330000080000000` in section 8.

## confirmation (2026-08-23): applies to CALL-RESULT conversions too

fn_80143258 (parked 81.4%) proved the blocker is not limited to literal /
variable casts: ngccc's own `(f32)(f64)(s32-call())` expander reproduces
WANT's per-site interleave byte-exactly — the sequence xors the high half of the incoming integer, stores the low word, zeroes a register, copies the value across, stores the high word, loads the double and applies the float subtract plus round — at every one of its 18 sites, but then synthesizes the 2-word
0x43300000/0x80000000 pool constant into module `.rodata`, shifting the
DOL (same routing dead end as above). Hand reconstructions that avoid the
pool keep xoris-in-r3 but schedule stw-hi before the next call's arg setup.
Verified across all five ProDG versions. Conclusion: until section routing
exists, EVERY int→float-fixup site whose WANT shows this interleave is
blocked, including call-result conversions — do not re-derive per-function.

## caveat (2026-08-24, fn_80196ACC): the workaround can cost a register

The §6j-1 manual conversion dance is not always free. On fn_80196ACC, plain
`(f32)(f64)(s32)` casts reproduced want's SINGLE shared conversion-temp slot
and its exact 0x70 frame — but synthesized a private `.rodata` bias double
(unpromotable even when masked-EXACT). The promotable manual dance
(referencing real rodata2 doubles lbl_802AA610/620/628) forces a second
named temp → +8 frame and a different FPR map that no longer matches.
**Before choosing a route on any int→float site, diff BOTH: sometimes want's
schedule only falls out of the compiler-synthesized form, and then the site
is blocked on routing (this issue), not on source shape.**

## round update (2026-08-25) — masked-EXACT .text reached on the
exemplar; new cast-expander finding

**fn_802327E0 (the original exemplar) now matches .text 152/152 masked**
(up from the 97% stale draft). The u8-load width fix plus full re-derivation
got every instruction to match — but via SYNTHESIZED casts, so the private
8-byte pool (bias double vs game's lbl_802B08D8) still blocks promotion.

NEW empirical rule discovered on this function (**cast-expander dead-copy
trio**): with ≥2 synthesized casts in the body, ngccc ALSO emits want's trio
of dead copies `[mr r8,r10][mr r7,r10][mr r5,r10]`; a single synthesized cast
does NOT spawn them. The promotable manual §6j-1 dance (real rodata2
doubles, empty module .rodata) eliminates the pool but ALSO loses the trio;
asm-mr wedges recover the copy ORDER but not their register homes.

Decision procedure for int→float sites updated:
1. Count want's dead-copy trio words. If present, the site needs ≥2
   synthesized casts to reproduce them → text-match possible, promotion
   blocked on routing (this issue).
2. If absent, the manual dance is both text-correct AND promotable.
3. asm-mr wedges are a partial repair only (order yes, homes no) — a future
   lever would need a way to pin the expander's scratch homes.

Retry hint: if dtk/ldscript ever gains per-object `.rodata` routing (or an
approved ASM_FUNC-style carve-out with honest accounting), fn_802327E0 flips
to matched immediately — its decode notes live in src/wip/fn_802327E0.c.

## Verification 2026-08-29

**Route B — `objcopy --rename-section` does route but duplicates:** `powerpc-eabi-objcopy --rename-section .rodata=.rodata2` on `minimal_plain.o` (`.rodata 8B` → `.rodata2 8B`) → `GROUP .rodata2` in `config/G2TE52/ldscript.tpl:23` → `sec8` (`readelf -S` shows `.rodata2 8B`). Alone it just moves the duplicate (`0x22840→0x22848`, still shifts DOL by 8B). Byte-identical only if paired with a **per-function `.rodata2` split claim** (e.g. `fn_802327E0: .rodata2 0x802B08D8..0x802B08E0`) carving `auto_03_8028FB60_rodata2.o` (0x22840) into two pieces around that hole so total stays 0x22840 — feasible (`ldscript.tpl` already `GROUP:{.rodata .rodata2 ...}`, `splits.txt` declares both) but per-function cost for ~400 sites.

**Promotion rule refined (2026-08-29):** manual union **is** promotable (empty `.rodata`) when WANT lacks the dead-copy trio `[mr r8,r10][mr r7,r10][mr r5,r10]`; when WANT has it (≥2 synthesized casts, `fn_802327E0` `0x802327FC..08` trio) the union loses the trio (149/152 text-match, 97.9%) — `asm mr` wedges recover order not homes. Count the trio first: present → text-match possible, promotion blocked on routing; absent → union is both text-correct and promotable.

**Growing EXACT-in-wip pool awaiting routing (do NOT bulk-promote):** `fn_80159BEC`, `fn_80159C68`, `fn_80186F60`, `fn_801A0FF0`, `fn_801A17C8` (all masked-sweep EXACT, DOL would shift) — newly promoted `fn_800D03DC` is the verified promotable member of this class.

## fn_800ABB34 (2026-09-28): an extern-symbol FP constant and a same-valued LITERAL are different pool nodes

92.5% → **EXACT** (promotable, Route A pool retargeted by `fix_fp_pool.py` as
usual), and the whole 7-word residual came from how the two float constants
were spelled — not from store order, not from flags.

Writing them as `extern f32 lbl_80298560/64;` (the *correct*, symbol-referenced
spelling, and the one this doc's whole Route-A story is built around) made
ngccc hoist `lfs f10` (the divisor) + `fdivs f12` three-to-four slots too early
and sink `stfs f0,0xc(r31)` by the same amount. Writing the **value-identical C
literals** `100.0f` / `1.0f` instead produces different RTL pool nodes, which
flips the list scheduler's intra-block priority and lands everything exactly.

Two things worth keeping:

* **A 90-99% float-tail park should try the literal spelling BEFORE grinding
  store order or flag combinations.** `tools/flag_sweep.py` (21 singles + 3
  pairs) found *no* improvement on this function — the store-order
  permutations (w-first, w-last, x/w/y/z, x/y/w/z, z/y/x/w, rotate-right) and a
  `"+f"` asm barrier all sat at 92.5%.
* This is the same class as recipe 45/53/285's "bare literal vs `lbl` symbol"
  split, but for **constants**, and it is value-preserving — so unlike the
  doc-14 pool problem it costs nothing at promote time (the private 16-byte
  `.rodata` is retargeted to `lbl_80298558/60/64` by `tools/fix_fp_pool.py`
  and `.rodata` ends at size 0). The manual §6j-1 union dance against the real
  rodata2 doubles scored 33.3% here (it adds a saved register and moves the
  whole float block), so it was not needed.

## Stale entry removed 2026-09-28: `fn_80159BEC` was NEVER EXACT-in-wip

This doc's "EXACT-in-wip pool awaiting routing" list included `fn_80159BEC`.
**It was not byte-exact — it sat at 59.4%.** Its actual blocker was the
float-if-conversion wall (AGENTS §6ag-4), and it is now byte-exact:

```c
fv  = (f32)fn_801A6E64(…);
res = 1; __asm__("" : "+r"(res));     /* zero-code barrier blocks setcc */
if (fv > sp8) { return res; }          /* the true arm must return res, not 1 */
return 0;
```

Three requirements, all load-bearing:

1. the compared operand is **staged in a named `f32`**;
2. the accumulator is a named local with a **zero-code `"+r"` barrier** between
   the assignment and the compare — without it GCC if-converts the compare to
   `setcc` and homes the result in a callee-saved register (frame 0x18 → 0x28,
   `li` hoisted above the `lis`);
3. the true arm returns **`res`**, not the literal `1`, so the `li r3,1`
   slot-fill survives.

Dead ends: all `setcc` spellings (59.4%); a `register s32 res __asm__("r3")`
pin (58.1% — the pin evicts the `xoris` from r3 and swaps the 0x4330-vs-anchor
register pair); the barrier on the float operand or on the pre-cast int (59.4%
/ 46.9%); `if/else res=1/res=0` (24.2%).

**Its promote path is the normal one**: the pool double is synthesised into
`.rodata` but retail's 0x80298170 sits inside `lbl_80298164`, so
`tools/fix_fp_pool.py` retargets it and zeroes the object's `.rodata`.

**Generalisation for this doc:** an EXACT-in-wip listing here does **not**
imply the `.text` is exact — the float-if-conversion and pool problems are
independent, and a stale entry will send a future agent to grind doc-14
routing for a function that was never close. Re-score before believing any
entry on that list.

## L4 is not a doc-14 problem (2026-09-28): 7/7 on float-block residuals

L4 (spelling a value-identical **C literal** instead of `extern f32/f64 lbl_X`)
went 7-for-7 across two rounds, and none of them needed any of the routing
machinery in this doc — the private pool is retargeted by the already-wired
`tools/fix_fp_pool.py` and `.rodata` ends at size 0, so these are
promote-clean. Members: fn_800ABB34, fn_800D94E4, fn_80058778, fn_80108E94,
fn_80143B7C, fn_800AF844, fn_80173C5C.

Three refinements the later members produced:

* **Apply L4 PER CONSTANT, not per function.** On fn_800AF844 only the constant
  that was *not* in a callee-saved FPR wanted the literal; the f31 one had to
  stay an extern, because its named local was load-bearing for the register
  allocation.
* **A park note that already exhausted naming, pointer-form and flag levers is
  the STRONGEST L4 signature** — a literal is still untried. fn_800AF844's note
  had explicitly ruled out every spelling *except* the extern.
* L4 interacts with structure: on fn_80173C5C the extern spelling capped the
  function at 85–87.5% *even after* the structural fix, so the two are not
  independent and both may be needed.

## Two new EXACT-in-wip members with private pools (2026-09-28)

Both are **masked-EXACT on `.text` but carry a synthesized pool constant**, so
they are *not* promote-clean as they stand — `tools/fix_fp_pool.py` (this doc's
object-surgery fix, or the §"source workaround" above) is still required. Both
drafts state this in their own headers, which is the correct state; this entry
exists so the two are not mistaken for promotable matches.

| fn | pool | what it is | note |
|---|---|---|---|
| `fn_80034608` | `.rodata` 4 B = `0.0f` | the L4 fix (§below) needs a *value-identical literal* so that the 0.0f folds into an **existing** page anchor with a displacement instead of getting its own `lis` | value-identical to retail `lbl_80291C84`; §doc 73 for why L4 is load-bearing here |
| `fn_801931EC` | `.rodata` 8 B = `0x4330000080000000` | classic int→f64 conversion pool, from a `(f32)(f64)(s32)` cast | the §"source workaround" (manual `union` + real `.rodata2` double) applies if a promote is ever wanted |

A cheap pre-promote check, since `test_wip_drafts.py` does **not** flag a
non-empty `.rodata`:

```sh
build/binutils/powerpc-eabi-readelf -W -S /tmp/leaf/fn_<ADDR>.o | grep rodata
```

## `fn_80182C8C` (2026-09-28): EXACT-in-wip, needs this doc at promote

388B, flagless, 97 instructions, zero emitted asm, `test_wip_drafts` reports
EXACT — but the object carries an **8-byte `.rodata` = `0x4330000080000000`**,
the synthesized int→f64 magic double. At link it would land in section 7
instead of the game's `.rodata2` `lbl_802A93F8` and shift the DOL, so this
needs `tools/fix_fp_pool.py` (or the §"source workaround") like every other
member of this table.

The plain `(f32)(f64)(s32)` casts **must stay** here: they emit want's
`lis r6,0x4330` / `xoris` / `fsub` / `frsp` dance *and* the `mr r10,r11` +
`mr r7,r11` dead-copy pair (§6as-1's cast-expander fingerprint). The §"source
workaround" manual union **fails to compile** on this function — three
conversions share one union slot in an f32-param function — so do not spend a
round attempting it; `fix_fp_pool.py` is the only route.

**Cheap pre-promote check** (the sweep does not flag a non-empty `.rodata`):

```sh
build/binutils/powerpc-eabi-readelf -W -S /tmp/leaf/fn_<ADDR>.o | grep rodata
```
