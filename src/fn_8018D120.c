// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018D120-0x8018D404 (740B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Script-message dispatcher: resolves vtable-hooked "script message" callbacks
// off the object (0x20 hash field + 0x14 vtable), and on named message hashes
// (0x2D4C5829, 0x524566E3, 0xFD7AE1F4, 0xEFC35592, 0xD76C173E, 0x5BC07EAA)
// runs the corresponding updates (frame counting, count +/-, event send).
// Suggested rename: ScriptHandleMessages / ScriptDispatchMessage.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern s32 fn_8018D924(Unk_C7387A53 * arg0);
extern s32 fn_8018D5D4(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_80128978(s32 arg0, s32 arg1);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 fn_8018D7BC(Unk_C7387A53 * arg0);
extern s32 Game_GetGoalManager(s32 arg0);
extern s32 fn_8018E24C(Unk_C7387A53 * arg0);
extern s32 fn_80183D68(Unk_C7387A53 * arg0, s32 arg1);
extern s32 CStruct_new(s32 arg0);
extern s32 CStruct_ctor(s32 arg0);
extern s32 fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
extern s32 CStruct_delete(CStruct * arg0, s32 arg1);

s32 fn_8018D120(Unk_C8FEE62D *arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 temp_r30 __asm__("r30");
    s32 sp8;
    s32 spC;
    s32 temp_r3;
    s32 var_r25;
    s32 var_r26;
    s32 var_r29;
    Unk_5BE2D2B7 *temp_r9;
    var_r26 = 0;
    if (ContainsFlag(arg0->unk0x20, QB_SILENT_ACTIVATION) != 0) {
        temp_r9 = arg0->unk0x14;
        var_r26 = temp_r9->unk0xAC((void *)((char *)arg0 + temp_r9->unk0xA8)) == 0;
    }
    temp_r9 = arg0->unk0x14;
    if ((temp_r9->unk0x24((void *)((char *)arg0 + temp_r9->unk0x20)) != 0) || (var_r26 != 0)) {
        temp_r3 = fn_8018D924(arg0);
        if (temp_r3 != 0) {
            return 0;
        }
    } else {
        return 0;
    }
    temp_r30 = fn_8018D5D4(arg0, arg3);
    var_r25 = 0;
    if (fn_80128978(temp_r30, arg1) != 0) {
        GetInteger(temp_r30, arg1, &sp8, 1);
        AddInteger(temp_r30, arg1, arg2);
        if (sp8 != arg2) {
            var_r29 = 0;
            if (arg3 != 0) {
                GetInteger(temp_r30, QB_NUM_FLAGS_SET, &spC, 1);
                if (arg2 == 0) {
                    spC = spC - 1;
                } else {
                    var_r29 = 1;
                    spC = spC + 1;
                }
                AddInteger(temp_r30, QB_NUM_FLAGS_SET, spC);
            } else {
                if (arg2 == 0) {
                    arg0->unk0x60 -= 1;
                } else {
                    var_r29 = 1;
                    arg0->unk0x60 += 1;
                }
            }
            if ((var_r29 != 0) && (ContainsFlag(arg0->unk0x20, QB_NO_MIDGOAL_SOUND) == 0)) {
                Script_RunScript(QB_GOAL_GOT_FLAG_SOUND, 0, 0, 0, 0);
            }
            if (ContainsFlag(arg0->unk0x20, QB_USE_HUD_COUNTER) != 0) {
                Script_RunScript(QB_GOAL_UPDATE_COUNTER, arg0->unk0x20, 0, 0, 0);
            }
            AddInteger(arg0->unk0x20, QB_NUM_FLAGS_SET, arg0->unk0x60);
        }
        var_r25 = 1;
    }
    if (var_r26 != 0) {
        if (ContainsFlag(arg0->unk0x20, QB_TRICKOBJECTS) == 0) {
            temp_r30 = fn_8018D7BC((s32)arg0);
            if (temp_r30 != 0) {
                fn_80183D68(Game_GetGoalManager(temp_r30), fn_8018E24C((s32)arg0));
            } else if ((arg3 == 0) && (ContainsFlag(arg0->unk0x20, QB_GAPS) != 0) && (ContainsFlag(arg0->unk0x20, QB_NO_GAP_MESSAGES) == 0)) {
                temp_r30 = CStruct_ctor(CStruct_new(8));
                __asm__("");
                fn_80126FF4(temp_r30, arg0->unk0x20);
                Script_RunScript(QB_GOAL_GAPS_GOT_GAP, temp_r30, 0, 0, 0);
                if (temp_r30 != 0) {
                    CStruct_delete(temp_r30, 3);
                }
            }
        }
    }
    return var_r25;
}
