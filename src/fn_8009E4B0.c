// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E4B0-0x8009E574 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void CStruct_delete(CStruct *, s32);
s32 fn_8012729C(CStruct *);
void fn_8012720C(CStruct *, s32);
void fn_801270B4(CStruct *, s32);
s32 GetChecksum(CStruct *, s32);
void fn_8009E4B0(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 temp_r3;
    u32 var_r31;

    if (arg0->unk0x24 != NULL) {
        if (arg1 != NULL) {
            for (var_r31 = 0; var_r31 < (u32) arg1->unk0x4; var_r31++) {
                temp_r3 = GetChecksum(arg1, var_r31);
                fn_801270B4(arg0->unk0x24, temp_r3);
                fn_8012720C(arg0->unk0x24, temp_r3);
            }
            if (fn_8012729C(arg0->unk0x24) != 0) {
                if (arg0->unk0x24 != NULL) {
                    CStruct_delete(arg0->unk0x24, 3);
                }
                arg0->unk0x24 = NULL;
            }
        } else {
            CStruct_delete(arg0->unk0x24, 3);
            arg0->unk0x24 = arg1;
        }
    }
}

