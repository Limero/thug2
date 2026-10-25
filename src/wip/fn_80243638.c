// PARKED 2026-09-18 — doc-15 CALL-ARG-SETUP / SCHEDULER SLOT-FILL WALL.
// Re-assessed: 59/84 = 70.2% with the two FLAG tokens below.
// Both tokens are load-bearing — `-fno-schedule-insns2` ALONE (`-fno-strength-
// reduce` dropped) collapses to 41/84 = 48.8%, so do not trim the FLAG line.
// Residual = 3 clusters, all pure scheduler slot-fill / colour tie-breaks on
// otherwise-identical content (the hand-rebuild body is correct):
//   +014  want `mr r29,r3 / lwz r0,0(r25) / addi r28,r25,4` vs got the `addi`
//         hoisted above the save (3-word rotation),
//   +04c  want `lwzx r9,r28,r30` before `mr r31,r3` (swapped),
//   +088  the in-arm arg setup: want `lwzx / addi r5,r29,4 / addi r6,r27,1 /
//         addi r11,r31,0x9c`, got `addi r27,r27,1` first and the two `addi
//         0x9c`/`0x84` temps coloured r8/r6 instead of r11/r7.
// This is the same one-call-site arg-setup-order gap documented in WIP.md's
// 2026-09-02 "doc-15 arg-setup family re-probe verdict" (want interleaves other
// arg setup / stores into the lis/ori materialisation gap; ngccc keeps pairs
// atomic). No source permutation moved any of the three clusters — the body
// already stages `nxt` in BOTH arms (the previous fix) and pins
// r29/r27/r10.
//
// family=m2c range=0x80243638-0x80243788 size=336B
// FLAG: -fno-strength-reduce -fno-schedule-insns2
// HAND-REBUILT from disasm; ~97% aligned content. Copies a 32-entry table
// from arg1 into arg0. Key shapes: chained alloc fn_80243434(Mem_NewZero(
// 0xF0)) (fn_80243434 reads r3); struct-member array views ((tbl_t*)arg1)
// ->e[i] for lwzx/stwx indexed forms; 21-word copy loop as countdown
// do-while (var_r10=0x48 step -0x18; -fno-strength-reduce stops mtctr);
// nxt=i+1 staged in BOTH arms so GCC duplicates addi r6 like retail;
// entry-fill zeros AFTER the two data loads (store-slot match).
// REMAINING DIFFS (3 clusters, all scheduler slot-fill tie-breaks):
// prologue addi r28 hoisted above mr r29; mr r31,r3 one slot early after
// bl fn_80243434; in-arm addi r27,r27,1 (nxt folded by r27-pin) vs want's
// per-arm addi r6,r27,1 + join mr.
// Arity ground truths: fn_80243434 is genuinely 1-arg (arg0 = alloc result,
// chained); Mem_NewZero(s32)->ptr; fn_8026B2B4 = strcpy-shaped 2-arg.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
extern s32 Mem_NewZero(s32 arg0);
extern void *fn_80243434(Unk_12004030 * arg0);
extern void strcpy(void *arg0, void *arg1);

typedef struct {
    char _0[4];
    s32 e[33];
} tbl_t;

typedef struct {
    char _0[0x84];
    s32 w[33];
} tbl84_t;

void *fn_80243638(void *arg0, s32 *arg1) {
    register void *var_r29 __asm__("r29");
    register s32 var_r27 __asm__("r27");
    s32 src;
    s32 nxt;
    Unk_C8FEE62D *temp_r31;
    s32 *dst;
    s32 *srcw;
    register s32 var_r10 __asm__("r10");
    s32 temp_r0;

    var_r29 = arg0;
    ((Unk_B3CC37CC *)var_r29)->unk0x0 = *(s32 *)arg1;
    var_r27 = 0;
    do {
        src = ((tbl_t *)arg1)->e[var_r27];
        if (src != 0) {
            temp_r31 = fn_80243434((void *)Mem_NewZero(0xF0));
            temp_r31->unk0x4 = *(s32 *)(((tbl_t *)arg1)->e[var_r27] + 0x4);
            temp_r31->unk0x8 = *(s32 *)(((tbl_t *)arg1)->e[var_r27] + 0x8);
            temp_r31->unk0xC = 0;
            temp_r31->unk0x10 = 0;
            temp_r31->unk0x14 = 0;
            temp_r31->unk0x18 = 0;
            strcpy((void *)((char *)temp_r31 + 0x1C), (void *)(((tbl_t *)arg1)->e[var_r27] + 0x1C));
            dst = (s32 *)((char *)temp_r31 + 0x9C);
            srcw = (s32 *)(((tbl_t *)arg1)->e[var_r27] + 0x9C);
            var_r10 = 0x48;
            do {
                var_r10 -= 0x18;
                dst[0] = srcw[0];
                dst[1] = srcw[1];
                dst[2] = srcw[2];
                dst[3] = srcw[3];
                dst[4] = srcw[4];
                temp_r0 = srcw[5];
                srcw += 6;
                dst[5] = temp_r0;
                dst += 6;
            } while (var_r10 != 0);
            dst[0] = srcw[0];
            dst[1] = srcw[1];
            dst[2] = srcw[2];
            ((tbl_t *)var_r29)->e[var_r27] = (s32)temp_r31;
            nxt = var_r27 + 1;
        } else {
            ((tbl_t *)var_r29)->e[var_r27] = src;
            nxt = var_r27 + 1;
        }
        ((tbl84_t *)var_r29)->w[var_r27] = ((tbl84_t *)arg1)->w[var_r27];
        var_r27 = nxt;
    } while (var_r27 <= 0x1F);
    ((Unk_B3CC37CC *)var_r29)->unk0x104 = 0;
    return var_r29;
}
