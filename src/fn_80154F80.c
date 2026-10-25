// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154F80-0x80154FE0 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305F9C[];
extern s32 fn_8021E024(void *);
extern s32 fn_8013FF5C(s32, s32);
extern s32 fn_80128E34(CStruct *, void *, void *, s32);

bool ScriptUsingDefaultMasterServers(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80128E34(fn_8013FF5C(fn_8021E024(*(s32 *)&lbl_80305F9C), QB_USE_DEFAULT_MASTER_SERVERS), QB_CHECKSUM, &sp8, 1);
    return ((sp8 ^ QB_BOOLEAN_TRUE) == 0);
}
