// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015DAFC-0x8015DB48 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(CStruct *, void *, void *);
s32 fn_801A5CE8(Unk_C7387A53 *);
extern char lbl_80305EFC[];
bool ScriptGetCurrentSkaterProfileIndex(void *arg0, CScript *arg1) {
    s32 temp_r5;
    temp_r5 = fn_801A5CE8(*(s32 *)&lbl_80305EFC);
    AddInteger(arg1->unk0x18, QB_CURRENTSKATERPROFILEINDEX, temp_r5);
    return true;
}
