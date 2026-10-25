# Issue 30 — Empty-doloop self-targeting `bdnz .` window artifact

**Status: SOLVED 2026-08-24 — inline-asm window with the
SN-assembler `bdnz $` self-target encoding. Exemplar fn_800FE094 went
36–58% → EXACT (promotable in `src/wip/`).**

## Symptom (historical)

Want contains a **self-targeting countdown loop with a non-empty window**: a count of 4 is loaded and moved to the count register, scheduler-sunk call-argument setup instructions sit inside the window, and the decrement-and-branch carries a zero displacement (raw word 0x42000000).

Every plain-C loop form (`for`/`while`/do-while/countdown, all
canonicalizations, all five ProDG versions, all schedule flags,
register pins, memory-clobber bodies) compiles to a **forward-displaced**
`bdnz` because SN cc1's scheduler sinks subsequent setup work into the
loop-body window and re-points the branch past it. Named/numeric
inline-asm labels (`1: bdnz 1b`, `g6s: bdnz g6s`) get their label
separated from the branch by the same scheduler.

## The solution (found on fn_8016C348's prologue)

Emit the ENTIRE window as one `volatile` inline-asm block and terminate it
with **`bdnz $`** — `$` is the SN assembler's "current address" operand and
encodes displacement 0. Two traps:

- `.` does NOT work: the SN assembler encodes `bdnz .` as +8.
- numeric backward labels (`1: bdnz 1b`) mis-resolve forward in this position.

Register plumbing: declare each register the window touches as a **local
register variable pinned to its want home**, use them as asm outputs so GCC
knows they were written:

```c
void fn_800FE094(void *arg0) {
    volatile __ps_t dst[8];              /* real array = frame anchor */
    register char   *a0   __asm__("r10");
    register __ps_t *src  __asm__("r11");
    register void   *dst4 __asm__("r4"); /* call-arg slot pin */
    register __ps_t *p    __asm__("r9");

    __asm__ volatile("li 0, 4\n\tmr %0, %4\n\tmtctr 0\n\taddi %1, 1, 8\n\t"
                     "addi %2, %0, 0x20\n\tmr %3, %1\n\tbdnz $"
                     : "=r"(a0), "=r"(p), "=r"(src), "=r"(dst4)
                     : "r"(arg0));

    p[0] = src[0];                       /* copies ride the asm-born ptrs */
    /* ... p[1..7] ... */
    dst[6] = *(__ps_t *)((char *)a0 + 0x10);  /* through the REAL array -> */
    dst[7] = *(__ps_t *)((char *)a0 + 0x18);  /* r1-relative psq_st encodings */
    fn_800073AC(a0 + 0xA8, dst4, 0x80808080u, 1);
}
```

Companion rules that made fn_800FE094 byte-exact (100.0% masked, `-mps-float`):

1. **Frame anchor**: keep a real local array (here `volatile __ps_t dst[8]`)
   so the frame size and r1-relative store encodings survive; an asm-only
   pointer birth collapses the frame to 8 bytes.
2. **Call-arg slot pin**: a value born inside the window into an ARGUMENT
   register (`mr r4,p`) must be declared as a register var pinned to that
   arg reg (`register void *dst4 __asm__("r4")`) and passed to the call —
   GCC then elides the identity copy at the call site instead of emitting a
   second `mr`.
3. **Encoding-sensitive stores go through the real array**: stores whose
   want form is frame-relative (`psq_st fX,N(r1)`) must be written through
   the declared array, not the asm-born pointer (which emits rN-relative).
4. r4/r9/r10/r11 are caller-saved → no save/restore spillover from the pins.

## Members

| fn | state |
|---|---|
| fn_800FE094 | **EXACT in wip ** — promotable |
| fn_8016C348 | prologue (incl. window) byte-exact via this recipe; body still parks on PS FPR rotation/interleave schedule (see its PARKED note) |
| fn_8015DD90 | 4 windows + ~300 insns of unrolled matrix fmadds; apply the recipe per-window, but expect independent body walls |
| fn_8017C8F4 | two windows (@0x8017C97C/@0x8017CC00) + `-mps-float` body; parked pre-solution at 2.5% — retry with this recipe first (its draft header has the updated note) |
| fn_801BB4A0 | **delay window verbatim AGAIN ** — second independent reuse; `__ps_t` pair copyback tail around it went EXACT (-mps-float) |
| fn_801AA2D4 | **window REPRODUCED VERBATIM ** — `li/lis/mtctr/lfs-f1-arg/addi×3/bdnz $` inline-asm block byte-exact on the first independent reuse of this recipe; remaining park is an unrelated allocator wall (entry param staged through r31 vs want arg0@r30/m1@r31). Recipe transfers cleanly to new sites |

Detector unchanged: grep wants for `mtctr` within 4 insns of a
displacement-0 `bdnz` (raw word `4200FFFF` style / capstone `bdnz <self>`).

## independent reuse (2026-08-24, fn_801E0974)

Fourth independent reproduction: both windows of fn_801E0974 emitted
verbatim (`li 0,4 / mtctr 0 / [body] / bnz $` split across two/three
volatile asm statements with `"r0","ctr"` clobbers). Confirms the recipe
transfers to PS-heavy allocator-stressed functions; that fn parks on
allocator/span grounds only, not the window. Note also: its sibling
fn_8015DD90 (park, FOUR self-targeting windows) still lists
"retry pending" above — the m2c statics-DCE cleanup there is already done,
making it the cheapest remaining candidate for this recipe.

## Promotion trap (found on fn_8014E440)

`bdnz $` inside an inline-asm string that does NOT terminate with the bdnz
(as in the fn_800FE094 recipe where `bdnz $` ends the block) compiles but
emits a **relocation against symbol `$`** — mwldeppc.exe then fails the
final link with `undefined: '$'`. gen_leaves' relocation masks hide this in
standalone tests, so it only surfaces at promote time. Promotion-safe form:

```c
".long 0x42000000"   /* bdnz 0 = self-target branch, verbatim word */
```

(fn_800FE094's promoted source already uses this; fn_8014E440's three bdnz
windows needed the same swap — DOL byte-identical after the fix.)

## Addendum (2026-09-03, batches 69/69b) — recipe correction + plain-C alternative

The `bdnz $` form documented above is **stale relative to the committed
exemplar**: `src/fn_800FE094.c` actually terminates its window with the raw
word **`.long 0x42000000`** (data-emitted bdnz, displacement 0 — no assembler
symbol, links clean). The textual `bdnz $` form goes through the assembler as
a symbol reference and **breaks the final link with `undefined: '$'`** —
observed on three independent promotion batches (fn_801B4404, fn_801B5A54,
and the 27 wip drafts still carrying it). `promote_wip.py` now screens for
`$` in asm strings and refuses such drafts upfront.

**Preferred alternative (proven on fn_801B4404 + fn_801B27F8, both
promoted DOL-identical): drop the instruction asm entirely.** The
empty-countdown window is plain C:

```c
p8  = (char *)sp8;          /* pointer inits as ordinary statements */
p48 = (char *)&tmp;
for (i4 = 4; i4 != 0; i4--)
    __asm__ volatile("");   /* unremovable body */
```

ngccc lowers the constant-count loop to `li/mtctr/bdnz` itself. When the
window interleaves real schedule work (loads/mults the scheduler must place),
the raw-word `.long 0x42000000` form remains the escape hatch — but try
plain C first; fn_801B5A54 shows the C conversion needs full re-derivation
when the window carries real dataflow.
