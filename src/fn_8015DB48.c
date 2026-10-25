// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015DB48-0x8015DBA0 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EFC;
extern s32 fn_801A5DAC(s32 arg0, s32 arg1);
extern s32 fn_801A5848(s32 arg0);
extern s32 AddString(CStruct * arg0, s32 arg1, void * arg2);
bool ScriptGetCustomSkaterName(void *arg0, CScript *arg1) {
    s32 temp_r5;
    temp_r5 = fn_801A5848(fn_801A5DAC(lbl_80305EFC, QB_CUSTOM));
    AddString(arg1->unk0x18, QB_DISPLAY_NAME, temp_r5);
    return true;
}
