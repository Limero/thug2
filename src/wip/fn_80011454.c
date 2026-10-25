// PARKED 2026-10-03 — base 5.8% (1344 B, 171 words).  Random-sample pick,
// no parking note before this.  Dominated by call-prototype errors: the body
// makes 10+ calls whose callees are still implicit-decl, so every one of them
// emits `crclr cr1eq` and shifts the whole tail.  Doc-56 rescan territory
// (tools/protoscale.py), not a codegen wall.  Untested lever: the u32/u16
// retyping that won fn_8000F68C / fn_8009DC9C does NOT apply (no hash switch);
// this one needs the prototype pass first.
//
// family=m2c range=0x80011454-0x80011994 size=1344B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 4.8% ([11]rev->4.8%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80017C10(void *, void *);
s32 fn_80010808(s32, s32, s32, s32);
// FLAG: -fno-expensive-optimizations
extern char lbl_80290628[];
extern char lbl_802FFE98[];
extern s32 lbl_802FFEE8;
extern s32 lbl_802FFEEC;
void *fn_80011454(s32 *arg0, s32 arg1, s32 arg2) {
    s32 sp38;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp10;
    s32 spC;
    s32 sp8;
    CStruct *temp_r10_2;
    CStruct *temp_r27;
    CStruct *temp_r8;
    CStruct *temp_r8_3;
    CStruct *temp_r9_3;
    CStruct *temp_r9_5;
    s32 *var_r25;
    s32 *var_r27;
    s32 *var_r28;
    s32 *var_r30;
    s32 *var_r31_2;
    s32 var_r23;
    s32 temp_r0;
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r11_2;
    s32 temp_r11_3;
    s32 temp_r11_4;
    s32 temp_r11_5;
    s32 temp_r11_7;
    s32 temp_r11_8;
    s32 temp_r26;
    s32 temp_r30;
    s32 temp_r31;
    s32 var_cr0_eq;
    s32 var_r24;
    s32 var_r27_2;
    s32 var_r28_2;
    s8 *var_r9;
    s8 var_ctr;
    s8 var_r31;
    u32 temp_r10_3;
    u32 temp_r8_2;
    u32 temp_r9;
    void *temp_r11_6;
    Unk_5AA7B5D7 *temp_r30_2;
    void *temp_r31_2;
    void *temp_r3;
    void *temp_r7;
    void *temp_r9_2;
    Unk_C7387A53 *temp_r9_4;
    Unk_C7387A53 *temp_r9_6;

    sp38 = 0;
    fn_80010400(*(s32 *)&lbl_802FFE98, QB_TEAMMATEPRO, 0, 0x80300000);
    if (((s32) ((CStruct *)arg0)->unk0x8C != 0) || (var_r23 = 1, ((arg2 == 0) != 0))) {
        var_r23 = 0;
    }
    var_r28 = NULL;
    var_r31_2 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x40) + 0x1C);
    var_r27 = NULL;
    var_r25 = NULL;
    temp_r26 = (arg1 + 3) & QB_UNKNOWN_0xFFFFFFFC;
    temp_r30 = 1 << fn_80010E8C(arg0, arg0);
    var_r24 = temp_r26;
    var_cr0_eq = var_r31_2 == NULL;
    if (var_cr0_eq == 0) {
        temp_r10 = lbl_802FFEEC;
        do {
            temp_r11 = var_r31_2 + *(s32 *)&lbl_80290628;
            temp_r9 = (u32) *((u32 *)&((CStruct *)var_r31_2)->unk0x8) >> 8U;
            if (temp_r9 >= (u32) (temp_r26 + (((temp_r11 - 1 + temp_r30) & -temp_r30) - temp_r11))) {
                if (temp_r10 != 0) {
                    if (var_r31_2 == temp_r10) {
                        goto block_11;
                    }
                } else if ((var_r28 == NULL) || ((u32) ((u32) *((u32 *)&((Unk_AA2D2650_2 *)var_r28)->unk0x8) >> 8U) > temp_r9)) {
block_11:
                    var_r25 = var_r27;
                    var_r28 = var_r31_2;
                }
            }
            var_r27 = var_r31_2;
            var_r31_2 = ((CStruct *)var_r31_2)->unk0x0;
            var_cr0_eq = var_r31_2 == NULL;
        } while (var_cr0_eq == 0);
    }
    0;
    if (var_cr0_eq == 0) {
        temp_r9_2 = var_r28 + *(s32 *)&lbl_80290628;
        var_r31 = ((s32) ((s32)(s32)(s32)temp_r9_2 - 1 + temp_r30) & -temp_r30) - (s32)temp_r9_2;
        if (var_r25 != NULL) {
            *((s32 *)var_r25) = ((Unk_AA2D2650_2 *)var_r28)->unk0x0;
        } else {
            *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x40) + 0x1C) = (s32 *) ((Unk_AA2D2650_2 *)var_r28)->unk0x0;
        }
        ((Unk_AA2D2650_2 *)var_r28)->unk0x0 = arg0;
        temp_r9_3 = arg0 + 0x10;
        temp_r27 = arg0 + 4;
        sp1C = temp_r9_3->unk0x4;
        sp18 = ((CStruct *)arg0)->unk0x10;
        sp20 = temp_r9_3->unk0x8;
        fn_80011E00(temp_r9_3, 1);
        sp8 = sp18;
        spC = sp1C;
        sp10 = sp20;
        sp28 = ((CStruct *)arg0)->unk0x4;
        sp2C = temp_r27->unk0x4;
        sp30 = temp_r27->unk0x8;
        fn_80011DE0(temp_r27, 1);
        temp_r10_2 = arg0 + 0x28;
        temp_r8 = arg0 + 0x1C;
        sp8 = sp28;
        spC = sp2C;
        sp10 = sp30;
        temp_r10_2->unk0x4 = (s32) (temp_r10_2->unk0x4 - ((u32) *((u32 *)&((Unk_AA2D2650_2 *)var_r28)->unk0x8) >> 8U));
        temp_r11_2 = *((u32 *)&temp_r8->unk0x4) + ((u32) *((u32 *)&((Unk_AA2D2650_2 *)var_r28)->unk0x8) >> 8U);
        *((u32 *)&temp_r8->unk0x4) = temp_r11_2;
        if (temp_r11_2 > (s32) temp_r8->unk0x8) {
            temp_r8->unk0x8 = temp_r11_2;
        }
        temp_r10_3 = *((u32 *)&((Unk_AA2D2650_2 *)var_r28)->unk0x8);
        temp_r11_3 = *(s32 *)&lbl_80290628;
        temp_r8_2 = temp_r10_3 >> 8U;
        temp_r7 = var_r28 + temp_r11_3 + temp_r26;
        temp_r30_2 = temp_r7 + var_r31;
        temp_r11_4 = ((temp_r8_2 - temp_r26) - temp_r11_3) - var_r31;
        if (temp_r11_4 > 0) {
            *((u32 *)&((Unk_AA2D2650_2 *)var_r28)->unk0x8) = (u32) ((temp_r10_3 & ~QB_UNKNOWN_0xFFFFFF00) | (temp_r26 << 8));
            temp_r30_2->unk0x8 = (s32) ((temp_r30_2->unk0x8 & ~QB_UNKNOWN_0xFFFFFF00) | (temp_r11_4 << 8));
            *(s32 *)((char *)temp_r30_2 + (s32)0xB) = 0;
            *((s32 *)temp_r7 + (s32)var_r31) = arg0;
            temp_r11_5 = temp_r27->unk0x8;
            sp1C = temp_r27->unk0x4;
            sp18 = ((CStruct *)arg0)->unk0x4;
            sp20 = temp_r11_5;
            fn_80011DE0(temp_r27, 1);
            spC = sp1C;
            sp10 = temp_r11_5;
            sp8 = sp18;
            temp_r9_4 = ((CStruct *)arg0)->unk0x80;
            ((s32 (*)(void *, void *))temp_r9_4->unk0x4C)(arg0 + temp_r9_4->unk0x48, temp_r30_2);
        } else {
            *((u32 *)&((Unk_AA2D2650_2 *)var_r28)->unk0x8) = (u32) ((temp_r10_3 & ~QB_UNKNOWN_0xFFFFFF00) | ((temp_r8_2 - var_r31) << 8));
        }
        goto block_29;
    }
    var_r28 = fn_80010808(((CStruct *)arg0)->unk0x34, arg0, temp_r26 + temp_r31, var_r23);
    temp_r31 = *(s32 *)&lbl_80290628;
    if ((s32) ((CStruct *)arg0)->unk0x38 == 1) {
        temp_r11_6 = var_r28 + temp_r31;
        var_r31 = ((s32) ((s32)(s32)(s32)temp_r11_6 - 1 + temp_r30) & -temp_r30) - (s32)temp_r11_6;
        fn_80010808(((CStruct *)arg0)->unk0x34, arg0, var_r31, var_r23);
    } else {
        var_r31 = (s32) (var_r28 + temp_r31) & ~-temp_r30;
        if (var_r31 != 0) {
            var_r24 = temp_r26 + var_r31;
            var_r28 = fn_80010808(((CStruct *)arg0)->unk0x34, arg0, var_r31, var_r23);
            var_r31 = 0;
        }
    }
    0;
    if (0) {
        ((Unk_AA2D2650_2 *)var_r28)->unk0x0 = arg0;
        temp_r9_5 = arg0 + 4;
        *((u32 *)&((Unk_AA2D2650_2 *)var_r28)->unk0x8) = (s32) ((*((u32 *)&((Unk_AA2D2650_2 *)var_r28)->unk0x8) & ~QB_UNKNOWN_0xFFFFFF00) | (var_r24 << 8));
        *(s32 *)((char *)var_r28 + (s32)0xB) = 0;
        temp_r11_7 = temp_r9_5->unk0x4;
        temp_r0 = ((CStruct *)arg0)->unk0x4;
        sp1C = temp_r11_7;
        sp18 = temp_r0;
        sp20 = temp_r9_5->unk0x8;
        fn_80011DE0(temp_r9_5, 1);
        temp_r8_3 = arg0 + 0x1C;
        sp8 = temp_r0;
        spC = temp_r11_7;
        sp10 = sp20;
        temp_r11_8 = temp_r8_3->unk0x4 + (var_r24 + *(s32 *)&lbl_80290628 + var_r31);
        temp_r8_3->unk0x4 = temp_r11_8;
        if (temp_r11_8 > (s32) temp_r8_3->unk0x8) {
            temp_r8_3->unk0x8 = temp_r11_8;
        }
block_29:
        if (0) {
            fn_80010764(var_r28);
            *(s32 *)((char *)var_r28 + (s32)0xB) = var_r31;
            var_r9 = var_r28 + *(s32 *)&lbl_80290628;
            if (var_r31 > 0) {
                var_ctr = var_r31;
                do {
                    *((s32 *)var_r9) = var_r31;
                    var_r9 += 1;
                    var_ctr -= 1;
                } while (var_ctr != 0);
            }
            0;
            return var_r28 + *(s32 *)&lbl_80290628 + var_r31;
        }
        goto block_35;
    }
block_35:
    if (((s32) ((CStruct *)arg0)->unk0x8C != 0) && (lbl_802FFEE8 == 0)) {
        var_r27_2 = 0;
        lbl_802FFEE8 = 1;
        var_r30 = arg0 + 0xA4;
        var_r28_2 = 0;
loop_38:
        temp_r31_2 = *((s32 *)((char *)arg0 + (s32)0x90 + (s32)var_r28_2));
        if ((temp_r31_2 == NULL) || (MemAvailable(((Unk_C7387A53 *)temp_r31_2)->unk0x34) <= (void *) (*((s32 *)var_r30) + arg1)) || (temp_r9_6 = ((Unk_C7387A53 *)temp_r31_2)->unk0x80, temp_r3 = ((s32 (*)(void *, void *, s32))temp_r9_6->unk0x24)(temp_r31_2 + temp_r9_6->unk0x20, arg1, 0), ((temp_r3 == NULL) != 0))) {
            var_r27_2 += 1;
            var_r30 += 4;
            var_r28_2 += 4;
            if (var_r27_2 > 4) {
                lbl_802FFEE8 = 0;
                goto block_43;
            }
            goto loop_38;
        }
        lbl_802FFEE8 = 0;
        0;
        return temp_r3;
    }
block_43:
    if (arg2 != 0) {
        fn_800723F0(arg0, arg1, arg2, var_r24, ((CStruct *)arg0)->unk0x44);
        fn_80017C10(var_r24, ((CStruct *)arg0)->unk0x44);
        ScriptDumpHeaps(0, 0);
    }
    0;
    return NULL;
}