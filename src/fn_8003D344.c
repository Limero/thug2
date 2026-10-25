// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003D344-0x8003D404 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern CStruct *lbl_803003F0;
void *Mem_Alloc2(s32 size);
void Mem_Free(void *p);
s32 fn_8003AB44(s32 arg0);
void fn_80032088(s32 arg0);
s32 fn_8012865C(CStruct *arg0, s32 arg1, CStruct *arg2, s32 arg3);
s32 *fn_8012ED98(void);
void fn_8012F1A8(CStruct *arg0, CStruct *arg1, s32 arg2, CStruct *arg3);
s32 fn_801309EC(void *arg0);
void fn_8012EE64(void *arg0, s32 arg1);
bool fn_8003D344(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r31;
    CStruct *temp_r3_2;

    temp_r31 = fn_8003AB44(lbl_803003F0);
    if (temp_r31 != 0) {
        temp_r3_2 = Mem_Alloc2(8);
        temp_r3_2->unk0x0 = 0;
        temp_r3_2->unk0x4 = 0;
        if (fn_8012865C(temp_r31, arg2, temp_r3_2, 0) != 0) {
            fn_80032088(0xF8);
            temp_r31 = fn_8012ED98();
            fn_8012F1A8(temp_r31, temp_r3_2, 0, lbl_803003F0);
            do {

            } while (fn_801309EC(temp_r31) != 0);
            if (temp_r31 != 0) {
                fn_8012EE64(temp_r31, 3);
            }
        }
        Mem_Free(temp_r3_2);
    }
    return true;
}
