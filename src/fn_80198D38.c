// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198D38-0x80198D70 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_80198D38(s32 arg0) {
    s32 sp8;

    fn_80128C80(arg0 + 4, QB_MAX_PLAYERS, &sp8, 1);
    return sp8;
}
