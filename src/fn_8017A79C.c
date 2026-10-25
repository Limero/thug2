// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017A79C-0x8017AB84 (1000B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
extern s32 lbl_80305F9C;
extern char lbl_802A9058[];
extern char lbl_802A9074[];
extern s32 fn_80198B10(s32);
extern s32 Game_GetGoalManager(void);
extern s32 GoalManager_GetGoal(s32, s32, s32);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern void fn_80131154(s32, CStruct *, Unk_9994C3F5 *, s32);
extern void AddString(CStruct *, s32, void *);
extern s32 fn_801258E8(void *, s32);
extern s32 CStruct_ctor(s32);
extern s32 CStruct_new(s32);
extern s32 NextItem(s32);
extern s32 fn_8022989C(CScript *);
extern s32 fn_80229B5C(CScript *);
extern s32 fn_8022986C(CScript *);
extern s32 fn_8021D358(s32, s32);
extern void CStruct_delete(CStruct *, s32);

bool fn_8017A79C(Unk_6A78CE27 *arg0) {
    s32 sp8[32];
    u8 tag;
    Unk_12004030 *t;
    s32 g;
    Unk_C7387A53 *p;
    s32 h;
    s32 var28;
    s32 b0;
    s32 b1;
    s32 temp30;
    Unk_C8FEE62D *entry;
    Unk_89391A04 *temp_r9;

    tag = arg0->unk0x4;
    if (tag == 0x91) {
        Script_RunScript(QB_GOAL_SCAVENGER_ADD_TIME, 0, 0, 0, 0);
    } else if (tag == 0x92) {
        entry = GoalManager_GetGoal(Game_GetGoalManager(), QB_SCAVENGER, 1);
        temp_r9 = *((s32 * *)&entry->unk0x14);
        if (temp_r9->unk0x24((char *)entry + temp_r9->unk0x20) != 0) {
            temp_r9 = *((s32 * *)&entry->unk0x14);
            temp_r9->unk0x34((char *)entry + temp_r9->unk0x30);
        }
    } else if (tag == 0x93) {
        temp30 = Game_GetGoalManager();
        entry = GoalManager_GetGoal(temp30, QB_SCAVENGER_INTERVAL, 1);
        temp_r9 = *((s32 * *)&entry->unk0x14);
        if (temp_r9->unk0x24((char *)entry + temp_r9->unk0x20) != 0) {
            temp_r9 = *((s32 * *)&entry->unk0x14);
            temp_r9->unk0x34((char *)entry + temp_r9->unk0x30);
        } else {
            entry = GoalManager_GetGoal(temp30, QB_SCAVENGER, 1);
            temp_r9 = *((s32 * *)&entry->unk0x14);
            if (temp_r9->unk0x24((char *)entry + temp_r9->unk0x20) != 0) {
                fn_80131154((s32)lbl_802A9058, 0, 0, 0);
            }
        }
    } else if (tag == 0x94) {
        entry = GoalManager_GetGoal(Game_GetGoalManager(), QB_SCAVENGER_COLLECT_PERIOD, 1);
        temp_r9 = *((s32 * *)&entry->unk0x14);
        if (temp_r9->unk0x24((char *)entry + temp_r9->unk0x20) != 0) {
            temp_r9 = *((s32 * *)&entry->unk0x14);
            temp_r9->unk0x34((char *)entry + temp_r9->unk0x30);
        }
    } else if (tag == 0x95) {
        g = lbl_80305F9C;
        t = *(s32 *)arg0;
        if (fn_80198B10(lbl_80305EC0) != 0) {
            var28 = -1;
            p = NextItem(g);
            if ((p != 0) && (fn_8022989C(p) == 0) && (fn_80229B5C(p) != 0)) {
                var28 = p->unk0x34;
            }
            h = CStruct_ctor(CStruct_new(8));
            AddString(h, QB_NAME, (char *)p + 0x3C);
            b1 = *((s8 *)&t->unk0x1);
            if (b1 == 1) {
                b0 = t->unk0x0;
                if (b0 == var28) {
                    Script_RunScript(QB_SCAVENGERHUNTONEOBJECTLEFTYOU, 0, 0, 0, 0);
                } else {
                    sprintf(sp8, (s32)lbl_802A9074, b0 + 1);
                    AddString(h, QB_NAME, fn_801258E8(sp8, 0));
                    Script_RunScript(QB_SCAVENGERHUNTONEOBJECTLEFTOTHERTEAM, h, 0, 0, 0);
                }
            } else if (b1 == 5) {
                b0 = t->unk0x0;
                if (b0 == var28) {
                    Script_RunScript(QB_SCAVENGERHUNTFIVEOBJECTSLEFTYOU, 0, 0, 0, 0);
                } else {
                    sprintf(sp8, (s32)lbl_802A9074, b0 + 1);
                    AddString(h, QB_NAME, fn_801258E8(sp8, 0));
                    Script_RunScript(QB_SCAVENGERHUNTFIVEOBJECTSLEFTOTHERTEAM, h, 0, 0, 0);
                }
            }
            if (h != 0) {
                CStruct_delete(h, 3);
            }
        } else {
            p = fn_8021D358(g, (u16)(s8)t->unk0x0);
            if (p != 0) {
                h = CStruct_ctor(CStruct_new(8));
                AddString(h, QB_NAME, (char *)p + 0x3C);
                b1 = *((s8 *)&t->unk0x1);
                if (b1 == 1) {
                    if (fn_8022986C(p) != 0) {
                        Script_RunScript(QB_SCAVENGERHUNTONEOBJECTLEFTYOU, 0, 0, 0, 0);
                    } else {
                        Script_RunScript(QB_SCAVENGERHUNTONEOBJECTLEFTOTHER, h, 0, 0, 0);
                    }
                } else if (b1 == 5) {
                    if (fn_8022986C(p) != 0) {
                        Script_RunScript(QB_SCAVENGERHUNTFIVEOBJECTSLEFTYOU, 0, 0, 0, 0);
                    } else {
                        Script_RunScript(QB_SCAVENGERHUNTFIVEOBJECTSLEFTOTHER, h, 0, 0, 0);
                    }
                }
                if (h != 0) {
                    CStruct_delete(h, 3);
                }
            }
        }
    }
    return true;
}
