// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80181C78-0x80181DA0 (296B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void *fn_80182F98(CStruct * arg0, s32 arg1);
s32 GetStructure(s32 arg0, s32 arg1);
s32 fn_801259C8(s32 arg0, s32 arg1);
s32 fn_80129528(CStruct * arg0, s32 arg1);
s32 GetStructure_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
void GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
s32 fn_801281BC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 Script_GenerateCRC(s32 arg0);
s32 fn_801819E4(Unk_FFAD6788 * arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 fn_80181C78(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 var_r30;

    var_r30 = arg0->unk0x68;
    for (;;) {
        if (var_r30 <= 0) {
            return 0;
        }
        var_r30 -= 1;
        if (*(u8 *)((char *)fn_80182F98((char *)arg0 + 0x54, var_r30) + (s32)0x1C) != 0) {
            break;
        }
    }
    if (arg4 > 1) {
        GetStructure_2(GetStructure(arg1, 1), QB_PARAMS, &sp8, 1);
        arg1 = arg4;
        do {
            arg1 -= 1;
            GetChecksum_2(sp8, QB_EXTRATRICKS, &spC, 0);
            GetStructure_2(fn_80129528(fn_801259C8(spC, 1), 0), QB_PARAMS, &sp8, 1);
        } while (arg1 > 1);
        fn_801281BC(sp8, QB_NAME, &sp10, 1);
        arg1 = Script_GenerateCRC(sp10);
    }
    return fn_801819E4(arg0, var_r30, arg1, arg2, arg3);
}
