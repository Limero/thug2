// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155C88-0x80155CD4 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(CStruct *, void *, void *);
s32 fn_80198BE8(void *);
extern char lbl_80305EC0[];
bool ScriptGetTimeLimit(void *arg0, CScript *arg1) {
    s32 temp_r5;
    temp_r5 = fn_80198BE8(*(s32 *)&lbl_80305EC0);
    AddInteger(arg1->unk0x18, QB_TIME_LIMIT,  temp_r5);
    return true;
}
