// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155F68-0x80155FC4 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void * lbl_80305DE4;
bool ScriptStopSecondControllerCheck(CStruct *pParams, CScript *pScript) {
    CScript *temp_r11;
    Unk_4E705049 *temp_r9;

    temp_r11 = lbl_80305DE4;
    if (temp_r11 != NULL) {
        temp_r9 = *((void * *)&temp_r11->unk0x18);
        ((void (*)(void *, s32))temp_r9->unk0x1C)((char *)temp_r11 + temp_r9->unk0x18, 3);
    }
    lbl_80305DE4 = NULL;
    return true;
}
