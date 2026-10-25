// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018DCC8-0x8018DE04 (316B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F1C;
extern char lbl_802A9634[];

s32 GetArray(CStruct *, u32, s32 *, s32);
s32 fn_80129528(CStruct *, s32);
s32 GetChecksum_4(CStruct *, void *, void *, s32);
s32 GetInteger(CStruct *, u32, s32 *, s32);
s32 fn_801A9270(s32, s32, s32);
s32 GetChecksum_2(CStruct *, u32, s32 *, s32);

void fn_8018DCC8(Unk_C8FEE62D *arg0, s32 arg1, s32 arg2) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 temp_r31;
    s32 var_r30;

    GetArray(arg0->unk0x20, QB_KILL_CLUSTERS, &sp8, 1);
    var_r30 = 0;
    if ((u32)var_r30 < *((u32 *)&((CStruct *)sp8)->unk0x4)) {
        do {
            temp_r31 = fn_80129528(sp8, var_r30);
            GetChecksum_4(temp_r31, (s32)lbl_802A9634, &spC, 1);
            if (GetInteger(temp_r31, QB_SCORE, &sp10, 0) == 0) {
                GetInteger(arg0->unk0x20, QB_SCORE, &sp10, 1);
            }
            if ((spC == arg1) && (arg2 > sp10)) {
                fn_801A9270(lbl_80305F1C, arg1, 0);
                GetChecksum_2(temp_r31, QB_FLAG, &sp14, 1);
                ((s32 (*)(void *, s32, s32, s32))*(s32 *)((char *)*((s32 * *)&arg0->unk0x14) + 0xA4))(
                    (char *)arg0 + *(s16 *)((char *)*((s32 * *)&arg0->unk0x14) + 0xA0), sp14, 1, 0);
                return;
            }
            var_r30++;
        } while ((u32)var_r30 < *((u32 *)&((CStruct *)sp8)->unk0x4));
    }
}
