// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C39EC-0x801C4228 (2108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern f32 fn_800144C8(void);
extern void fn_80003FF8(Unk_DB0E2BAB *, s32, f32);
extern f32 lbl_802ACAEC;
extern f32 lbl_802ACAF0;
extern f32 lbl_802ACAF4;

void fn_801C39EC(void *arg0) {
    struct {
        f32 v[16];
        f32 m[16];
        volatile s32 h88;
        volatile s32 h8C;
        volatile s32 h90;
        volatile s32 h94;
    } fr;
    f32 var_f1;
    f32 var_f12;
    f32 temp_f13;
    register s32 a0 __asm__("r30");
    register s32 idx __asm__("r29");
    register f32 *bp __asm__("r28");
    register char *walker __asm__("r31");
    register f32 *pv1 __asm__("r11");
    register char *temp_r9 __asm__("r9");
    register char *temp_r10 __asm__("r10");
    register char *temp_r11 __asm__("r11");
    s32 ctr;

    a0 = (s32)arg0;
    for (ctr = 4; ctr != 0; ctr--) {}
    idx = 0;
    __asm__("" : "+r"(idx));
    bp = fr.v;
    walker = (char *)a0 + 0x1C;
    do {
        if (*(s32 *)(walker + 0x10) != 0) {
            var_f1 = fn_800144C8() * ((Unk_5EF41E38 *)walker)->unk0x8;
            temp_f13 = ((Unk_59AB5482_2 *)walker)->unk0xC + __builtin_fabsf(var_f1);
            ((Unk_59AB5482_2 *)walker)->unk0xC = temp_f13;
            if (temp_f13 >= ((Unk_59AB5482_2 *)walker)->unk0x0) {
                *(s32 *)(walker + 0x10) = 0;
                if (var_f1 < lbl_802ACAEC) {
                    var_f12 = lbl_802ACAF0;
                } else {
                    var_f12 = lbl_802ACAF4;
                }
                var_f1 -= var_f12 * (((Unk_59AB5482_2 *)walker)->unk0xC - ((Unk_59AB5482_2 *)walker)->unk0x0);
            }
            fn_80003FF8(fr.v, idx, var_f1);
            temp_r9 = *(char **)((char *)a0 + 0xC);
            fr.h88 = (s32)bp;
            fr.h8C = (s32)(temp_r9 + 0x78);
            __asm__("" : "+r"(bp) : "m"(fr.h8C));
            pv1 = bp;
            fr.m[0] = *(f32 *)((char *)pv1 + 0x0) * ((Unk_DB0E2BAB *)temp_r9)->unk0x78 + *(f32 *)((char *)pv1 + 0x4) * ((Unk_DB0E2BAB *)temp_r9)->unk0x88 + *(f32 *)((char *)pv1 + 0x8) * ((Unk_DB0E2BAB *)temp_r9)->unk0x98 + *(f32 *)((char *)pv1 + 0xc) * *(f32 *)((char *)temp_r9 + 0xa8);
            fr.m[1] = *(f32 *)((char *)pv1 + 0x0) * ((Unk_DB0E2BAB *)temp_r9)->unk0x7C + *(f32 *)((char *)pv1 + 0x4) * ((Unk_DB0E2BAB *)temp_r9)->unk0x8C + *(f32 *)((char *)pv1 + 0x8) * *(f32 *)((char *)temp_r9 + 0x9c) + *(f32 *)((char *)pv1 + 0xc) * *(f32 *)((char *)temp_r9 + 0xac);
            fr.m[2] = *(f32 *)((char *)pv1 + 0x0) * ((Unk_DB0E2BAB *)temp_r9)->unk0x80 + *(f32 *)((char *)pv1 + 0x4) * ((Unk_DB0E2BAB *)temp_r9)->unk0x90 + *(f32 *)((char *)pv1 + 0x8) * ((Unk_DB0E2BAB *)temp_r9)->unk0xA0 + *(f32 *)((char *)pv1 + 0xc) * ((Unk_DB0E2BAB *)temp_r9)->unk0xB0;
            fr.m[3] = *(f32 *)((char *)pv1 + 0x0) * ((Unk_DB0E2BAB *)temp_r9)->unk0x84 + *(f32 *)((char *)pv1 + 0x4) * ((Unk_DB0E2BAB *)temp_r9)->unk0x94 + *(f32 *)((char *)pv1 + 0x8) * ((Unk_DB0E2BAB *)temp_r9)->unk0xA4 + *(f32 *)((char *)pv1 + 0xc) * *(f32 *)((char *)temp_r9 + 0xb4);
            fr.m[4] = *(f32 *)((char *)pv1 + 0x10) * ((Unk_DB0E2BAB *)temp_r9)->unk0x78 + *(f32 *)((char *)pv1 + 0x14) * ((Unk_DB0E2BAB *)temp_r9)->unk0x88 + *(f32 *)((char *)pv1 + 0x18) * ((Unk_DB0E2BAB *)temp_r9)->unk0x98 + *(f32 *)((char *)pv1 + 0x1c) * *(f32 *)((char *)temp_r9 + 0xa8);
            fr.m[5] = *(f32 *)((char *)pv1 + 0x10) * ((Unk_DB0E2BAB *)temp_r9)->unk0x7C + *(f32 *)((char *)pv1 + 0x14) * ((Unk_DB0E2BAB *)temp_r9)->unk0x8C + *(f32 *)((char *)pv1 + 0x18) * *(f32 *)((char *)temp_r9 + 0x9c) + *(f32 *)((char *)pv1 + 0x1c) * *(f32 *)((char *)temp_r9 + 0xac);
            fr.m[6] = *(f32 *)((char *)pv1 + 0x10) * ((Unk_DB0E2BAB *)temp_r9)->unk0x80 + *(f32 *)((char *)pv1 + 0x14) * ((Unk_DB0E2BAB *)temp_r9)->unk0x90 + *(f32 *)((char *)pv1 + 0x18) * ((Unk_DB0E2BAB *)temp_r9)->unk0xA0 + *(f32 *)((char *)pv1 + 0x1c) * ((Unk_DB0E2BAB *)temp_r9)->unk0xB0;
            fr.m[7] = *(f32 *)((char *)pv1 + 0x10) * ((Unk_DB0E2BAB *)temp_r9)->unk0x84 + *(f32 *)((char *)pv1 + 0x14) * ((Unk_DB0E2BAB *)temp_r9)->unk0x94 + *(f32 *)((char *)pv1 + 0x18) * ((Unk_DB0E2BAB *)temp_r9)->unk0xA4 + *(f32 *)((char *)pv1 + 0x1c) * *(f32 *)((char *)temp_r9 + 0xb4);
            fr.m[8] = *(f32 *)((char *)pv1 + 0x20) * ((Unk_DB0E2BAB *)temp_r9)->unk0x78 + *(f32 *)((char *)pv1 + 0x24) * ((Unk_DB0E2BAB *)temp_r9)->unk0x88 + *(f32 *)((char *)pv1 + 0x28) * ((Unk_DB0E2BAB *)temp_r9)->unk0x98 + *(f32 *)((char *)pv1 + 0x2c) * *(f32 *)((char *)temp_r9 + 0xa8);
            fr.m[9] = *(f32 *)((char *)pv1 + 0x20) * ((Unk_DB0E2BAB *)temp_r9)->unk0x7C + *(f32 *)((char *)pv1 + 0x24) * ((Unk_DB0E2BAB *)temp_r9)->unk0x8C + *(f32 *)((char *)pv1 + 0x28) * *(f32 *)((char *)temp_r9 + 0x9c) + *(f32 *)((char *)pv1 + 0x2c) * *(f32 *)((char *)temp_r9 + 0xac);
            fr.m[10] = *(f32 *)((char *)pv1 + 0x20) * ((Unk_DB0E2BAB *)temp_r9)->unk0x80 + *(f32 *)((char *)pv1 + 0x24) * ((Unk_DB0E2BAB *)temp_r9)->unk0x90 + *(f32 *)((char *)pv1 + 0x28) * ((Unk_DB0E2BAB *)temp_r9)->unk0xA0 + *(f32 *)((char *)pv1 + 0x2c) * ((Unk_DB0E2BAB *)temp_r9)->unk0xB0;
            fr.m[11] = *(f32 *)((char *)pv1 + 0x20) * ((Unk_DB0E2BAB *)temp_r9)->unk0x84 + *(f32 *)((char *)pv1 + 0x24) * ((Unk_DB0E2BAB *)temp_r9)->unk0x94 + *(f32 *)((char *)pv1 + 0x28) * ((Unk_DB0E2BAB *)temp_r9)->unk0xA4 + *(f32 *)((char *)pv1 + 0x2c) * *(f32 *)((char *)temp_r9 + 0xb4);
            fr.m[12] = *(f32 *)((char *)pv1 + 0x30) * ((Unk_DB0E2BAB *)temp_r9)->unk0x78 + *(f32 *)((char *)pv1 + 0x34) * ((Unk_DB0E2BAB *)temp_r9)->unk0x88 + *(f32 *)((char *)pv1 + 0x38) * ((Unk_DB0E2BAB *)temp_r9)->unk0x98 + *(f32 *)((char *)pv1 + 0x3c) * *(f32 *)((char *)temp_r9 + 0xa8);
            fr.m[13] = *(f32 *)((char *)pv1 + 0x30) * ((Unk_DB0E2BAB *)temp_r9)->unk0x7C + *(f32 *)((char *)pv1 + 0x34) * ((Unk_DB0E2BAB *)temp_r9)->unk0x8C + *(f32 *)((char *)pv1 + 0x38) * *(f32 *)((char *)temp_r9 + 0x9c) + *(f32 *)((char *)pv1 + 0x3c) * *(f32 *)((char *)temp_r9 + 0xac);
            fr.m[14] = *(f32 *)((char *)pv1 + 0x30) * ((Unk_DB0E2BAB *)temp_r9)->unk0x80 + *(f32 *)((char *)pv1 + 0x34) * ((Unk_DB0E2BAB *)temp_r9)->unk0x90 + *(f32 *)((char *)pv1 + 0x38) * ((Unk_DB0E2BAB *)temp_r9)->unk0xA0 + *(f32 *)((char *)pv1 + 0x3c) * ((Unk_DB0E2BAB *)temp_r9)->unk0xB0;
            fr.m[15] = *(f32 *)((char *)pv1 + 0x30) * ((Unk_DB0E2BAB *)temp_r9)->unk0x84 + *(f32 *)((char *)pv1 + 0x34) * ((Unk_DB0E2BAB *)temp_r9)->unk0x94 + *(f32 *)((char *)pv1 + 0x38) * ((Unk_DB0E2BAB *)temp_r9)->unk0xA4 + *(f32 *)((char *)pv1 + 0x3c) * *(f32 *)((char *)temp_r9 + 0xb4);
            ((Unk_0B6E8BDA *)temp_r9)->unk0x78 = *(__ps_t *)&fr.m[0];
            ((Unk_0B6E8BDA *)temp_r9)->unk0x80 = *(__ps_t *)&fr.m[2];
            ((Unk_0B6E8BDA *)temp_r9)->unk0x88 = *(__ps_t *)&fr.m[4];
            ((Unk_0B6E8BDA *)temp_r9)->unk0x90 = *(__ps_t *)&fr.m[6];
            ((Unk_0B6E8BDA *)temp_r9)->unk0x98 = *(__ps_t *)&fr.m[8];
            ((Unk_0B6E8BDA *)temp_r9)->unk0xA0 = *(__ps_t *)&fr.m[10];
            ((Unk_0B6E8BDA *)temp_r9)->unk0xA8 = *(__ps_t *)&fr.m[12];
            ((Unk_0B6E8BDA *)temp_r9)->unk0xB0 = *(__ps_t *)&fr.m[14];
            temp_r10 = *(char **)((char *)a0 + 0x58);
            fr.h90 = (s32)bp;
            temp_r11 = temp_r10 + 0x20;
            __asm__("" : "+r"(temp_r11));
            fr.h94 = (s32)temp_r11;
            __asm__("" : "+r"(bp) : "r"(temp_r11));
            temp_r9 = bp;
            fr.m[0] = *(f32 *)((char *)temp_r9 + 0x0) * *(f32 *)((char *)temp_r10 + 0x20) + *(f32 *)((char *)temp_r9 + 0x4) * *(f32 *)((char *)temp_r10 + 0x30) + *(f32 *)((char *)temp_r9 + 0x8) * *(f32 *)((char *)temp_r11 + 0x20) + *(f32 *)((char *)temp_r9 + 0xc) * *(f32 *)((char *)temp_r11 + 0x30);
            fr.m[1] = *(f32 *)((char *)temp_r9 + 0x0) * *(f32 *)((char *)temp_r11 + 0x4) + *(f32 *)((char *)temp_r9 + 0x4) * *(f32 *)((char *)temp_r11 + 0x14) + *(f32 *)((char *)temp_r9 + 0x8) * *(f32 *)((char *)temp_r11 + 0x24) + *(f32 *)((char *)temp_r9 + 0xc) * *(f32 *)((char *)temp_r11 + 0x34);
            fr.m[2] = *(f32 *)((char *)temp_r9 + 0x0) * *(f32 *)((char *)temp_r11 + 0x8) + *(f32 *)((char *)temp_r9 + 0x4) * *(f32 *)((char *)temp_r11 + 0x18) + *(f32 *)((char *)temp_r9 + 0x8) * *(f32 *)((char *)temp_r11 + 0x28) + *(f32 *)((char *)temp_r9 + 0xc) * *(f32 *)((char *)temp_r11 + 0x38);
            fr.m[3] = *(f32 *)((char *)temp_r9 + 0x0) * *(f32 *)((char *)temp_r11 + 0xc) + *(f32 *)((char *)temp_r9 + 0x4) * *(f32 *)((char *)temp_r11 + 0x1c) + *(f32 *)((char *)temp_r9 + 0x8) * *(f32 *)((char *)temp_r11 + 0x2c) + *(f32 *)((char *)temp_r9 + 0xc) * *(f32 *)((char *)temp_r11 + 0x3c);
            fr.m[4] = *(f32 *)((char *)temp_r9 + 0x10) * *(f32 *)((char *)temp_r10 + 0x20) + *(f32 *)((char *)temp_r9 + 0x14) * *(f32 *)((char *)temp_r11 + 0x10) + *(f32 *)((char *)temp_r9 + 0x18) * *(f32 *)((char *)temp_r11 + 0x20) + *(f32 *)((char *)temp_r9 + 0x1c) * *(f32 *)((char *)temp_r11 + 0x30);
            fr.m[5] = *(f32 *)((char *)temp_r9 + 0x10) * *(f32 *)((char *)temp_r11 + 0x4) + *(f32 *)((char *)temp_r9 + 0x14) * *(f32 *)((char *)temp_r11 + 0x14) + *(f32 *)((char *)temp_r9 + 0x18) * *(f32 *)((char *)temp_r11 + 0x24) + *(f32 *)((char *)temp_r9 + 0x1c) * *(f32 *)((char *)temp_r11 + 0x34);
            fr.m[6] = *(f32 *)((char *)temp_r9 + 0x10) * *(f32 *)((char *)temp_r11 + 0x8) + *(f32 *)((char *)temp_r9 + 0x14) * *(f32 *)((char *)temp_r11 + 0x18) + *(f32 *)((char *)temp_r9 + 0x18) * *(f32 *)((char *)temp_r11 + 0x28) + *(f32 *)((char *)temp_r9 + 0x1c) * *(f32 *)((char *)temp_r11 + 0x38);
            fr.m[7] = *(f32 *)((char *)temp_r9 + 0x10) * *(f32 *)((char *)temp_r11 + 0xc) + *(f32 *)((char *)temp_r9 + 0x14) * *(f32 *)((char *)temp_r11 + 0x1c) + *(f32 *)((char *)temp_r9 + 0x18) * *(f32 *)((char *)temp_r11 + 0x2c) + *(f32 *)((char *)temp_r9 + 0x1c) * *(f32 *)((char *)temp_r11 + 0x3c);
            fr.m[8] = *(f32 *)((char *)temp_r9 + 0x20) * *(f32 *)((char *)temp_r10 + 0x20) + *(f32 *)((char *)temp_r9 + 0x24) * *(f32 *)((char *)temp_r11 + 0x10) + *(f32 *)((char *)temp_r9 + 0x28) * *(f32 *)((char *)temp_r11 + 0x20) + *(f32 *)((char *)temp_r9 + 0x2c) * *(f32 *)((char *)temp_r11 + 0x30);
            fr.m[9] = *(f32 *)((char *)temp_r9 + 0x20) * *(f32 *)((char *)temp_r11 + 0x4) + *(f32 *)((char *)temp_r9 + 0x24) * *(f32 *)((char *)temp_r11 + 0x14) + *(f32 *)((char *)temp_r9 + 0x28) * *(f32 *)((char *)temp_r11 + 0x24) + *(f32 *)((char *)temp_r9 + 0x2c) * *(f32 *)((char *)temp_r11 + 0x34);
            fr.m[10] = *(f32 *)((char *)temp_r9 + 0x20) * *(f32 *)((char *)temp_r11 + 0x8) + *(f32 *)((char *)temp_r9 + 0x24) * *(f32 *)((char *)temp_r11 + 0x18) + *(f32 *)((char *)temp_r9 + 0x28) * *(f32 *)((char *)temp_r11 + 0x28) + *(f32 *)((char *)temp_r9 + 0x2c) * *(f32 *)((char *)temp_r11 + 0x38);
            fr.m[11] = *(f32 *)((char *)temp_r9 + 0x20) * *(f32 *)((char *)temp_r11 + 0xc) + *(f32 *)((char *)temp_r9 + 0x24) * *(f32 *)((char *)temp_r11 + 0x1c) + *(f32 *)((char *)temp_r9 + 0x28) * *(f32 *)((char *)temp_r11 + 0x2c) + *(f32 *)((char *)temp_r9 + 0x2c) * *(f32 *)((char *)temp_r11 + 0x3c);
            fr.m[12] = *(f32 *)((char *)temp_r9 + 0x30) * *(f32 *)((char *)temp_r10 + 0x20) + *(f32 *)((char *)temp_r9 + 0x34) * *(f32 *)((char *)temp_r11 + 0x10) + *(f32 *)((char *)temp_r9 + 0x38) * *(f32 *)((char *)temp_r11 + 0x20) + *(f32 *)((char *)temp_r9 + 0x3c) * *(f32 *)((char *)temp_r11 + 0x30);
            fr.m[13] = *(f32 *)((char *)temp_r9 + 0x30) * *(f32 *)((char *)temp_r11 + 0x4) + *(f32 *)((char *)temp_r9 + 0x34) * *(f32 *)((char *)temp_r11 + 0x14) + *(f32 *)((char *)temp_r9 + 0x38) * *(f32 *)((char *)temp_r11 + 0x24) + *(f32 *)((char *)temp_r9 + 0x3c) * *(f32 *)((char *)temp_r11 + 0x34);
            fr.m[14] = *(f32 *)((char *)temp_r9 + 0x30) * *(f32 *)((char *)temp_r11 + 0x8) + *(f32 *)((char *)temp_r9 + 0x34) * *(f32 *)((char *)temp_r11 + 0x18) + *(f32 *)((char *)temp_r9 + 0x38) * *(f32 *)((char *)temp_r11 + 0x28) + *(f32 *)((char *)temp_r9 + 0x3c) * *(f32 *)((char *)temp_r11 + 0x38);
            fr.m[15] = *(f32 *)((char *)temp_r9 + 0x30) * *(f32 *)((char *)temp_r11 + 0xc) + *(f32 *)((char *)temp_r9 + 0x34) * *(f32 *)((char *)temp_r11 + 0x1c) + *(f32 *)((char *)temp_r9 + 0x38) * *(f32 *)((char *)temp_r11 + 0x2c) + *(f32 *)((char *)temp_r9 + 0x3c) * *(f32 *)((char *)temp_r11 + 0x3c);
            ((Unk_C1F9F519 *)temp_r10)->unk0x20 = *(__ps_t *)&fr.m[0];
            ((Unk_C1F9F519 *)temp_r11)->unk0x8 = *(__ps_t *)&fr.m[2];
            ((Unk_C1F9F519 *)temp_r11)->unk0x10 = *(__ps_t *)&fr.m[4];
            ((Unk_C1F9F519 *)temp_r11)->unk0x18 = *(__ps_t *)&fr.m[6];
            ((Unk_C1F9F519 *)temp_r11)->unk0x20 = *(__ps_t *)&fr.m[8];
            ((Unk_C1F9F519 *)temp_r11)->unk0x28 = *(__ps_t *)&fr.m[10];
            ((Unk_C1F9F519 *)temp_r11)->unk0x30 = *(__ps_t *)&fr.m[12];
            ((Unk_C1F9F519 *)temp_r11)->unk0x38 = *(__ps_t *)&fr.m[14];
        }
        idx++;
        walker += 0x14;
    } while (idx <= 2);

    if ((((Unk_C8FEE62D *)a0)->unk0x2C == 0) && (((Unk_C8FEE62D *)a0)->unk0x40 == 0) && (((Unk_C8FEE62D *)a0)->unk0x54 == 0)) {
        temp_r9 = *(char **)((char *)a0 + 0x18);
        ((s32 (*)(void *, s32)) ((Unk_DB0E2BAB *)temp_r9)->unk0x44)((char *)a0 + ((Unk_DB0E2BAB *)temp_r9)->unk0x40, 1);
    }
}
