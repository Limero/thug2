// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B8018-0x801B8070 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 CStruct_new(s32);
s32 CStruct_ctor(void);
void fn_80126FF4(s32, s32);
s32 fn_801B8018(void *arg0, s32 arg1) {
    s32 temp_r30;
    Unk_80577C09 *temp_r9;

    CStruct_new(8);
    temp_r30 = CStruct_ctor();
    fn_80126FF4(temp_r30, arg1);
    temp_r9 = *(Unk_80577C09 **)((char *)arg0 + 0xC);
    fn_80126FF4(temp_r30, temp_r9->unk0x24);
    return temp_r30;
}
