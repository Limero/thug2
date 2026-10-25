// PARKED 2026-10-19 at 70.5% (45 diffs, got 620B vs want 624B) — best match;
// re-triage of the 2026-09-19 67.3% body: residual (a) from that note (the
// fn_80240B0C call addi hoist) now matches — the current call spelling
// emits li r9/li r5/li r6/li r7/li r8/addi r3/li r4 in want order.
// Tried 2026-10-19: inlining the k=1 combine as
// *(u8*)B2C(sp8,1)=*(s8*)(arg0+1)+*(u8*)(tmp+1) folds the extsb away
// entirely (63.5%, 616B); the staged dst1/sgn1 form keeps extsb in both
// operand orders (`sgn1 + tmp` and `tmp + sgn1` both score 70.5% — GCC
// canonicalises the add, so the order is not the lever). Staging the
// second overlap test through `u8 *sp_p = sp8` materialises an address
// but in the wrong place (extra store, branch structure shifts, 49.4%) —
// reverted. Remaining residuals, both pure regalloc/scheduling: (1) k=1
// combine loads arg0[1] into r9 instead of r0 (want r0=sgn/r9=tmp,
// extsb r0; got r9=sgn/r0=tmp, extsb r9; the add itself is identical);
// (2) the second overlap test is one `addi r10,r1,8` short (want
// materialises &sp8 into r10 mid-test and addresses sp8[1]/sp8[4]/
// sp8[2]/sp8[5] via (r10); this draft addresses everything via (r1))
// with knock-on register names (r6/r7/r10/r8 vs r11/r9/r10). Park;
// needs a new lever that pins &sp8 into a register without extra stores.
// (2026-09-19 note, superseded except for the history: two fixes landed
// top of the hand-rebuilt body:
//  * the k=1 combine store IS `(s8)arg0[1] + temp_r29[1]`: WANT keeps the
//    `extsb`. The old inline `(s8)*(u8*)...` let ngccc fold it away, so the
//    call result is now saved to `dst1` FIRST, then `sgn1 = *(s8*)(arg0+1)`,
//    then the store — that reproduces WANT's `bl; lbz; lbz; extsb; add; stb`
//    order (60.3% -> 67.3%). Writing it inline, as a local s8, or with any
//    of -fno-gcse/-fno-schedule-insns* also folds or reorders it.
//  * residual (still parked): (a) the `addi r3, r1, 8` for the 7-arg
//    fn_80240B0C call is hoisted 4 slots early by ngccc (WANT emits it after
//    li r8, before li r4); `&sp8[0]`, `(u8 *)sp8`, a staged pointer and all
//    flag combos keep ngccc's order. (b) the second overlap test differs only
//    by register naming (r6/r7 vs r11/r9). Park, do not re-grind.
// family=m2c range=0x802428BC-0x80242B2C size=624B
// HAND-REBUILT from disasm; NEAR 60.3% positional (~90% content-aligned).
// REMAINING DIFFS: (a) fn_80240B0C call: got hoists `addi r3,r1,8` above
// the li-zero arg block (want emits it between li r8/li r4); (b) k=1
// combine: want keeps `extsb r0,r0` on arg0[1], GCC folds it away in every
// C spelling tried ((s8) cast, swapped operands, u8 trunc wrap, staged
// temps); (c) cascade shifts from (a)/(b). Levers: -fno-schedule-insns2,
// -fno-gcse, operand swaps, staged temps. AABB-overlap scan:
// 3-axis byte/sbyte overlap test between arg0 and arg1, then optional
// (arg2) scan for any entry with flag +4 set, then per-entry loop: vcall
// method(*(arg0+0x38)+0xC)(arg0+lha off, i), bare chained fn_80240C80()
// (blr stub, vcall ret passes through r3), 7-arg zero-fill
// fn_80240B0C(&sp8,0,0,0,0,0,0), fn_80240BB4(obj,&sp8), three combine
// stores via fn_80240B2C(&sp8,k), second overlap test -> return 1.
// sp8 is u8[6] (rounds to 8-byte slot = want frame 0x28).
// Arity ground truths: fn_80240B0C(ptr,u8,u8,u8,u8,u8,u8) 7-arg byte-set;
// fn_80240B2C(ptr,idx)->ptr 2-arg; fn_80240BB4 2-arg; fn_80240C80 0-arg
// stub here (chained r3); vcall method is 2-arg (obj+off, i).
#include "types.h"
extern void *fn_80241E38(void *arg0, s32 arg1);
extern void *fn_80240C80(void);
extern s32 fn_80240B0C(void *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6);
extern void fn_80240BB4(void *arg0, void *arg1);
extern s32 fn_80240B2C(s32 arg0, s32 arg1);

s32 fn_802428BC(void *arg0, void *arg1, s32 arg2) {
    u8 sp8[6];
    s32 var_r29;
    s8 sgn1;
    u8 *dst1;
    s32 var_r30;
    s32 var_r27;
    void *temp_r29;
    void *temp_r30;

    if (((s32)(*(u8 *)((char *)arg0 + 0) + *(u8 *)((char *)arg0 + 3)) > *(u8 *)((char *)arg1 + 0))
    && ((s32)(*(u8 *)((char *)arg0 + 0) < (*(u8 *)((char *)arg1 + 0) + *(u8 *)((char *)arg1 + 3))))
    && ((s32)((s8)*(u8 *)((char *)arg0 + 1) + *(u8 *)((char *)arg0 + 4)) > (s8)*(u8 *)((char *)arg1 + 1))
    && ((s32)((s8)*(u8 *)((char *)arg0 + 1) < ((s8)*(u8 *)((char *)arg1 + 1) + *(u8 *)((char *)arg1 + 4))))
    && ((s32)(*(u8 *)((char *)arg0 + 2) + *(u8 *)((char *)arg0 + 5)) > *(u8 *)((char *)arg1 + 2))
    && ((s32)(*(u8 *)((char *)arg0 + 2) < (*(u8 *)((char *)arg1 + 2) + *(u8 *)((char *)arg1 + 5))))) {
        var_r29 = 0;
        if (arg2 != 0) {
            for (var_r30 = 0; var_r30 < (u32)*(u32 *)((char *)arg0 + 0x30); var_r30++) {
                if (*(u8 *)((char *)fn_80241E38(arg0, var_r30) + 4) != 0) {
                    var_r29 = 1;
                }
            }
        }
        if (var_r29 == 0) {
            return 1;
        }
        for (var_r27 = 0; var_r27 < (u32)*(u32 *)((char *)arg0 + 0x30); var_r27++) {
            temp_r29 = fn_80241E38(arg0, var_r27);
            ((void (*)(void *, s32))*(s32 *)(*(s32 *)((char *)arg0 + 0x38) + 0xC))(
                (char *)arg0 + (s32)*(s16 *)(*(s32 *)((char *)arg0 + 0x38) + 8), var_r27);
            temp_r30 = fn_80240C80();
            fn_80240B0C((void *)sp8, 0, 0, 0, 0, 0, 0);
            fn_80240BB4(temp_r30, (void *)sp8);
            *(u8 *)fn_80240B2C((s32)(void *)sp8, 0) = *(u8 *)((char *)arg0 + 0) + *(u8 *)((char *)temp_r29 + 0);
            dst1 = (u8 *)fn_80240B2C((s32)(void *)sp8, 1);
    sgn1 = *(s8 *)((char *)arg0 + 1);
    *dst1 = *(u8 *)((char *)temp_r29 + 1) + sgn1;
            *(u8 *)fn_80240B2C((s32)(void *)sp8, 2) = *(u8 *)((char *)arg0 + 2) + *(u8 *)((char *)temp_r29 + 2);
            if (*(u8 *)((char *)temp_r29 + 4) == 0
            && ((s32)(sp8[0] + sp8[3]) > *(u8 *)((char *)arg1 + 0))
            && ((s32)(sp8[0] < (*(u8 *)((char *)arg1 + 0) + *(u8 *)((char *)arg1 + 3))))
            && ((s32)((s8)sp8[1] + sp8[4]) > (s8)*(u8 *)((char *)arg1 + 1))
            && ((s32)((s8)sp8[1] < ((s8)*(u8 *)((char *)arg1 + 1) + *(u8 *)((char *)arg1 + 4))))
            && ((s32)(sp8[2] + sp8[5]) > *(u8 *)((char *)arg1 + 2))
            && ((s32)(sp8[2] < (*(u8 *)((char *)arg1 + 2) + *(u8 *)((char *)arg1 + 5))))) {
                return 1;
            }
        }
    }
    return 0;
}
