// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234DA8-0x80234DDC (52B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(CStruct *, void *, void *);
bool ScriptGetEditorMaxThemes(void *arg0, CScript *arg1) {
    AddInteger(arg1->unk0x18, QB_MAX_THEMES, 5);
    return true;
}
