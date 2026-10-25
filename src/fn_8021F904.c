// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021F904-0x8021F964 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_8021E024(void *);
extern s32 fn_8013FF5C(s32, s32);
extern s32 fn_80128E34(CStruct *, void *, void *, s32);

s32 fn_8021F904(void *arg0) {
    s32 sp8;

    sp8 = 0;
    fn_80128E34(fn_8013FF5C(fn_8021E024(arg0), QB_SHOW_NAMES), QB_CHECKSUM, &sp8, 0);
    return ((sp8 ^ QB_BOOLEAN_TRUE) == 0);
}
