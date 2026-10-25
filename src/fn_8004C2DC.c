// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004C2DC-0x8004C410 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8004C410(s32 arg0, Unk_DB0E2BAB *arg1);
void CObject_AddRefLink(Unk_C7387A53 *arg0, Unk_C7387A53 **arg1);
void CObject_RemoveRefLink(Unk_C7387A53 *arg0, Unk_C7387A53 **arg1);

//  (8) SPLIT init/loop temps (`first` vs `node`): want loads walk->unk0x0
//      into r3 (call-arg chain, dies at DFA0) and only recycles r31 for the
//      loop node AFTER zero1 dies — 8 homes total.  One shared `node` var
//      made GCC home the init web too (9 homes: stmw r23, frame -0x40,
//      every home shifted -1).
//  (12) PROMOTE-BLOCKER FIXED: masked 100% but both while-exit `beq`s
//       resolved +6 insns past want's (promote_wip REFUSE, 2 internal
//       branch targets).  GCC constant-propagated `sp[0] == 0` down the
//       exit paths (sp[0] written NULL right before) and skipped the
//       cleanup TEST entirely — retail always re-tests (c3cc = lwz/cmpwi/
//       beq cleanup check).  Memory clobber before the cleanup forces the
//       reload + test for both the entry-test and latch-test exits.
//  (11) SPLIT SOURCE EXPRESSIONS: memory ops use `sp[0]` (array ->
//       8(r1) fold) while the homed `p` feeds ONLY call args ([mr r4,r29])
//       — using `p[0]` for memory too made GCC address through the p-home
//       (0(r30)) instead of want's r1 fold, everywhere.
//  (10) TWO-WEB &sp (§6s-1 verbatim): `b = sp` births the address into
//       scratch r9 for the two init stores (`b[1]=0` -> stw 4(r9)),
//       `p = b` copies it homed into r29 BETWEEN them (want literally has
//       [addi r9,r1,8][stw r31,4(r9)][mr r29,r9][stw r31,8(r9)]), then
//       every call arg + later p[0] use goes through p (r29 / 8(r1)
//       folds).  A single var made GCC birth directly into r30 with no
//       copy, which also swapped walk to r29 (want r30).
//  (9) CONDITION WITHOUT ASSIGNMENT: `while ((node = p[0]))` unified the
//      condition+body node defs into ONE homed web (r31) — that pushed a
//      9th home (stmw r23, frame -0x40).  Want's condition value is a
//      DYING scratch (lwz r9 / cmpwi / cmpw, dies before the body), and
//      the body re-reads p[0] fresh (r31) in the separate jump-target
//      block.  Plain `while (p[0])` + `if (p[0] == *arg1)` CSEs the two
//      header reads into that one scratch, `node = p[0]` inside the body
//      gets its own reload+home, and zero1 (r31) dies at the entry-test's
//      walk->unk0x18 store just before node's birth — 8 homes.
void fn_8004C2DC(s32 arg0, Unk_C7387A53 **arg1) {
    Unk_C7387A53 *sp[4];
    Unk_C7387A53 **b;
    Unk_C7387A53 **p;
    s32 *tbl;
    s32 i;
    Unk_DB0E2BAB *walk;
    Unk_C7387A53 *first;
    Unk_C7387A53 *node;
    Unk_C7387A53 *next;

    tbl = (s32 *) ((char *) arg0 + 0x5A4);
    for (i = 0; i <= 3; i++) {
        walk = (Unk_DB0E2BAB *) tbl[i];
        if (walk != NULL) {
            do {
                if (walk->unk0x18 != 0) {
                    fn_8004C410(arg0, walk);
                    b = sp;
                    b[1] = NULL;
                    __asm__ volatile("" : "+r"(b));
                    p = b;
                    b = sp;
                    b[2] = NULL;
                    first = (Unk_C7387A53 *) walk->unk0x0;
                    sp[0] = first;
                    if (first != NULL) {
                        CObject_AddRefLink(first, p);
                    }
                    while (sp[0] != NULL) {
                        if (sp[0] == *arg1) {
                            walk->unk0x18 = 0;
                            break;
                        }
                        node = sp[0];
                        if (node != NULL) {
                            CObject_RemoveRefLink(node, p);
                            sp[0] = NULL;
                        }
                        next = node->unk0x58;
                        sp[0] = next;
                        if (next != NULL) {
                            CObject_AddRefLink(next, p);
                        }
                    }
                    __asm__ volatile("" ::: "memory");
                    if (sp[0] != NULL) {
                        CObject_RemoveRefLink(sp[0], p);
                        sp[0] = NULL;
                    }
                }
                walk = (Unk_DB0E2BAB *) walk->unk0x10;
            } while (walk != NULL);
        }
    }
}
