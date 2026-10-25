// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-ffixed-r11` -> 14.49% to 23.19%.
// WIP draft - PARKED. See notes below.
// extra_cflags: -mps-float -ffixed-r11
// family=m2c range=0x800FD074-0x800FD188 size=276B
// PARKED: PS stack-spill/regalloc class (docs/parkings/06-paired-single-ops.md
//   M5.0j). Reconstruction is semantically complete but ngccc 3.9.3 will not
//   reproduce the game's coupled allocator decisions:
//   - want saves r29/r30/r31 (arg0, &tmpA across the bl, arg1); 3.9.3 folds
//     &tmpA into an r1 displacement and saves only two regs (frame 0x30 vs
//     want 0x38; a volatile-double dummy fixes the frame but not the save set)
//   - stack slots: want tmpA@0x8 < tmpB@0x10 < out@0x18; ngccc assigns them in
//     reverse declaration order and refuses the game's order+save-set combo
//   - branch arms: want keeps tbl in r8 and mulli product in r11; got uses
//     r10/r5 (cascade of the missing third saved reg)
//   - post-call block: game reloads every pair from the stack (psq_l after
//     psq_st); 3.9.3 keeps __ps_t temps in FPRs (doc06 M5.0j spill gap).
//   Best candidate kept below (-mps-float): 14.5% masked. Needs the game's
//   exact ProDG build for the spill pattern.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029C16C;
extern void fn_8008757C(void *, Unk_DB0E2BAB *, CStruct *);

void *fn_800FD074(Unk_EA529D06 *arg0, Unk_BE223D5D *arg1, s32 arg2) {
    __ps_t t10;
    __ps_t t18;
    f32 out[4];
    f32 tmpB[2];
    f32 tmpA[2];
    f32 c16C;
    f32 *pv;
    s32 base;
    s32 off;
    Unk_C7387A53 *tbl;
    s32 v;

    tbl = arg1->unk0x8;
    v = tbl->unk0x3C;
    if (v != 0) {
        off = arg2 * 12;
        c16C = lbl_8029C16C;
        out[0] = *(f32 *)((char *)v + off);
        out[1] = *(f32 *)(off + (s32)*((s32 *volatile *)&tbl->unk0x3C) + 4);
        base = *((s32 *volatile *)&tbl->unk0x3C);
    } else {
        off = arg2 * 12;
        c16C = lbl_8029C16C;
        v = tbl->unk0x30;
        out[0] = *(f32 *)((char *)v + off);
        out[1] = *(f32 *)(off + (s32)*((s32 *volatile *)&tbl->unk0x30) + 4);
        base = *((s32 *volatile *)&tbl->unk0x30);
    }
    out[2] = *(f32 *)((char *)base + off + 8);
    out[3] = c16C;
    *(__ps_t *)tmpB = *(__ps_t *)(out + 2);
    c16C = lbl_8029C16C;
    *(__ps_t *)tmpA = *(__ps_t *)out;
    tmpB[1] = c16C;
    pv = tmpA;
    fn_8008757C((void *)out, (char *)arg1 + 0x20, (void *)pv);
    *(__ps_t *)tmpA = *(__ps_t *)out;
    t10 = arg1->unk0x10;
    *(__ps_t *)tmpB = *(__ps_t *)(out + 2);
    t18 = arg1->unk0x18;
    *(__ps_t *)pv = *(__ps_t *)pv + t10;
    *(__ps_t *)pv = *(__ps_t *)pv + t18;
    arg0->unk0x8 = *(__ps_t *)tmpB;
    arg0->unk0x0 = *(__ps_t *)tmpA;
    return arg0;
}
