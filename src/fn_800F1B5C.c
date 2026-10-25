// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F1B5C-0x800F1C34 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetArray(CStruct *, s32, void *, s32);
CStruct *fn_80129528(CStruct *, s32);
CStruct *fn_801293FC(CStruct *, s32);
CStruct *fn_800F0AFC(CStruct *);
void fn_80129260(CStruct *, s32, s32);
void fn_80129114(CStruct *, s32);
void fn_800F1B5C(s32 arg0, CStruct *arg1) {
    CStruct *sp8;
    u32 var_r31;
    s32 temp_r27;
    s32 temp_r30;
    CStruct *temp_r3;
    CStruct *temp_r4;
    u32 var_r31_2;
    var_r31 = 0U;
    temp_r27 = arg1->unk0x4;
    if (var_r31 < (u32) temp_r27) {
        do {
            temp_r3 = fn_80129528(arg1, var_r31);
            sp8 = 0;
            if (GetArray(temp_r3, QB_LINKS, &sp8, 0) != 0) {
                temp_r30 = sp8->unk0x4;
                if (temp_r30 != 0) {
                    var_r31_2 = 0U;
                    if (var_r31_2 < (u32) temp_r30) {
                        do {
                            temp_r4 = fn_800F0AFC(fn_80129528(arg1, (s32)fn_801293FC(sp8, var_r31_2)));
                            fn_80129260(sp8, var_r31_2, (s32)temp_r4);
                            var_r31_2 += 1;
                        } while (var_r31_2 < (u32) temp_r30);
                    }
                    fn_80129114(sp8, 0xd);
                }
            }
            var_r31 += 1;
        } while (var_r31 < (u32) temp_r27);
    }
}
