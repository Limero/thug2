// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80201F54-0x80202298 (836B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 fn_802010FC(Unk_BC7B49A5 *);
extern s32 fn_80174AB8(void *, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern s32 fn_801258B0(s32, s32);
extern s32 AddString(CStruct *, s32, void *);
extern void AddInteger(CStruct *, s32, s32);
extern s32 fn_801A5210(s32, void *);
extern s32 fn_801A5240(s32, s32, s32);
extern void fn_80143258(s32, s32);
extern s32 Game_GetGoalManager();
extern s32 fn_801850FC(Unk_C7387A53 *);
extern s32 CStruct_delete(CStruct *, s32);
void fn_80201F54(Unk_ABBD6FA6 *arg0) {
    char *temp_r26;
    char *p2;
    char *p3;
    s32 temp_r27;
    s32 temp_r30;
    u32 temp_r31;
    s32 var_r24;
    s32 var_r25;
    s32 var_r28;

    if (fn_802010FC(arg0) != 0) {
        var_r24 = 0;
        temp_r26 = (char *)arg0 + 0x30;
        var_r28 = 0;
        temp_r27 = fn_80174AB8(*(s32 *)&lbl_80305EAC, 0);
        var_r25 = 0x46;
        temp_r30 = CStruct_ctor(CStruct_new(8));
        do {
            if ((*(s32 *)((char *)(var_r28 + (s32)temp_r26)) == 0) && (*(s32 *)((p2 = (char *)arg0 + 0x2C, p2 + var_r28)) != 0)) {
                if (var_r24 == 0) {
                    Script_RunScript(QB_STATS_MESSAGE_LAND, 0, 0, 0, 0);
                    var_r24 = 1;
                }
                *(s32 *)((char *)(var_r28 + (s32)temp_r26)) = 1;
                temp_r31 = *(u32 *)((p3 = (char *)arg0 + 0x24, p3 + var_r28));
                switch (temp_r31) {
                case QB_MANUAL_BALANCE:
                    AddString(temp_r30, QB_TEXT, fn_801258B0(QB_MANUAL_INCREASE_TEXT, 0));
                    break;
                case QB_RAIL_BALANCE:
                    AddString(temp_r30, QB_TEXT, fn_801258B0(QB_RAIL_INCREASE_TEXT, 0));
                    break;
                case QB_LIP_BALANCE:
                    AddString(temp_r30, QB_TEXT, fn_801258B0(QB_LIP_INCREASE_TEXT, 0));
                    break;
                case QB_SPEED:
                    AddString(temp_r30, QB_TEXT, fn_801258B0(QB_SPEED_INCREASE_TEXT, 0));
                    break;
                case QB_OLLIE:
                    AddString(temp_r30, QB_TEXT, fn_801258B0(QB_OLLIE_INCREASE_TEXT, 0));
                    break;
                case QB_AIR:
                    AddString(temp_r30, QB_TEXT, fn_801258B0(QB_AIR_INCREASE_TEXT, 0));
                    break;
                case QB_FLIP_SPEED:
                    AddString(temp_r30, QB_TEXT, fn_801258B0(QB_FLIP_INCREASE_TEXT, 0));
                    break;
                case QB_SWITCH:
                    AddString(temp_r30, QB_TEXT, fn_801258B0(QB_SWITCH_INCREASE_TEXT, 0));
                    break;
                case QB_SPIN:
                    AddString(temp_r30, QB_TEXT, fn_801258B0(QB_SPIN_INCREASE_TEXT, 0));
                    break;
                case QB_RUN:
                    AddString(temp_r30, QB_TEXT, fn_801258B0(QB_RUN_INCREASE_TEXT, 0));
                    break;
                }
                AddInteger(temp_r30, QB_GOT_IT, 1);
                Script_RunScript(QB_SHOW_STATS_MESSAGE, temp_r30, 0, 0, 0);
                if (arg0->unk0x9FC != 0) {
                    fn_801A5240(temp_r27, temp_r31, fn_801A5210(temp_r27, temp_r31) + 1);
                }
            }
            var_r28 += 0x24;
        } while (--var_r25 != 0);
        if (var_r24 != 0) {
            fn_80143258(arg0->unk0xA9C, temp_r27);
            if (arg0->unk0xA00 == 0) {
                if (fn_801850FC(Game_GetGoalManager()) != 0) {
                    Script_RunScript(QB_BEAT_FIRST_STAT_GOAL, 0, 0, 0, 0);
                    arg0->unk0xA00 = 1;
                }
            }
            Script_RunScript(QB_STAT_PLAY_WIN_SOUND, 0, 0, 0, 0);
        }
        if (temp_r30 != 0) {
            CStruct_delete(temp_r30, 3);
        }
        arg0->unk0xA8C = 0;
        arg0->unk0xA90 = 0;
    }
}
