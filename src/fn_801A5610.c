// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5610-0x801A568C (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80128E34(CStruct *, void *, void *, s32);
void fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_801A5610(s32 arg0, s32 arg1) {
    s32 sp8;

    sp8 = 0;
    if (arg1 != QB_STANCE) {
        if (arg1 == QB_PUSHSTYLE) {
            fn_80128E34(arg0 + 0x6C, QB_PUSHSTYLE, &sp8, 1);
        }
    } else {
        fn_80128E34(arg0 + 0x6C, QB_STANCE, &sp8, 1);
    }
    return sp8;
}
