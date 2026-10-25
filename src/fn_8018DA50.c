// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018DA50-0x8018DC98 (584B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8012720C(CStruct *, void *);
void AddInteger(CStruct *, void *, void *);
s32 AddChecksum(CStruct *, void *, void *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 GetArray(CStruct *, void *, s32 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 fn_80129528(CStruct *, void *);
s32 Script_SpawnScript(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
s32 fn_8018BFB4(Unk_C7387A53 *);
s32 fn_8018C068(Unk_C7387A53 *, void *);
s32 fn_8018D0F8(Unk_C7387A53 *);
s32 fn_8018D614(Unk_C7387A53 *, void *, void *, void *);
s32 fn_8018DA50(Unk_C8FEE62D *);
s32 fn_8018E24C(void *);
bool fn_8018DA50(Unk_C8FEE62D *arg0) {
    void *sp10;
    s32 sp14;
    s32 sp18;
    s32 spBoth;
    s32 temp_r30;
    s32 temp_r3;
    u32 var_r29;

    if (GetArray(arg0->unk0x20, QB_TOUR_SPOTS, (void **) &sp10, 0) == 0) {
        GetArray(arg0->unk0x20, QB_HORSE_SPOTS, (void **) &sp10, 1);
    }
    var_r29 = 0;
    if (var_r29 < (u32) *((u32 *) ((char *) sp10 + 4))) {
        spBoth = 0;
    loop_4:
        temp_r30 = fn_80129528(sp10, var_r29);
        {
            register s32 p14 __asm__("r9");
            p14 = (s32) &sp14;
            GetChecksum_2(temp_r30, QB_FLAG, (s32 *) p14, 1);
        }
        if (fn_8018D614(arg0, sp14, 1, 0) == 0) {
            fn_8018D0F8(arg0);
            GetInteger(temp_r30, QB_TIME, (s32 *) &sp18, 1);
            if (ContainsFlag(arg0->unk0x20, QB_CUMULATIVE_TIMER) != 0) {
                fn_8018C068(arg0, sp18);
            } else {
                AddInteger(arg0->unk0x20, QB_TIME, sp18);
                fn_8018BFB4(arg0);
            }
            AddChecksum(temp_r30, QB_GOAL_ID, fn_8018E24C(arg0));
            if ((s32) arg0->unk0x60 == 0) {
                AddChecksum(temp_r30, 0, QB_FIRST_SPOT);
            }
            if (ContainsFlag(arg0->unk0x20, QB_QUICK_START) != 0) {
                AddChecksum(temp_r30, 0, QB_QUICK_START);
            } else {
                fn_8012720C(temp_r30, QB_QUICK_START);
            }
            temp_r3 = ContainsFlag(arg0->unk0x20, QB_HORSE);
            if (temp_r3 != 0) {
                Script_SpawnScript(QB_GOAL_HORSE_NEXT_SPOT, temp_r30, 0, 0, 0, 0, 0, 0,
                            spBoth, spBoth);
            } else {
                Script_SpawnScript(QB_GOAL_TOUR_NEXT_SPOT, temp_r30, 0, 0, 0, 0, 0, 0,
                            temp_r3, temp_r3);
            }
            fn_8012720C(temp_r30, QB_QUICK_START);
        } else {
            var_r29 += 1;
            if (var_r29 < (u32) *((u32 *) ((char *) sp10 + 4))) {
                goto loop_4;
            }
        }
    }
    return true;
}
