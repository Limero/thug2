// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80167C08-0x80167E04 (508B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
register s32 r31_guard __asm__("r31");
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 s_first_date_is_more_recent(CStruct *arg0, CStruct *arg1) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r3;

    sp8 = 0;
    spC = 0;
    sp10 = 0;
    sp14 = 0;
    sp18 = 0;
    sp1C = 0;
    GetInteger(arg0, QB_YEAR, &sp8, 0);
    GetInteger(arg0, QB_MONTH, &spC, 0);
    GetInteger(arg0, QB_DAY, &sp10, 0);
    GetInteger(arg0, QB_HOUR, &sp14, 0);
    GetInteger(arg0, QB_MINUTES, &sp18, 0);
    GetInteger(arg0, QB_SECONDS, &sp1C, 0);
    sp20 = 0;
    sp24 = 0;
    sp28 = 0;
    sp2C = 0;
    sp30 = 0;
    sp34 = 0;
    GetInteger(arg1, QB_YEAR, &sp20, 0);
    GetInteger(arg1, QB_MONTH, &sp24, 0);
    GetInteger(arg1, QB_DAY, &sp28, 0);
    GetInteger(arg1, QB_HOUR, &sp2C, 0);
    GetInteger(arg1, QB_MINUTES, &sp30, 0);
    GetInteger(arg1, QB_SECONDS, &sp34, 0);
    var_r3 = 0;
    if ((sp8 >= sp20) && ((sp8 > sp20) || ((spC >= sp24) && ((spC > sp24) || ((sp10 >= sp28) && ((sp10 > sp28) || ((sp14 >= sp2C) && ((sp14 > sp2C) || ((sp18 >= sp30) && ((sp18 > sp30) || ((sp1C >= sp34) && (sp1C > sp34)))))))))))) {
        var_r3 = 1;
    }
    return var_r3;
}
