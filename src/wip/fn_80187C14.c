// WIP DRAFT (non-matching) — group F rebuild
// 2026-10-08: 60.39% -> **76.8%** (official) from ONE pin found by the
// reload_pin_sweep chunk run: `CStruct *cur` -> `register CStruct *cur __asm__("r10")`
// (sweep predicted 60.39 -> 76.77; reproduces exactly).
// RETURN-TYPE FIX 2026-09-25: `GetInteger` declared `s32` here, but
// its result is discarded at every call site in this body.  With the
// result live, ngccc's expand_call reorders the arg setup (doc-15);
// declaring it `void` restores retail's order.
// Lever: automated sweep, M8.31 / AGENTS 4q.1.  Now 60.00% NEAR.
// family=m2c range=0x80187C14-0x801880EC size=1240B
// PARKED: 60% — saved-reg/CR allocation coin-flips (doc-15 + doc-28
// class). Body fully restructured from disasm and is semantically faithful;
// every callee arity/return audited. What was FIXED to get 12%→60%:
//   - chained creates: CStruct_ctor(CStruct_new(8)) everywhere; prefs =
//     fn_8018BFAC(elem) chained as arg0 of GetString; newobj = create
//     chained into AddChecksum; handle = fn_80128F94(fn_8003E7CC(0xC))
//     chained as arg0 of the 3-ARG fn_80129068(handle, sp2C, 0xA)
//     (m2c draft had dropped that chained arg0); fn_80126FF4(newobj=create,
//     node->8) assignment-expression form.
//   - THIRD distinct object var (`third`, create#3 in the fn_80128978==0
//     branch): want homes it in r30 while newobj(r29) stays live — m2c
//     conflated them, which stretched newobj's web and broke coloring
//     (+10% alone).
//   - separate `list2` var for *(cur+8) in the walk loop (do NOT reuse key).
//   - s32→void flips on AddInteger + AddString fixed the mr/ori
//     arg-setup order at their call sites (M8.31 inverse) and, as a side
//     effect, the cur(r27)/list2(r28) walk-loop coloring.
//   - register-pin zero_r18 (§6a-6) fixes the r18=zero / r19=arg1 bottom
//     pair — BUT its li hoists to function entry (register vars are live-
//     from-entry) where want has it after the loop guard (~13-word shift).
//     Pinning a COPY of arg1 to r19 instead was tried and is WORSE (48%):
//     without the r18 claim the whole map rotates back. elem/prefs/newobj
//     pinning corrupts call args (§70-130a, verified 7%).
// REMAINING diffs (all downstream allocator state, no source lever found):
//   1. li r18,0 position (see above).
//   2. sp24/sp28 zero stores use r0/r30 instead of want's single freed-r31
//      zero web.
//   3. arg2!=0 long-range test: want spills cr0 via mfcr r22 + mtcrf 0x80
//      before the branch; got keeps it in a free saved-CR field (cr3,
//      mtcrf 0x18 epilogue) — doc-28 shape; the §6t-2 memory-bitfield trick
//      does not apply cleanly because want ALSO keeps cr4=(obj_a==0) live
//      across the whole outer walk loop natively.
//   4. inner-walk cur2 recycles the dead r18 pin reg instead of want's r30.
// Retry hints: re-run after any recipe that pins late-born webs or models
// mfcr/mtcrf CR0 spill from C; check whether fn_80127AAC/AddChecksum
// return types flip anything further once 1-3 have a route.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802A9500[];
extern s32 CStruct_new(s32 size);
extern s32 CStruct_ctor(s32 arg0);
extern s32 fn_80184168(Unk_9994C3F5 * arg0);
extern void *fn_8018B4C0(Unk_C8FEE62D * arg0, s32 *arg1, s32 *arg2);
extern s32 fn_8018E24C(Unk_C7387A53 * arg0);
extern s32 fn_8018D924(Unk_C7387A53 * arg0);
extern s32 fn_8018BFAC(Unk_C7387A53 * arg0);
extern s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
extern s32 AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
extern void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 fn_80190840(Unk_C7387A53 * arg0);
extern void AddString(CStruct * arg0, s32 arg1, void * arg2);
extern s32 GetArray(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void fn_80127AAC(CStruct * arg0, s32 arg1, Unk_5AA7B5D7 * arg2);
extern s32 fn_80128978(s32 arg0, s32 arg1);
extern s32 fn_80127C14(CStruct * arg0, s32 arg1, CStruct * arg2);
extern void CStruct_delete(CStruct * arg0, s32 arg1);
extern s32 GetStructure_2(CStruct * arg0, s32 hash, s32 * out, s32 flag);
extern void GetInteger(CStruct * arg0, s32 hash, s32 * out, s32 flag);
extern void fn_801270B4(CStruct * arg0, s32 arg1);
extern s32 fn_8003E7CC(s32 arg0);
extern s32 fn_80128F94(Unk_9D4ED6AF * arg0);
extern s32 fn_80129068(Unk_5AA7B5D7 * arg0, s32 arg1, s32 arg2);
extern void fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
extern void fn_80129314(CStruct * arg0, s32 arg1, s32 arg2);
extern void AddArrayPointer(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 fn_80127358(CStruct * arg0, Unk_C7387A53 * arg1);
extern void fn_80126A30(Unk_5AA7B5D7 * arg0);
extern void fn_80128FB4(Unk_F8A5095F * arg0, s32 arg1);
extern void fn_80127CD4(CStruct * arg0, s32 arg1, s32 arg2);

void fn_80187C14(Unk_9994C3F5 *arg0, CStruct *arg1, s32 arg2) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 cnt;
    s32 obj_a;
    s32 obj_b;
    s32 elem;
    s32 name_obj;
    s32 flags_a;
    s32 flags_b;
    s32 prefs;
    s32 newobj;
    s32 third;
    s32 key;
    s32 list2;
    s32 handle;
    s32 idx;
    register CStruct *cur __asm__("r10");   /* 2026-10-08 pin-sweep +16.4 */
    s32 nxt;
    Unk_9994C3F5 *cur2;
    s32 nxt2;
    Unk_5BE2D2B7 *vtbl;
    register s32 zero_r18 __asm__("r18");

    obj_a = CStruct_ctor(CStruct_new(8));
    obj_b = CStruct_ctor(CStruct_new(8));
    cnt = fn_80184168(arg0);
    sp8 = 0;
    zero_r18 = 0;
    if (sp8 < cnt) {
        do {
            elem = (s32)fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
            key = ((Unk_C8FEE62D *)elem)->unk0x34;
            if ((arg2 == 0) || (key == arg2)) {
                flags_a = 0;
                name_obj = fn_8018E24C((void *)elem);
                vtbl = *((void * *)&((Unk_C8FEE62D *)elem)->unk0x14);
                if (vtbl->unk0xAC(
                        (void *)(elem + vtbl->unk0xA8)) != 0) {
                    flags_a = 1;
                }
                flags_b = 0;
                if (fn_8018D924((void *)elem) != 0) {
                    flags_b = 1;
                }
                GetString(prefs = fn_8018BFAC((void *)elem), QB_VIEW_GOALS_TEXT, &sp10, 1);
                AddChecksum(newobj = CStruct_ctor(CStruct_new(8)), QB_GOAL_ID, name_obj);
                AddInteger(newobj, QB_BEATEN, flags_a);
                AddInteger(newobj, QB_LOCKED, flags_b);
                AddInteger(newobj, QB_REWARD_POINTS, fn_80190840(elem));
                AddString(newobj, QB_VIEW_GOALS_TEXT, sp10);
                sp14 = zero_r18;
                sp18 = zero_r18;
                if (GetString(prefs, QB_GOAL_DESCRIPTION, &sp14, 0) != 0) {
                    AddString(newobj, QB_GOAL_DESCRIPTION, sp14);
                } else if (GetArray(prefs, QB_GOAL_DESCRIPTION, &sp18, 0) != 0) {
                    fn_80127AAC(newobj, QB_GOAL_DESCRIPTION, sp18);
                } else {
                    AddString(newobj, QB_GOAL_DESCRIPTION, (s32)lbl_802A9500);
                }
                sp1C = 0;
                GetString(prefs, QB_VIEW_GOALS_TIP, &sp1C, 0);
                if (sp1C != 0) {
                    AddString(newobj, QB_VIEW_GOALS_TIP, sp1C);
                }
                sp20 = 0;
                GetArray(prefs, QB_VIEW_GOALS_CAMERAS, &sp20, 0);
                if (sp20 != 0) {
                    fn_80127AAC(newobj, QB_VIEW_GOALS_CAMERAS, sp20);
                }
                if (fn_80128978(obj_a, key) == 0) {
                    third = CStruct_ctor(CStruct_new(8));
                    fn_80127C14(obj_a, key, third);
                    if (third != 0) {
                        CStruct_delete(third, 3);
                    }
                }
                sp24 = 0;
                GetStructure_2(obj_a, key, &sp24, 1);
                fn_80127C14(sp24, name_obj, newobj);
                if (newobj != 0) {
                    CStruct_delete(newobj, 3);
                }
                GetInteger(sp24, QB_NUM_GOALS_ADDED, &sp28, 0);
                sp28 += 1;
                AddInteger(sp24, QB_NUM_GOALS_ADDED, sp28);
            }
            sp8 += 1;
        } while (sp8 < cnt);
    }
    cur = fn_80127358(obj_a, NULL);
    if (cur != NULL) {
        idx = 0;
        do {
            nxt = fn_80127358(obj_a, cur);
            list2 = cur->unk0x8;
            GetInteger(list2, QB_NUM_GOALS_ADDED, &sp2C, 1);
            fn_801270B4(list2, QB_NUM_GOALS_ADDED);
            fn_80129068(handle = fn_80128F94(fn_8003E7CC(0xC)), sp2C, 0xA);
            cur2 = fn_80127358(list2, NULL);
            if (cur2 != NULL) {
                do {
                    nxt2 = fn_80127358(list2, cur2);
                    fn_80126FF4(newobj = CStruct_ctor(CStruct_new(8)),
                                cur2->unk0x8);
                    fn_80129314(handle, idx++, newobj);
                    cur2 = nxt2;
                } while (cur2 != NULL);
            }
            if (arg2 != 0) {
                AddArrayPointer(arg1, QB_VIEW_GOALS_INFO, handle);
                if (obj_a != 0) {
                    CStruct_delete(obj_a, 3);
                }
                if (obj_b != 0) {
                    CStruct_delete(obj_b, 3);
                }
                return;
            }
            fn_80127AAC(obj_b, cur->unk0x4, handle);
            fn_80126A30(handle);
            if (handle != 0) {
                fn_80128FB4(handle, 3);
            }
            cur = nxt;
        } while (cur != NULL);
    }
    if (obj_a != 0) {
        CStruct_delete(obj_a, 3);
    }
    fn_80127CD4(arg1, QB_VIEW_GOALS_INFO, obj_b);
}
