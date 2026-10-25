// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113A38-0x80113A5C (36B). Byte-identical.
#include "types.h"
#include "structs.h"
// ScriptStopMusic @ 0x80113A38
bool ScriptStopMusic(CStruct *pParams, CScript *pScript) {
    StopMusic();
    return true;
}
