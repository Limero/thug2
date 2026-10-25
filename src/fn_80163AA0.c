// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80163AA0-0x80163AEC (76B). Byte-identical.
#include "types.h"
extern char lbl_80305EC0[];
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(CStruct *, void *, void *);
s32 fn_80198E4C(void *);
bool ScriptGetFireballLevel(void *arg0, CScript *arg1) {
    s32 temp_r30;

    temp_r30 = arg1->unk0x18;
    AddInteger(temp_r30, QB_LEVEL, fn_80198E4C(*(s32 *)&lbl_80305EC0));
    return true;
}
