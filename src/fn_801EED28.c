// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EED28-0x801EF0A0 (888B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802ADC64;

f32 fn_801EF3A8(Unk_C7387A53 *, s32 *);
f32 fn_801EF44C(Unk_C7387A53 *, s32 *);
extern s32 CStruct_new(s32);
void *CStruct_ctor(void *);
void AddChecksum(CStruct *, s32, s32);
void AddInteger(CStruct *, s32, s32);
void fn_8009F010(s32, s32, void *);
void CStruct_delete(CStruct *, s32);

void fn_801EED28(Unk_DB0E2BAB *arg0) {
    union { u64 d; s32 w[2]; char _p[16]; } sp8;
    register f32 var_f31 __asm__("fr31");
    void *temp_r31;
    void *outp;

    var_f31 = lbl_802ADC64;
    if (*((f32 *)&arg0->unk0x1C) != var_f31) {
        outp = &sp8;
        var_f31 = fn_801EF3A8(arg0, outp);
        if (var_f31 <= *((f32 *)&arg0->unk0x1C)) {
            temp_r31 = CStruct_ctor((void *)CStruct_new(8));
            AddChecksum(temp_r31, QB_COLOBJID, sp8.w[0]);
            AddInteger(temp_r31, QB_INTID, sp8.w[0]);
            fn_8009F010(arg0->unk0xC, QB_OBJECTINRADIUS, temp_r31);
            if (!(*(s32 *)(arg0->unk0xC + 0xC) & 1)) {
                fn_8009F010(arg0->unk0xC, QB_ANYOBJECTINRADIUS, temp_r31);
            }
            if (temp_r31 != NULL) {
                CStruct_delete(temp_r31, 3);
            }
        } else {
            if (fn_801EF44C(arg0, &sp8) <= *((f32 *)&arg0->unk0x1C)) {
                temp_r31 = CStruct_ctor((void *)CStruct_new(8));
                AddChecksum(temp_r31, QB_COLOBJID, sp8.w[0]);
                AddInteger(temp_r31, QB_INTID, sp8.w[0]);
                fn_8009F010(arg0->unk0xC, QB_ANYOBJECTINRADIUS, temp_r31);
                if (temp_r31 != NULL) {
                    CStruct_delete(temp_r31, 3);
                }
            }
            var_f31 = lbl_802ADC64;
        }
    }
    if (*((f32 *)&arg0->unk0x20) != lbl_802ADC64) {
        if (var_f31 == lbl_802ADC64) {
            var_f31 = fn_801EF44C(arg0, &sp8);
        }
        if (var_f31 >= *((f32 *)&arg0->unk0x20)) {
            if (!(*(s32 *)(arg0->unk0xC + 0xC) & 1)) {
                temp_r31 = CStruct_ctor((void *)CStruct_new(8));
                AddChecksum(temp_r31, QB_OUTCOLOBJID, sp8.w[0]);
                AddInteger(temp_r31, QB_OUTINTID, sp8.w[0]);
                fn_8009F010(arg0->unk0xC, QB_OBJECTOUTOFRADIUS, temp_r31);
                if (temp_r31 != NULL) {
                    CStruct_delete(temp_r31, 3);
                }
            }
        }
    }
    if (*((f32 *)&arg0->unk0x24) != lbl_802ADC64) {
        if (var_f31 == lbl_802ADC64) {
            var_f31 = fn_801EF3A8(arg0, &sp8);
        }
        if (var_f31 <= *((f32 *)&arg0->unk0x24)) {
            temp_r31 = CStruct_ctor((void *)CStruct_new(8));
            AddChecksum(temp_r31, QB_COLOBJID, sp8.w[0]);
            if (!(*(s32 *)(arg0->unk0xC + 0xC) & 1)) {
                fn_8009F010(arg0->unk0xC, QB_OBJECTINAVOIDRADIUS, temp_r31);
            }
            if (temp_r31 != NULL) {
                CStruct_delete(temp_r31, 3);
            }
        }
    }
    if (*((f32 *)&arg0->unk0x28) != lbl_802ADC64) {
        if (var_f31 == lbl_802ADC64) {
            var_f31 = fn_801EF3A8(arg0, &sp8);
        }
        if (var_f31 >= *((f32 *)&arg0->unk0x28)) {
            if (!(*(s32 *)(arg0->unk0xC + 0xC) & 1)) {
                fn_8009F010(arg0->unk0xC, QB_OBJECTOUTOFAVOIDRADIUS, 0);
            }
        }
    }
    if (*((f32 *)&arg0->unk0x2C) != lbl_802ADC64) {
        if (var_f31 == lbl_802ADC64) {
            var_f31 = fn_801EF3A8(arg0, &sp8);
        }
        if (var_f31 <= *((f32 *)&arg0->unk0x2C)) {
            if (!(*(s32 *)(arg0->unk0xC + 0xC) & 1)) {
                fn_8009F010(arg0->unk0xC, QB_OBJECTINATTENTIONRADIUS, 0);
            }
        } else {
            if (!(*(s32 *)(arg0->unk0xC + 0xC) & 1)) {
                fn_8009F010(arg0->unk0xC, QB_OBJECTOUTOFATTENTIONRADIUS, 0);
            }
        }
    }
}
