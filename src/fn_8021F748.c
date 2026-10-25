// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021F748-0x8021F78C (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8021E024(void);
s32 fn_8013FF5C(s32, s32);
void fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_8021F748(s32 arg0) {
    s32 sp8;

    fn_80128E34(fn_8013FF5C(fn_8021E024(), QB_LEVEL), QB_CHECKSUM, &sp8, 1);
    return sp8;
}
