// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161CAC-0x80161D5C (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800168B0(void *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
bool ScriptObjectExists(s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_800168B8(void);
void CStruct_delete(CStruct *, s32);

bool ScriptLobbyCheckKeyboard(CStruct *pParams, CScript *pScript) {
    u8 sp8[256];
    s32 temp_r31;

    if ((fn_800168B0(sp8) > 0) && (sp8[0] == 0x20)) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        AddChecksum(temp_r31, QB_ID, QB_KEYBOARD_ANCHOR);
        if (ScriptObjectExists(temp_r31, 0) == 0) {
            Script_RunScript(QB_LOBBY_ENTER_KB_CHAT, 0, 0, 0, 0);
            fn_800168B8();
        }
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
    return true;
}
