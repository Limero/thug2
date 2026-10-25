// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155C48-0x80155C64 (28B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
// ScriptToggleRails @ 0x80155C48
bool ScriptToggleRails(CStruct *pParams, CScript *pScript) {
    Unk_1E29BE92 *temp_r11;

    temp_r11 = *(void * *)&lbl_80305EAC;
    temp_r11->unk0x424 = (s32) (temp_r11->unk0x424 ^ 1);
    return true;
}
