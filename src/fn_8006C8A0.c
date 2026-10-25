// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006C8A0-0x8006CB04 (612B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"

float fn_800144C8(void);
void fn_8006F014(CStruct *);
s32 fn_8006F028(CStruct *, s32 *);
void fn_8006F0E4(CStruct *, s32 *);

extern s32 lbl_80300460;
extern void* lbl_80301428;

typedef struct Unk_8006C8A0_18 {
    char pad0x0[0x4];
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    s32 unk10;
    f32 unk14;
    f32 unk18;
} Unk_8006C8A0_18;

void fn_8006C8A0(void) {
    struct { s32 v; char _pad[28]; } sp8f;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f30;
    void *var_r22;
    Unk_8006C8A0_18 *var_r31;

    temp_f30 = fn_800144C8();
    if (lbl_80301428 != 0) {
        fn_8006F014(lbl_80301428);
        var_r31 = fn_8006F028(lbl_80301428, 0);
        if (var_r31 != NULL) {
            do {
                var_r22 = NULL;
                if ((*(volatile s32 *)&lbl_80300460 == 0) || (var_r31->unk10 & 8)) {
                    temp_f0 = var_r31->unk18 - temp_f30;
                    var_r31->unk18 = temp_f0;
                    if (temp_f0 > 0.0f) {
                        temp_f10 = temp_f0 / var_r31->unk14;
                        var_r31->unkC = (s8)(var_r31->unk8 + (s32)(((f32)(f64)var_r31->unk4 - (f32)(f64)var_r31->unk8) * temp_f10));
                        var_r31->unkD = (s8)(var_r31->unk9 + (s32)(((f32)(f64)var_r31->unk5 - (f32)(f64)var_r31->unk9) * temp_f10));
                        var_r31->unkE = (s8)(var_r31->unkA + (s32)(((f32)(f64)var_r31->unk6 - (f32)(f64)var_r31->unkA) * temp_f10));
                        var_r31->unkF = (s8)(var_r31->unkB + (s32)(((f32)(f64)var_r31->unk7 - (f32)(f64)var_r31->unkB) * temp_f10));
                    } else {
                        var_r22 = var_r31;
                    }
                }
                var_r31 = fn_8006F028(lbl_80301428, 0);
                if (var_r22 != NULL) {
                    sp8f.v = var_r22;
                    fn_8006F0E4(lbl_80301428, &sp8f.v);
                    Mem_Free(var_r22);
                }
            } while (var_r31 != NULL);
        }
    }
}
