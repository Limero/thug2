// RE-MEASURED 2026-10-07: 94.30% (was 93.67%) after deleting ALL six r-register pins + the two zero-code barriers + both FLAG lines together
//   reproduce: LEAF_TMPDIR=<private dir> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x801CB7B8
//   found by the scaffold-ablation sweep (AGENTS-recipes §6bg conjunction trap): the
//   header's own park note had ruled out ONE piece at a time, but the barrier's
//   removal alone had never been measured against the current body.
// WIP DRAFT (non-matching) — hand-rebuilt from disasm.
// family=m2c range=0x801CB7B8-0x801CBA30 size=632B
// PARKED at ~92% (-fno-schedule-insns2): body structure/registers byte-exact incl.
// page-anchor-in-r31 (asm lis @ha + pinned var_r28 early birth recycling), fr31 float,
// goto-dispatch block layout, asm-lwz scratch temps feeding pinned var_r28. Remaining
// 12 words = doc-15 family: (1) CObject_RemoveRefLink arg-move order (want r4-addi first);
// (2) big-body node-save vs hash-setup order (fixed by void-flip on AddChecksum/AddString,
// both applied); (3) oc/oo web homed r0 + sunk past addi (want r3 inside arms); (4)
// known-zero r27 propagated into else-arm Script_RunScript as `mr r5,r27` (want fresh
// `li r5,0`) — "=r" wedges break cmpwi home instead; identity barriers are transparent.
// Resisted: proto narrowing, void flips, inline-save chain, "+r"/"=r" barriers, sched flags.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305F9C[];
extern u32 lbl_80300434;
extern s32 lbl_80305EC0;
extern f32 lbl_802AD0A4;
extern f32 lbl_802AD0A8;
extern char lbl_802AD09C[];
extern s32 fn_8009CF2C(CStruct *);
extern s32 fn_8021F904(s32);
extern void GetElement_2(void *, void *, s32, s32);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern s32 fn_8021D358(s32, u16);
extern s32 fn_80145104(Unk_C7387A53 *);
extern s32 fn_8021C9B0(CScript *);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void AddChecksum(CStruct *, s32, s32);
extern s32 fn_80198B10(s32);
extern s32 fn_8014510C(Unk_EE36B018 *);
extern s32 sprintf(s32, ...);
extern void AddString(CStruct *, s32, void *);
extern void fn_8012788C(CStruct *, s32, f32, f32, f32);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern s32 CStruct_delete(CStruct *, s32);

void fn_801CB7B8(void *arg0) {
    s32 sp8[4];
    char sp18[0x48];
    register void *a0 __asm__("r29");
    s32 t30;
    s32 oc;
    s32 spv;
    s32 var_r28;
    Unk_24DD6A96 *o;

    register char *page __asm__("r31");
    a0 = arg0;
    __asm__ volatile("lis %0,%1@ha" : "=r"(page) : "s"(lbl_80305F9C));
    if (fn_8009CF2C(((Unk_5ECFB536 *)page)->unk0x5F9C) == 0 || fn_8021F904(((Unk_5ECFB536 *)page)->unk0x5F9C) == 0) {
        void *v9 = *((void * *)&((Unk_C8FEE62D *)a0)->unk0x18);
        ((s32 (*)(void *, s32)) ((Unk_DB0E2BAB *)v9)->unk0x44)((char *)a0 + (s16)((Unk_DB0E2BAB *)v9)->unk0x40, 1);
        return;
    }
    GetElement_2(sp8, lbl_80300434, ((Unk_C8FEE62D *)a0)->unk0x1C, 0);
    spv = sp8[0];
    if (spv != NULL) {
        {
            s32 spv2 = spv;
            CObject_RemoveRefLink(spv2, sp8);
        }
        sp8[0] = NULL;
    }
    t30 = fn_8021D358(((Unk_5ECFB536 *)page)->unk0x5F9C, *(u16 *)(((Unk_C8FEE62D *)a0)->unk0xC + (s32)0x1A));
    if (fn_80145104(((Unk_C8FEE62D *)a0)->unk0xC) == 0) {
        goto block_9;
    }
    {
        s32 var_r11;
        var_r11 = 1;
        if ((*(s32 *)(((Unk_C8FEE62D *)a0)->unk0xC + (s32)0x114) & 4) == 0) {
            var_r11 = 0;
        }
        if (var_r11 == 0) {
            goto big_body;
        }
    }
block_9:
    if (spv != NULL) {
        s32 node2 = CStruct_ctor(CStruct_new(8));
        AddChecksum(node2, QB_ID, ((Unk_C8FEE62D *)a0)->unk0x1C);
        Script_RunScript(QB_DESTROY_OBJECT_LABEL, node2, 0, 0, 0);
        if (node2 != 0) {
            CStruct_delete(node2, 3);
        }
    }
    return;
big_body:
    {
        register f32 var_f31 __asm__("fr31");
        s32 node;
        register char *sp18p __asm__("r30");

        var_f31 = (fn_8021C9B0(((Unk_5ECFB536 *)page)->unk0x5F9C) == t30) ? lbl_802AD0A4 : lbl_802AD0A8;
        AddChecksum(node = CStruct_ctor(CStruct_new(8)), QB_ID, ((Unk_C8FEE62D *)a0)->unk0x1C);
        if (fn_80198B10(lbl_80305EC0) != 0) {
            s32 t34;
            __asm__ volatile("lwz %0,0x34(%1)" : "=r"(t34) : "r"(t30));
            oc = ((Unk_C8FEE62D *)a0)->unk0xC;
            var_r28 = t34 + 2;
        } else {
            s32 oo = ((Unk_C8FEE62D *)a0)->unk0xC;
            s32 t18;
            __asm__ volatile("lwz %0,0x18(%1)" : "=r"(t18) : "r"(oo));
            oc = oo;
            var_r28 = t18 + 2;
        }
        sp18p = sp18;
        sprintf((s32)sp18p, (s32)lbl_802AD09C, var_r28, fn_8014510C(oc));
        AddString(node, QB_TEXT, sp18p);
        o = ((Unk_C8FEE62D *)a0)->unk0xC;
        fn_8012788C(node, QB_POS3D, o->unk0x58, o->unk0x5C + var_f31, o->unk0x60);
        {
            if (spv != NULL) {
                void *v9b = *((void * *)&((Unk_9994C3F5 *)spv)->unk0x8);
                ((s32 (*)(void *, s32)) ((Unk_89391A04 *)v9b)->unk0x14)((char *)spv + (s16)((Unk_89391A04 *)v9b)->unk0x10, node);
            } else {
                Script_RunScript(QB_CREATE_OBJECT_LABEL, node, 0, 0, 0);
            }
        }
        if (node != 0) {
            CStruct_delete(node, 3);
        }
    }
}
