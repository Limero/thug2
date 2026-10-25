// REBUILT 2026-10-12: hand rebuild from want disasm, 41.6% (was raw
// m2c husk at 1.1%, 812B vs 360B — bloat from double-promoted float temps).
// Now size-near-exact (got 356B vs want 360B, -4B = the one missing `mr`),
// block1 (0x800D9960-0x800D99E0) byte-clean except index-reg rotation,
// semantics verified insn-by-insn against want. STILL PARKED — see
// REMAINING (the block2 `mr r10,r9` + off2-into-r9 allocator wall).
// family=m2c range=0x800D9960-0x800D9AC8 size=360B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT THIS FUNCTION IS (decoded from want, K = lbl_80299C2C = 0.0f):
//   off = arg1*4; v = *(arg0+0x180+off); ret = 0
//   if (v != 0): { nv = v*scale + p170; p170 = nv; lim = p160;
//                  if (|nv| > |lim| && ((nv > 0) flipped != (lim > 0))) p170 = lim }
//     where scale = *(arg0+0x1F8), p170/p160 = (arg0+0x170/0x160+off)
//   off2 = arg1*4; v2 = *(arg0+0x190+off2)
//   if (v2 != 0): { t = v2*scale;
//                   if (|t| > |p170-lim|): { p170 = lim; p190 = 0;
//                                            return (p160 == 0) }
//                   p170 -= t }
//   f1 = p170*scale
//   if ((arg0->unk0x20 & (0x20 << arg1)) == 0):
//     { sum = p150+f1; p150 = sum;
//       if ((p140 > p150) != (p140 > sum)): { ret = 1; f1 -= sum-p140 } }
//   fn_800D77FC(f1); return ret
// Frame 0x10 (r31+LR only, NO FPR saves — matchable class).
//
// PROBE-VERIFIED ProDG/3.9.3 scc map (LSB numbering; see /tmp probes, since
// cleaned — redo: compile `s32 p(f32 a){return a OP Kglob;}` + disassemble):
//   fcmpu cr7 + mfcr + rlwinm(0x1f) = EQ extract; (0x1d) = LT; (0x1e) = GT;
//   cr6-field GT = rlwinm(0x1a). `!=`-as-value = crnot+clrlwi, NOT bare SO.
//   Consequences: block1-inner compares are GT-based, block2-return is
//   `(reload == k2)` (EQ extract, exact match for `return (x == K)`).
//
// SHAPES THAT ARE NOW PROVEN (each verified by compiling probes/variants):
//  - block1-inner: `s32 a = (nv > k); if ((a ^ 1) != (lim > k)) store;`
//    emits EXACTLY want's fcmpu-cr7/mfcr/rlwinm(0x1e)/fcmpu-cr6/xori/mfcr/
//    rlwinm(0x1a)/cmpw/beq. Single-expression `(nv<=k)!=(lim>k)` instead fuses
//    to cror/creqv+bso (wrong); `((nv>k)^1)` single-expr also wrong. The named
//    temp forcing materialization is load-bearing.
//  - K must be a per-block FPR local (`f32 k`/`k2`, one lfs each, reused for
//    all compares in the block incl. the p190 `= k2` store and the return
//    compare). Textual `lbl_...` at each use emits an extra lis+lfs per use.
//  - block3: `(c140 > c150) != (reload140 > sum)` with the second p140 load
//    TEXTUAL emits want's creqv-cr6gt-cr7gt + bso exactly.
//  - `__builtin_fabsf` for the fabs insns (plain fabs() promotes to double).
//  - lfsx-form addressing needs f32* field-base pointer vars + a separate
//    byte-offset var dereferenced as `*(f32*)((char*)base + off)`; direct
//    `(char*)arg0+CONST+off` collapses to add-form.
//  - C89 rule (ngccc): no statements before declarations within a block —
//    mid-block recompute `off = arg1*4;` must sit after all decls of its block.
//
// REMAINING (block2 only, -4B, then cascade):
//   want  slwi r9,r4,2 / addi r8,r3,0x190 / lis r11 / lfsx f13,r8,r9 /
//         lfs f9,K(r11) / mr r10,r9 / addi r9,r3,0x170 / fcmpu / beq
//   got   lis r9,0 / slwi r0,r4,2 / addi r8,r3,0x190 / lfs f12,K(r9) /
//         lfsx f13,r8,r0 / addi r11,0x160(hoisted!) / addi r9,0x170 / fcmpu
//   i.e. off2 lands in r0 (want r9), K-anchor in r9 (want r11), the p160-addi
//   hoists above the fcmpu, and the `mr r10,r9` is missing.
//   The mr's purpose is now understood: block1's index dies after block1
//   (short range -> r10, verified: block1-only compiles mr-free with off in
//   r10); block2's off2 is born in r9; r9 is then clobbered by the p170-addi,
//   forcing the copy to r10 for block3/f1. What was NOT reproduced: getting
//   off2 into r9 in the first place, nor the slwi-first order.
//   Partitionings measured (off = block1 idx, off2 = block2 idx):
//     (a) B1:off B2+3:off2 -> off2 long-ranges into r3, arg0 copied r10 (BAD)
//     (b) B1:off B2:off2 B3:off2+reload-via-off -> off revived to r8 (34%)
//     (c) single off everywhere -> CSE merges to ONE slwi, -8B size break
//     (d) single var reassigned (C89-dance) -> arg0-copy back (31%)
//     (e) B1:off B2:off2 B3:off [KEPT] -> block1 clean, 41.6%, -4B (the mr)
//   Empirical allocator rule (5+ builds): a dead-after-block1 index -> r10;
//   a revived/long-range index -> r8/r3 + `mr r10,r3` arg0-copy. Retail has
//   the long range WITHOUT the copy — the unreproduced combination.
//   NEXT IDEAS: (1) anything that puts off2 in r9 (fewer live GPRs at block2
//   entry? different pointer-decl order — p170-before-p160 tried, no-op);
//   (2) `volatile`-qualified reload as an alternative p140 second load;
//   (3) check whether block3's `f1 -= sum - c140` should use the reloaded
//   value instead (currently uses first-load c140; want keeps reload live).
#include "types.h"
#include "structs.h"

extern f32 lbl_80299C2C;
extern void fn_800D77FC(f32);

s32 fn_800D9960(CScript *arg0, s32 arg1) {
    s32 off = arg1 * 4;
    f32 *p180 = (f32 *)((char *)arg0 + 0x180);
    f32 v = *(f32 *)((char *)p180 + off);
    s32 ret = 0;
    f32 f1;

    if (v != lbl_80299C2C) {
        f32 *p170 = (f32 *)((char *)arg0 + 0x170);
        f32 *p160 = (f32 *)((char *)arg0 + 0x160);
        f32 k = lbl_80299C2C;
        f32 sc = *(f32 *)((char *)arg0 + 0x1F8);
        f32 cur = *(f32 *)((char *)p170 + off);
        f32 nv = v * sc + cur;
        f32 lim;
        s32 a;
        *(f32 *)((char *)p170 + off) = nv;
        lim = *(f32 *)((char *)p160 + off);
        if (__builtin_fabsf(nv) > __builtin_fabsf(lim)) {
            a = (nv > k);
            if ((a ^ 1) != (lim > k)) {
                *(f32 *)((char *)p170 + off) = lim;
            }
        }
    }
    {
        s32 off2 = arg1 * 4;
        f32 *p190 = (f32 *)((char *)arg0 + 0x190);
        f32 *p160 = (f32 *)((char *)arg0 + 0x160);
        f32 *p170 = (f32 *)((char *)arg0 + 0x170);
        f32 v2 = *(f32 *)((char *)p190 + off2);
        f32 k2 = lbl_80299C2C;
        if (v2 != k2) {
            f32 sc = *(f32 *)((char *)arg0 + 0x1F8);
            f32 lim = *(f32 *)((char *)p160 + off2);
            f32 cur = *(f32 *)((char *)p170 + off2);
            f32 t = v2 * sc;
            if (__builtin_fabsf(t) > __builtin_fabsf(cur - lim)) {
                *(f32 *)((char *)p170 + off2) = lim;
                *(f32 *)((char *)p190 + off2) = k2;
                return (*(f32 *)((char *)p160 + off2) == k2);
            }
            *(f32 *)((char *)p170 + off2) = cur - t;
        }
        {
            f32 cur = *(f32 *)((char *)p170 + off2);
            f32 sc = *(f32 *)((char *)arg0 + 0x1F8);
            f1 = cur * sc;
        }
        if ((arg0->unk0x20 & (0x20 << arg1)) == 0) {
            f32 *p150 = (f32 *)((char *)arg0 + 0x150);
            f32 *p140 = (f32 *)((char *)arg0 + 0x140);
            f32 c150 = *(f32 *)((char *)p150 + off);
            f32 c140 = *(f32 *)((char *)p140 + off);
            f32 sum = c150 + f1;
            *(f32 *)((char *)p150 + off) = sum;
            if ((c140 > c150) != (*(f32 *)((char *)p140 + off) > sum)) {
                ret = 1;
                f1 -= sum - c140;
            }
        }
    }
    fn_800D77FC(f1);
    return ret;
}
