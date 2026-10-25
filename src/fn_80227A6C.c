// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80227A6C-0x80227D64 (760B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A83F8[];
extern s32 lbl_80305EC0;
extern s32 Game_GetGoalManager();
extern s32 GoalManager_GetGoal(s32, s32, s32);
extern s32 fn_801840F0(Unk_C7387A53 *, s32);
extern s32 fn_8021D358(s32, u16);
extern s32 NextItem(s32);
extern s32 fn_80184248(s32);
extern s32 fn_801859E8(Unk_9994C3F5 *);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void AddInteger(CStruct *, s32, s32);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
extern void fn_80191DBC(s32);
extern s32 fn_80198B10(s32);
extern void fn_8018ED70(Unk_C7387A53 *, void *);
extern void AddString(CStruct *, s32, void *);
extern s32 fn_8018E1E8(void *);
bool fn_80227A6C(CScript *arg0) {
    s32 sp8;
    s32 var_byte;
    CScript *t26;
    void *t27;
    register void *t28 __asm__("r28");
    void *t29;
    register void *t30 __asm__("r30");
    Unk_C8FEE62D *t31;
    void *var_r3;
    s32 *list;
    s32 *list2;

    t31 = *(void **)arg0;
    t27 = *((void * *)&arg0->unk0x18);
    t29 = (void *)Game_GetGoalManager();
    t30 = (void *)GoalManager_GetGoal(t29, t31->unk0x4, 1);
    t28 = (void *)fn_801840F0((s32)t29, 0);
    if ((s32)t30 == 0) {
        return true;
    }
    t26 = (void *)fn_8021D358((s32)t27, (u16)(s8)*(u8 *)t31);
    t31 = (void *)NextItem((s32)t27);
    var_r3 = (void *)*(s32 *)((char *)(((Unk_C8FEE62D *)t30)->unk0x14) + 0xEC);
    ((s32 (*)(void *, s32))var_r3)((char *)t30 + *(s16 *)((char *)(((Unk_C8FEE62D *)t30)->unk0x14) + 0xE8), t26->unk0x34);
    if (t26->unk0x18 == 0) {
        return true;
    }
    var_r3 = (void *)*(s32 *)((char *)(((Unk_C8FEE62D *)t30)->unk0x14) + 0xE4);
    ((s32 (*)(void *, s32))var_r3)((char *)t30 + *(s16 *)((char *)(((Unk_C8FEE62D *)t30)->unk0x14) + 0xE0), *(s32 *)((char *)*((s32 * *)&t26->unk0x18) + 0x18));
    if ((s32)t31 == (s32)t26) {
        t28 = (void *)fn_80184248((s32)t29);
        t29 = (void *)fn_801859E8((s32)t29);
        if ((s32)t28 > (s32)t29) {
            t31 = (void *)CStruct_ctor(CStruct_new(8));
            AddInteger((s32)t31, QB_NUMGOALSLEFT, (s32)t28 - (s32)t29);
            Script_RunScript(QB_GOAL_ATTACK_COMPLETED_GOAL, t31, 0, 0, 0);
            if ((s32)t31 != 0) {
                CStruct_delete((s32)t31, 3);
            }
        }
        fn_80191DBC(((Unk_C8FEE62D *)t30)->unk0x18);
        return true;
    }
    if ((s32)t28 != 0) {
        fn_8018E1E8((s32)t30);
        fn_8018E1E8((s32)t28);
    }
    if (fn_80198B10(lbl_80305EC0) == 0) {
        return true;
    }
    if (t31->unk0x34 != t26->unk0x34) {
        return true;
    }
    list = *((s32 * *)&((Unk_C8FEE62D *)t30)->unk0x2C);
    if (*list != 0) {
        t31 = t30;
        list2 = list;
        if (list2 != NULL) {
            do {
                list2 = *list2;
                t31 = (void *)GoalManager_GetGoal(t29, list2, 1);
                list2 = *((s32 * *)&t31->unk0x2C);
            } while ((list2 != NULL) && (*list2 != 0));
        }
        var_r3 = (void *)*(s32 *)((char *)(t31->unk0x14) + 0x84);
        ((s32 (*)(void *))var_r3)((char *)t31 + *(s16 *)((char *)(t31->unk0x14) + 0x80));
        if ((s32)t31 != (s32)t28) {
            var_r3 = (void *)*(s32 *)((char *)(((Unk_C8FEE62D *)t28)->unk0x14) + 0x74);
            ((s32 (*)(void *, s32, s32))var_r3)((char *)t28 + *(s16 *)((char *)(((Unk_C8FEE62D *)t28)->unk0x14) + 0x70), 0, 1);
        }
    } else {
        var_r3 = (void *)*(s32 *)((char *)(((Unk_C8FEE62D *)t30)->unk0x14) + 0x84);
        ((s32 (*)(void *))var_r3)((char *)t30 + *(s16 *)((char *)(((Unk_C8FEE62D *)t30)->unk0x14) + 0x80));
    }
    fn_80191DBC(((Unk_C8FEE62D *)t28)->unk0x18);
    var_r3 = (void *)*(s32 *)((char *)(((Unk_C8FEE62D *)t30)->unk0x14) + 0xDC);
    ((s32 (*)(void *))var_r3)((char *)t30 + *(s16 *)((char *)(((Unk_C8FEE62D *)t30)->unk0x14) + 0xD8));
    t28 = (void *)fn_80184248((s32)t29);
    t29 = (void *)fn_801859E8((s32)t29);
    if ((s32)t28 > (s32)t29) {
        sp8 = 0;
        fn_8018ED70((void *)t30, &sp8);
        t31 = (void *)CStruct_ctor(CStruct_new(8));
        AddInteger((s32)t31, QB_NUMGOALSLEFT, (s32)t28 - (s32)t29);
        AddString((s32)t31, QB_PLAYERNAME, (char *)t26 + 0x3C);
        AddString((s32)t31, QB_GOALTEXT, (void *)sp8);
        Script_RunScript(QB_GOAL_ATTACK_COMPLETED_GOAL_OTHER_SAME_TEAM, t31, 0, 0, 0);
        if ((s32)t31 != 0) {
            CStruct_delete((s32)t31, 3);
        }
    }
    return true;
}
