// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234D18-0x80234D60 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80238964(void);
void AddInteger(CStruct *, s32, void *);
void *fn_80235CB4(void);
// ScriptGetEditorTheme @ 0x80234D18
bool ScriptGetEditorTheme(void *arg0, CScript *arg1) {
    s32 temp_r30;

    temp_r30 = arg1->unk0x18;
    fn_80238964();
    AddInteger((void *)temp_r30, QB_THEME, fn_80235CB4());
    return true;
}
