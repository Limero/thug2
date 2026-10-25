// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155198-0x801551EC (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A7F60[];
s32 ContainsFlag(CStruct *, void *);
s32 fn_80128A90(CStruct *, void *);
bool ScriptDumpScripts(CStruct *pParams, CScript *pScript) {
    if (fn_80128A90(pParams, (void *)lbl_802A7F60) == 0) {
        ContainsFlag(pParams, QB_SHOW_OBJECTS);
        fn_80131D18();
    }
    return true;
}
