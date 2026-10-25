// WIP DRAFT (concrete attempt;)
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 10.6667% -> 13.1579% per-object flags: -Os -> -fno-schedule-insns
// family=m2c range=0x80116EC0-0x80116FCC size=268B
// PARKED: script-dump candidate scored 4.9%; stack buffer/global formatting helper scheduling differs.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 7.3% ([0]rev->7.3%).
// FLAG: -fno-schedule-insns
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 10.7%.
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(s32, s32, s32);
s32 ScriptDump(CScript *arg1) {
    s32 sp408;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;
    CStruct *temp_r30_2;
    GetChecksum_2(0, &sp408, 1);
    CStruct_new(8);
    temp_r3 = fn_801288C4(arg1->unk0x18, sp408);
    temp_r31 = CStruct_ctor();
    if (temp_r3 == 0) {
        sprintf(&sp8, fn_80126698(sp408));
    } else {
        sprintf(&sp8, fn_80126698(sp408));
        fn_8009F4C4(0x10);
        temp_r30_2 = fn_801252BC();
        fn_80126808(temp_r3);
        temp_r30_2->unk0x4 = QB_A;
        fn_80127438(temp_r31, temp_r30_2);
    }
    AddString(temp_r31, 0, &sp8);
    temp_r30 = ScriptPrintf(temp_r31, arg1);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return temp_r30;
}
