// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016A258-0x8016A2BC (100B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8016A320();                                  

s32 fn_8016A3B0();                                  
s32 fn_8016A3DC();                                  

// ScriptSwitchToTempPoolsIfTheyExist @ 0x8016A258
bool ScriptSwitchToTempPoolsIfTheyExist(CStruct *pParams, CScript *pScript) {
    fn_8016A30C();
    fn_8016A34C();
    fn_8016A360();
    if ((fn_8016A320() != 0) && (fn_8016A3B0() != 0) && (fn_8016A3DC() != 0)) {
        return true;
    }
    fn_8016A374();
    fn_8016A388();
    fn_8016A39C();
    return false;
}
