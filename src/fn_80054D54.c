// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054D54-0x80054DC4 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
CStruct *fn_80054E1C(void);
void fn_80054C6C(CStruct *arg0, s32 arg1);
void fn_80054950(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
bool fn_80054D54(s32 arg0) {
    s32 temp_r29;
    s32 temp_r30;
    CStruct *temp_r3;

    temp_r3 = fn_80054E1C();
    if (temp_r3 != NULL) {
        temp_r29 = temp_r3->unk0x8C;
        temp_r30 = temp_r3->unk0x84;
        fn_80054C6C(temp_r3, 1);
        fn_80054950(arg0, temp_r30, temp_r29 ^ 1, temp_r29, 0, 0);
        return true;
    }
    return false;
}
