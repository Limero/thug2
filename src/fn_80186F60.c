// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80186F60-0x80187424 (1220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: large skater/object task routine (register-locked r26/r27,
// walks 0x80300000 region). Score-compare + scorepot-style f64 conversion
// sites. Kept asm register variables from m2c — required for the byte match.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 fn_80186DF8(s32 arg0);
s32 fn_80184168(Unk_9994C3F5 * arg0);
void *fn_8018B4C0(Unk_C8FEE62D * arg0, s32 *arg1, s32 *arg2);
s32 fn_801906D4(Unk_C7387A53 * arg0);
s32 fn_801952F8(Unk_C7387A53 * arg0);
s32 fn_8018BFAC(Unk_C7387A53 * arg0);
s32 ContainsFlag(CStruct * arg0, s32 arg1);
s32 fn_801745B4(s32 arg0);
void *fn_801403CC(void * arg0);
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
s32 Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 fn_801270B4(CStruct * arg0, s32 arg1);
s32 CStruct_delete(CStruct * arg0, s32 arg1);
s32 fn_80128978(s32 arg0, s32 arg1);
s32 fn_80195F98(Unk_C7387A53 * arg0);
s32 fn_80197C80(Unk_D0C13A11 * arg0);
s32 fn_80196468(Unk_C7387A53 * arg0);
s32 fn_80190738(Unk_C7387A53 * arg0);
s32 fn_801813F0(CStruct * arg0);
s32 fn_80183D68(Unk_C7387A53 * arg0, s32 arg1);
s32 fn_8018E24C(Unk_C7387A53 * arg0);
s32 Script_SpawnScript(Unk_15EF4A35 * arg0, s32 arg1, s32 arg2, Unk_80577C09 * arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);

void *fn_80186F60(Unk_9994C3F5 *arg0) {
    s32 sp10;
    s32 sp14;
    s32 i;
    s32 sp1C;
    u64 pad20;
    s32 count;
    s32 cond;
    s32 task;
    s32 t745;
    Unk_89391A04 *vt;
    Unk_C8FEE62D *obj;
    Unk_C7387A53 *m1;
    Unk_C8FEE62D *m2;
    Unk_C8FEE62D *m6;
    register char *page __asm__("r26");
    register s32 a0 __asm__("r27");

    __asm__("" : : "m"(sp10), "m"(sp14), "m"(i), "m"(sp1C), "m"(pad20));
    page = (char *)0x80300000;
    a0 = arg0;
    fn_80186DF8(arg0);
    count = fn_80184168(arg0);
    i = 0;
    goto L_test;
L_chain:
    if (ContainsFlag(fn_8018BFAC(obj), QB_HIGH_COMBO) == 0) {
        goto L_arm2;
    }
    t745 = fn_801745B4(((Unk_5ACE0BC2 *)page)->unk0x5EAC);
    if (t745 == 0) {
        goto L_inc;
    }
    m1 = fn_801403CC(t745);
    if (m1->unk0x24 <= 0) {
        goto L_inc;
    }
    task = CStruct_ctor(CStruct_new(8));
    AddChecksum(task, QB_GOAL_ID, fn_8018E24C(obj));
    AddInteger(task, QB_LAST_SCORE_LANDED, m1->unk0x24);
    Script_RunScript(QB_GOAL_HIGHCOMBO_CHECK_SCORE, task, 0, 0, 0);
    if (task != 0) {
        CStruct_delete(task, 3);
        goto L_inc;
    }
    goto L_inc;
L_arm2:
    if (ContainsFlag(fn_8018BFAC(obj), QB_SCORE_GOAL) == 0) {
        goto L_arm3;
    }
    t745 = fn_801745B4(((Unk_5ACE0BC2 *)page)->unk0x5EAC);
    if (t745 == 0) {
        goto L_inc;
    }
    m2 = fn_801403CC(t745);
    GetInteger(fn_8018BFAC(obj), QB_SCORE, &sp10, 1);
    if (fn_801813F0(m2) + (s32)((f32)(f64)m2->unk0x18 * *((f32 *)&m2->unk0x6C)) >= sp10) {
        AddInteger(fn_8018BFAC(obj), QB_WINNING_SCORE,
            fn_801813F0(m2) + (s32)((f32)(f64)m2->unk0x18 * *((f32 *)&m2->unk0x6C)));
        fn_80183D68((s32)a0, fn_8018E24C(obj));
        fn_801270B4(fn_8018BFAC(obj), QB_WINNING_SCORE);
    }
    goto L_inc;
L_arm3:
    if (ContainsFlag(fn_8018BFAC(obj), QB_TRICKOBJECTS) == 0) {
        goto L_arm4;
    }
    fn_80195F98(obj);
    goto L_inc;
L_arm4:
    if (ContainsFlag(fn_8018BFAC(obj), QB_TRICKBEAT) == 0) {
        goto L_arm5;
    }
    fn_80197C80(obj);
    goto L_inc;
L_arm5:
    if (ContainsFlag(fn_8018BFAC(obj), QB_SKATETHELINE) == 0) {
        goto L_arm6;
    }
    fn_80196468(obj);
    goto L_inc;
L_arm6:
    if ((cond = fn_80128978(fn_8018BFAC(obj), QB_ARCADE_CURRENT_SCORE_TOTAL)) == 0) {
        goto L_arm7;
    }
    t745 = fn_801745B4(((Unk_5ACE0BC2 *)page)->unk0x5EAC);
    if (t745 == 0) {
        goto L_inc;
    }
    m6 = fn_801403CC(t745);
    GetInteger(fn_8018BFAC(obj), QB_ARCADE_CURRENT_SCORE_TOTAL, &sp14, 0);
    if (fn_801813F0(m6) + (s32)((f32)(f64)m6->unk0x18 * *((f32 *)&m6->unk0x6C)) > sp14) {
        sp14 = fn_801813F0(m6) + (s32)((f32)(f64)m6->unk0x18 * *((f32 *)&m6->unk0x6C));
        AddInteger(fn_8018BFAC(obj), QB_ARCADE_CURRENT_SCORE_TOTAL, sp14);
    }
    goto L_inc;
L_arm7:
    if (fn_80190738(obj) == 0) {
        goto L_inc;
    }
    if (ContainsFlag(fn_8018BFAC(obj), QB_COMBO_STARTED) == 0) {
        goto L_inc;
    }
    task = CStruct_ctor(CStruct_new(8));
    AddChecksum(task, QB_GOAL_ID, fn_8018E24C(obj));
    Script_SpawnScript(QB_GOAL_LOSE_NEXT_FRAME, task, 0, 0, 0, 0, 0, 0, cond, cond);
    if (task != 0) {
        CStruct_delete(task, 3);
    }
L_inc:
    i += 1;
L_test:
    if (i >= count) {
        goto L_exit;
    }
    obj = fn_8018B4C0((char *)a0 + 4, &i, &sp1C);
    obj = obj;
    vt = *((void * *)&obj->unk0x14);
    if (vt->unk0x24((char *)obj + vt->unk0x20) == 0) {
        goto L_inc;
    }
    if (fn_801906D4(obj) != 0) {
        return (void *)fn_801952F8(obj);
    }
    goto L_chain;
L_exit: ;
}
