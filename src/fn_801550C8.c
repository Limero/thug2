// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801550C8-0x8015512C (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305F9C;
s32 fn_8021E024(void *);
s32 fn_8013FF5C(s32, s32);
s32 fn_80128E34(CStruct *, void *, void *, s32);

bool ScriptDeviceChosen(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80128E34(fn_8013FF5C(fn_8021E024(lbl_80305F9C), QB_DEVICE_TYPE), QB_CHECKSUM, &sp8, 1);
    return sp8 != QB_DEVICE_NONE;
}
