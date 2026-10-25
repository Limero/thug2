// WIP DRAFT (non-matching) — INERT, never compiled into main.dol
// family=m2c range=0x801860B8-0x80186624 size=1388B
//
// PARKED 2026-10-05 (agent w_801860B8): m2c draft 8.9% -> this body 30.55%
//   masked (tools/score_wip.py, exact 0x56C length). Structure recovered:
//   * 0xd8 frame: `char buf[128]` at sp8 + the 8 out-params at sp88..spA4 in
//     declaration order, and mfcr/mtcrf CR save (the tail reuses cr3/cr4 from
//     the loop-2 guard, ~0x400 bytes later).
//   * real prototypes for EVERY callee (retail has no crclr except the 3
//     varargs sprintf calls): unprototyped/implicit decls cost a crclr each.
//   * `fn_80128978(fn_8018BFAC(), QB_ORDINAL)` — m2c dropped the script arg.
//   * loop 1: the value/index/list args are computed in each branch and the
//     single `fn_801292A8` is SHARED (branch -> join -> bl).
//   * loop 2: inner `while (idx < j)` with a `break` on the ordinal match plus
//     `if (idx != k)` swap of listA[k]/listA[idx].
//   * fn_8018EC90 / fn_8018ECBC / GoalManager_GetGoal used as NON-void (their
//     r3 is consumed); CStruct_ctor(CStruct_new(8)); Script_RunScript's 5th
//     arg; the mtlr+blrl vcall (GoalVtbl.adj MUST be s16 -> retail `lha r3,0xa8`).
//   * `goto addstring` INSIDE the `else if` branch so the QB_WIN_RECORD_STRING
//     AddString block falls through from the %i:%02i.%02i sprintf (retail has
//     no branch there) — this alone was worth +11 points and fixed the length.
//   RESIDUAL (241/347 words):
//   1. loop-2 entry guard. Retail = ONE 5-insn block
//        li r29,0 / cmpwi cr4,r27,0 / cmpw r29,r25 / cmpwi cr3,r21,0 / bge
//      then a body with NO cr4/cr3 test anywhere. ngccc 2.95.3 emits one branch
//      per && operand (proved with a 6-line `if (a&&b&&c)` test), so every
//      source shape leaves 2 extra `beq cr4/beq cr3` — here hoisted into the
//      preheader, and (via the redundant tail `break`) compensated at the latch
//      so the total length is right. The +2 shifts the index-aligned stream
//      for the remaining ~280 words; that shift is the bulk of the 241 diffs.
//      Tried: guard-outside, &&-in-condition, for/do-while/forever, break at
//      the top and at the bottom, nested ifs, separate ifs, `if (!(a&&b)) goto`.
//   2. `li r25,0` (counter j) is sunk below `bl fn_80184168` instead of staying
//      above it (2 words; same count, so harmless for alignment).
//   3. loop 1 emits `mr r4,j` before `mr r5,val`; retail has the reverse order.
//   4. block A vs the inner loop is laid out after it here, before it in retail.
//   5. `%i:%02i.%02i`: ngccc folds `(x/1000)/60` to the (wrong) `x/60`; retail
//      keeps `t=x/1000; t/60`. Forcing a temp for t restores retail's shape but
//      makes the object 1396B and drops the score to 18.7%, so it is left as is
// — see <scratch>
// DO NOT trust a higher-scoring shape: dropping the `k < j` guard test scores
//   26.8% but loses the CR save entirely (frame 0xb8, no mfcr/mtcrf, no cr3/cr4
//   reuse) — a byte-count coincidence, not a closer match.
#include "types.h"
#include "qb_constants.h"

/* Real prototypes for every callee: retail emits no crclr except for the
   varargs sprintf, so implicit/unprototyped decls are ruled out (each costs a
   crclr plus a register). GoalManager_GetGoal / fn_8018EC90 / fn_8018ECBC are
   declared non-void here because their r3 result IS used. */
s32 fn_80184168(void);
void fn_8003E7CC(s32);
void *fn_80128F94(void);
void fn_80129068(void *, s32, s8);
s32 fn_8018B4C0(s32 *, s32 *, s32 *);
s32 fn_8018BFAC(void);
s32 fn_80128978(s32, s32);
s32 fn_8018E24C(s32);
void fn_801292A8(void *, s32, s32);
s32 GetChecksum(void *, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
s32 GetInteger(void *, s32, s32 *, s32);
s32 fn_80186C48(s32);
s32 ContainsFlag(void *, s32);
void fn_8018ED70(s32, void *);
s32 fn_8018EC90(s32);
s32 fn_8018ECBC(s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(void *, s32, s32);
void AddString(void *, s32, void *);
s32 GetChecksum_2(void *, s32, s32 *, s32);
char *PrintThousands(s32, char);
s32 sprintf();
char *strcat(char *, char *);
void CStruct_delete(void *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80126A30(void *);
void fn_80128FB4(void *, s32);

/* .rodata strings as extern arrays (not literals) so GCC emits lis/la pairs
   instead of inlining the copies. */
extern char lbl_802A94BC[]; /* "%i"           */
extern char lbl_802A94C0[]; /* "st place"     */
extern char lbl_802A94CC[]; /* "nd place"     */
extern char lbl_802A94D8[]; /* "rd place"     */
extern char lbl_802A94E4[]; /* "%s"           */
extern char lbl_802A94E8[]; /* "%i:%02i.%02i" */

/* goal+0x14 is the offset table: [0xA8] s16 this-adjust, [0xAC] the handler.
   `adj` MUST be s16 or the call site loads it with lwz instead of retail's lha. */
typedef struct GoalVtbl {
    char pad0x0[0xA8];
    s16 adj;
    void (*fn)();
} GoalVtbl;

typedef struct Goal {
    char pad0x0[0x14];
    GoalVtbl *vtable;
} Goal;

void fn_801860B8(s32 arg0) {
    /* declaration order == stack order: buf@sp8, then sp88..spA4 above */
    char buf[128];
    s32 sp88;
    s32 sp8C;
    s32 sp90;
    s32 sp94;
    char *sp98;
    s32 sp9C;
    s32 spA0;
    s32 spA4;
    s32 n;
    void *listA;
    void *listB;
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 idx;
    s32 idxNext;
    s32 v;
    s32 v2;
    s32 item;
    s32 script;
    s32 goal;
    s32 struct30;
    s32 argV;
    s32 argI;
    s32 argL;

    i = 0;
    j = 0;
    n = fn_80184168();
    fn_8003E7CC(0xC);
    listA = fn_80128F94();
    fn_8003E7CC(0xC);
    listB = fn_80128F94();
    fn_80129068(listA, n, 0xD);
    fn_80129068(listB, n, 0xD);
    sp88 = 0;
    while (sp88 < n) {
        {   /* the extra block scope is load-bearing: without it ngccc emits
             * one word more here and the object stops matching 0x56C */
            item = fn_8018B4C0(arg0 + 4, &sp88, &sp8C);
            if (fn_80128978(fn_8018BFAC(), QB_ORDINAL) != 0) {
                argV = fn_8018E24C(item);
                argI = j;
                argL = listA;
                j = j + 1;
            } else {
                argV = fn_8018E24C(item);
                argI = i;
                argL = listB;
                i = i + 1;
            }
            fn_801292A8(argL, argI, argV);
            sp88 = sp88 + 1;
        }
    }
    k = 0;
    if (k < j && listA != 0 && listB != 0) {
        while (k < j) {
            idx = k;
            idxNext = k + 1;
            while (idx < j) {
                v = GetChecksum(listA, idx);
                GoalManager_GetGoal(arg0, v, 1);
                GetInteger(fn_8018BFAC(), QB_ORDINAL, &sp94, 1);
                if (sp94 - 1 == k) {
                    break;
                }
                idx = idx + 1;
            }
            if (idx != k) {
                v2 = GetChecksum(listA, k);
                GoalManager_GetGoal(arg0, v2, 1);
                GetInteger(fn_8018BFAC(), QB_ORDINAL, &sp90, 1);
                fn_801292A8(listA, k, v);
                fn_801292A8(listA, idx, v2);
            }
            k = idxNext;
            if (listA == 0 || listB == 0) {
                break;
            }
        }
    }
    idx = 0;
    while (idx < i) {
        v = GetChecksum(listB, idx);
        fn_801292A8(listA, idx + j, v);
        idx = idx + 1;
    }
    m = 0;
    while (m < n) {
        goal = GoalManager_GetGoal(arg0, GetChecksum(listA, m), 1);
        script = fn_8018BFAC();
        sp98 = 0;
        fn_8018ED70(goal, &sp98);
        if (sp98 != 0 && (fn_80186C48(arg0) != 0 || ContainsFlag(script, QB_PRO_GOAL) == 0)) {
            if (fn_8018EC90(goal) == 0) {
                struct30 = CStruct_ctor(CStruct_new(8));
                AddChecksum(struct30, QB_GOAL_ID, fn_8018E24C(goal));
                AddString(struct30, QB_TEXT, sp98);
                if (((s32 (*)(void *))((Goal *)goal)->vtable->fn)(goal + ((Goal *)goal)->vtable->adj) != 0) {
                    sp9C = 0;
                    if (fn_8018ECBC(goal) != 0) {
                        GetInteger(script, QB_WIN_RECORD, &sp9C, 0);
                        sprintf(buf, lbl_802A94BC, sp9C);
                        switch (sp9C) {
                        case 1:
                            strcat(buf, lbl_802A94C0);
                            break;
                        case 2:
                            strcat(buf, lbl_802A94CC);
                            break;
                        case 3:
                            strcat(buf, lbl_802A94D8);
                            break;
                        }
                        goto addstring;
                    } else if (GetChecksum_2(script, QB_RECORD_TYPE, &spA0, 0) != 0) {
                        if (spA0 == -QB_UNKNOWN_0x32993752) {
                            GetInteger(script, QB_WIN_RECORD, &sp9C, 0);
                            sprintf(buf, lbl_802A94E4, PrintThousands(sp9C, ','));
                        } else if (spA0 == QB_TIME) {
                            spA4 = 0;
                            GetInteger(script, QB_WIN_RECORD, &spA4, 0);
                            sprintf(buf, lbl_802A94E8, (spA4 / 1000) / 60,
                                    (spA4 / 1000) % 60, (spA4 % 1000) / 10);
                        } else {
                            goto run;
                        }
addstring:
                        AddString(struct30, QB_WIN_RECORD_STRING, buf);
                    } else {
                        AddChecksum(struct30, 0, QB_NO_RECORD_TYPE);
                    }
                }
            run:
                Script_RunScript(QB_VIEW_GOALS_MENU_ADD_ITEM, struct30, 0, 0, 0);
                if (struct30 != 0) {
                    CStruct_delete(struct30, 3);
                }
            }
        }
        m = m + 1;
    }
    fn_80126A30(listA);
    fn_80126A30(listB);
    if (listA != 0) {
        fn_80128FB4(listA, 3);
    }
    if (listB != 0) {
        fn_80128FB4(listB, 3);
    }
}
