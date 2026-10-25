// WIP DRAFT (non-matching) — C body REBUILT BY HAND from the DOL disassembly
// family=m2c range=0x8004E0B4-0x8004E710 size=1628B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-04 (0x8004E0B4, CBaseMenu_PassTargetedEvent).
// STATUS: 1628 B object = want size EXACTLY; masked want|got 98.28 %
// (7 disagreeing words of 407, all pure scheduler slots, zero length change).
// Hand-verified beyond the mask: all 43 call targets resolve by symbol name at
// exactly the want offsets, all constant-pool address pairs agree,
// and none of the 7 residual words is a branch.
// DIFF 14.36 % (1616 B, 3 words short) -> NEAR-ish 98.28 % (1628 B).
//
// WHAT THE REBUILD FIXED (all measured, all load-bearing — keep them):
//  1. fn_800A54AC is 6 GPR args (r3-r8) + f1 = ONE f32, not the 8-argument
//     call m2c produced. m2c split the float-constant load into a junk
//     `-3.765255e-39f` literal plus a `0x80290000` 7th argument; the correct
//     prototype (see src/wip/fn_8004EAC0.c, same 7-arg mixed ABI) removes the
//     phantom argument AND the spurious condition-register setup that an
//     fpr-passing unprototyped call makes the compiler emit before every call.
//  2. Every callee is declared with the signature retail's own call sites
//     prove, not m2c's guesses: fn_8003FF04 is 3-arg (m2c had 2),
//     CObject_AddRefLink/RemoveRefLink take (object, node) — m2c passed
//     `&node` for BOTH args, fn_8009E3D0's arg0 is the list ELEMENT (not
//     `this`), GetInteger/GetChecksum_2 are 4-arg, fn_8004E734 is 4-arg,
//     fn_8004215C/fn_80042180/fn_8004C414/fn_8004C858 all RETURN s32 (they are
//     tested in the entry guard) even though two of them are declared void
//     elsewhere in the tree.
//  3. Frame. Two 16-byte ref-link cells at 0x08/0x18 plus four s32 at
//     0x28..0x34 = 0x30 of locals, and nine simultaneously-live callee-saved
//     values (g, -1, 0, cell1-home, best, evt, cell2, this, ret/tmp), which is
//     what rounds the frame to 0x60 with the GPR save base at 0x3c and the
//     link-register slot at 0x64 = want's prologue byte-for-byte. GCC picks
//     the whole r23..r31 assignment on its own now that the semantics are
//     right — no pin is needed for `g`/`this` any more.
//  4. The ref-link idiom is the game's own — compare src/CScreenElement_CallMemberFunction.c
//     (EXACT): a `Cell *` alias over a local cell plus
//     `next = 0; prev = 0; obj = o;` then `AddRefLink(o, p)`. m2c instead
//     punned `((Unk_59AB5482 *)&sp8)->unk0x4 = 0` through a `s32 *` and passed
//     `&sp8` as the object, which is wrong and generates a rematerialised
//     address at every site instead of retail's register web.
//  5. Loop shapes. The grid-index walk is `while (cell1.obj != NULL) { ... }`
//     (pre-tested, bottom re-tested — retail has no do-while latch) and the
//     child-id walk is `for (;;) { if (cell1.obj == NULL) break; if (match)
//     { ...; break; } idx += 1; ... }`, whose bottom test sits at 0x8004E504
//     ABOVE the id compare. m2c's do-while + goto gives a different block
//     layout and a different counter-increment position.
//  6. `this->unk0x64` is the list head, fn_8009E3D0 is called with the list
//     ELEMENT, and the child's id compare is `sp34 == elem->unk0x18`
//     (m2c read the operand order off a reload and got the test shape right by
//     accident but the arg0 wrong).
//
// THE 2026-10-04 BREAKTHROUGH — "re-test the FIELD, not the local".
// The previous park note blamed the 2-word block-1 shortfall on an
// unloadable GCC reload artefact and reached for `-fno-thread-jumps` (which
// does restore the reload+compare, and does then walk into the doc-28
// CR-pairing trap, so that route really is dead). The actual cause is a
// SOURCE-LEVEL bug that costs two words and no flags can fix: after the
// AddRefLink call, want RELOADS the cell field from the frame and compares it
// against null, while the earlier body had folded the null test into a branch
// on the already-live value — which also left the second block 2 words short.
//
// GCC can only thread the branch away (jump_threads) when the post-call
// condition is written on the SAME rtx the incoming edge constrains. Written
// as `if (elem == NULL)`, both tests share the pseudo for `elem`; written as
// `if (cell1.obj == NULL)` the second test is a fresh MEM operand on 8(r1),
// thread_jumps cannot match the two conditions, and the reload + compare
// survive. That is why block 2 — whose tests the previous agent had already
// written as `cell2.obj` — kept its redundant reload all along, and why the
// asymmetry looked like a register-allocation bug. It was a one-token
// difference in the lvalue, not a reload-pass artefact. §6z-133's
// `__asm__("" : "+r"(v))` barrier is NOT needed for this class.
//
// Two knock-on corrections to the previous note, both measured on the FIXED
// body (never re-measure scaffolding on a broken body):
//  (a) `cb = ca;` used to have THREE pinned aliases (r9 / r26 / r29). Two of
//      them were actively HARMFUL once the semantics were right:
//        - un-pinning `ca` (the scratch store base) flips the call argument
//          at all three AddRefLink sites to retail's callee-saved register
//          (+3 words of exact match). With the r9 pin present the compiler
//          preferred the pinned scratch register for the argument too, and
//          copy-prop had already merged the two webs so nothing could pull
//          them apart again.
//        - un-pinning `cb2` (cell2's scratch base) is what buys the
//          frame-relative store pair, the home-register copy and the matching
//          call arguments — the last 2 words of the old shortfall — PROVIDED
//          the calls still spell `&cell2` and only the two zero-stores go
//          through `cb2` (pinning the call argument to `cb2` as well makes
//          the compiler keep ONE register and costs 2 words).
//      `cb` alone still needs `register Cell *cb __asm__("r26")`: without it GCC
//      allocates the whole callee-saved set differently (evt -> r27, cell1
//      scratch -> r29, home -> r28) and the object drops back to 1616 B / 84.8 %.
//      Plain `register Cell *cb;` (no hard-register name) is byte-identical to
//      no pin at all, so the storage class alone buys nothing.
//  (b) Store order. The cell zero-stores must be spelled `next` before `prev`
//      in block 2 and in the grid-index loop, and `next` before `prev` in
//      block 1 too — the draft now spells all three `next` first, which is what
//      reproduces want's store pairs in both loops and in block 2.
//
// RESIDUAL: 7 words, no length change, all in two basic blocks.
//  a. Loop-1 cell init (5 words, 0x8004E378-0x8004E394). Everything matches
//     except slot placement: want hoists the saved-value reload to slot 2
//     and pushes the object store to the last slot; the build puts the
//     reload in slot 7 and the object store in slot 5. The two stores in
//     between already match exactly, as do the home-register copy and the
//     -1 constant load. Moving `this->unk0x1C0 = sp2c;` to the 2nd / 3rd
//     statement DOES hoist the reload (slot 1 instead of 2) but then shuffles
//     the prev / next pair down two slots — net zero. Measured, rejected.
//  b. The first fn_800A54AC setup (2 words, 0x8004E2D8/0x8004E2DC): want
//     folds the constant into the argument register and then copies the
//     object register; the build hoists the object-register copy above the
//     fold. The three other A54AC sites all match, so this is a per-block
//     scheduler artefact, not a prototype problem.
// Neither is reachable from C at this size without a store-order sweep, which
// is not being done here.
// 2026-10-18: stmt_perm_search.pl hill-climb on best..obj block: 98.77% ->
// 99.02% with source (best,obj,unk,prev) [perm (0,3,2,1)]. Manual follow-ups
// all worse (reverted): (next,best,prev,unk,obj)=98.8%, (next,unk,best,prev,
// obj)=98.5%. Want emits reload-early/obj-last; any source order moving obj
// last or unk early shuffles the prev/next pair or slips reload to slot 1.
// Kept: (next,best,obj,unk,prev). Residual 4 words at 0x8004E378-94.
//
// Also confirmed inert on the final body (re-measured, all byte-worse or
// no-ops): `-fno-schedule-insns2` (94.35 %), `-fno-schedule-insns` (1616 B),
// `-fno-delayed-branch`, `-fno-gcse` (94.59 %), `-fno-cse-follow-jumps`,
// `-fno-thread-jumps`, `-fexpensive-optimizations`. ngccc does not accept
// `-fno-schedule-insns1`, `-fno-crossjumping`, `-fno-if-conversion`,
// `-fno-tree-pre`.
//
// If you pick this up: the remaining 7 words are both pure final-scheduler
// slots in one 10-instruction block and one argument setup. Do NOT reach for
// the reload barrier — it is not what is missing here any more.#include "types.h"
// ORDERED 2026-09-11 (tools/stmt_perm_search.py): statement block lines 281..284 re-ordered; score now 99.0%.
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80301A78[];
extern f32 lbl_80292AD0;

/* list element reached through this->unk0x64: child id, the getter handle
   fn_8009E3D0 forwards, and the next link */
typedef struct Elem {
    char pad0x0[0x18];
    s32 unk0x18;
    char pad0x1c[0x8];
    CStruct *unk0x24;
    char pad0x28[0x48];
    s32 unk0x70;
} Elem;

/* the targeted event */
typedef struct Evt {
    s32 unk0x0;
    char pad0x4[0xC];
    CStruct *unk0x10;
} Evt;

/* 16-byte ref-link cell: the object that owns the link, plus the next/prev
   pair CObject_AddRefLink / CObject_RemoveRefLink splice. The same slot is
   reused as the CStruct parameter list for QB_CONTROLLER. */
typedef struct Cell {
    Elem *obj;
    struct Cell *next;
    struct Cell *prev;
    s32 pad0xc;
} Cell;

s32 fn_8004215C(s32);
s32 fn_8004C414(s32, s32);
s32 fn_80042180(Unk_F6E3A2C3 *);
s32 fn_8004C858(s32, s32);
s32 fn_8009EF74(Unk_F6E3A2C3 *, Evt *);
Elem *fn_8003FF04(Unk_F6E3A2C3 *, s32, s32 *);
Elem *fn_8003FF64(Unk_F6E3A2C3 *, s32);
void CObject_AddRefLink(Elem *, Cell *);
void CObject_RemoveRefLink(Elem *, Cell *);
void fn_8004EA60(Unk_F6E3A2C3 *);
void fn_8004E734(Unk_F6E3A2C3 *, s32, s32, s32);
void fn_8004EAC0(Unk_F6E3A2C3 *);
void fn_8004E900(Unk_F6E3A2C3 *, s32);
void fn_800A3B90(Evt *, s32, s32);
s32 fn_800A3BDC(Evt *);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8009E3D0(Elem *, s32, s32 *);
void CStruct_ctor(Cell *);
void AddInteger(Cell *, s32, s32);
void CStruct_delete(Cell *, s32);
s32 fn_800A54AC(s32, s32, s32, s32, s32, s32, f32);

s32 CBaseMenu_PassTargetedEvent(Unk_F6E3A2C3 *this, Evt *evt) {
    Cell cell1;
    Cell cell2;
    s32 sp28;
    s32 sp2c;
    s32 sp30;
    s32 sp34;
    s32 tmp;
    s32 g;
    s32 ret;
    s32 idx;
    s32 best;
    Elem *elem;
    Elem *next;
    /* ca/cb/cb2 are all `&cellN` under three different names: retail keeps the
       cell address in TWO registers at every init site (a short-lived scratch
       base for the indexed `stw rX, 4/8(rN)` stores, plus a callee-saved home
       that feeds the AddRefLink/RemoveRefLink argument register). Splitting the
       two uses into separate C variables is what reproduces that - see park
       note (a). Only `cb` still needs a hard-register pin. */
    Cell *ca;      /* scratch store base */
    register Cell *cb __asm__("r26");   /* callee-saved home -> the r4 argument */
    Cell *cb2;     /* cell2's scratch store base */

    tmp = this->unk0x10;
    if (((fn_8004215C(this) != 0) && (fn_8004C414(tmp, evt->unk0x0) != 0) &&
         ((fn_80042180(this) == 0) || (fn_8004C858(tmp, this->unk0x18) == 0))) ||
        (fn_8009EF74(this, evt) == 0)) {
        return 0;
    }
    g = *(s32 *)&lbl_80301A78;
    if (evt->unk0x0 == QB_NOTIFY_CHILD_LOCK) {
        ret = 0;
        if (this->unk0x194 != 0) {
            elem = fn_8003FF04(this, this->unk0x194, &sp28);
            ca = &cell1;
            ca->next = 0;
            ca->prev = 0;
            ca->obj = elem;
            cb = ca;
            if (elem != NULL) {
                CObject_AddRefLink(elem, cb);
            }
            if (cell1.obj == NULL) {
                elem = fn_8003FF64(this, this->unk0x190);
                cb2 = &cell2;
                cb2->next = 0;
                cb2->prev = 0;
                cell2.obj = elem;
                if (elem != NULL) {
                    CObject_AddRefLink(elem, &cell2);
                }
                if (cell2.obj != NULL) {
                    this->unk0x194 = cell2.obj->unk0x18;
                    fn_8004EA60(this);
                    ret = 1;
                } else {
                    this->unk0x190 = -1;
                    fn_8004E734(this, 1, 1, 1);
                    ret = 1;
                }
                if (cell2.obj != NULL) {
                    CObject_RemoveRefLink(cell2.obj, &cell2);
                    cell2.obj = 0;
                }
            } else {
                this->unk0x190 = sp28;
                fn_8004EA60(this);
            }
            if (cell1.obj != NULL) {
                CObject_RemoveRefLink(cell1.obj, cb);
                cell1.obj = 0;
            }
        } else {
            fn_8004E734(this, 1, 1, 1);
            ret = 1;
        }
        if ((ret != 0) && (this->unk0x198 != 0)) {
            fn_8004E734(this, 1, 1, 1);
            if (this->unk0x194 != 0) {
                CStruct_ctor(&cell1);
                AddInteger(&cell1, QB_CONTROLLER, this->unk0x19C);
                fn_800A54AC(g, QB_FOCUS, this->unk0x194, QB_SYSTEM, &cell1, 0, lbl_80292AD0);
                CStruct_delete(&cell1, 2);
            }
        }
        fn_8004EAC0(this);
        fn_800A3B90(evt, this->unk0x18, 0);
    }
    if ((evt->unk0x0 == QB_FOCUS) && (this->unk0x198 == 0)) {
        this->unk0x19C = fn_800A3BDC(evt);
        sp2c = -1;
        if (evt->unk0x10 != 0) {
            if (GetInteger(evt->unk0x10, QB_GRID_INDEX, &sp2c, 0) != 0) {
                elem = this->unk0x64;
                ca = &cell1;
                ca->next = 0;
                best = -1;
                ca->obj = elem;
                this->unk0x1C0 = sp2c;
                ca->prev = 0;
                cb = ca;
                if (elem != NULL) {
                    CObject_AddRefLink(elem, cb);
                }
                idx = 0;
                while (cell1.obj != NULL) {
                    sp30 = -1;
                    if ((fn_8009E3D0(cell1.obj, QB_TAG_GRID_X, &sp30) != 0) && (sp30 <= sp2c)) {
                        best = idx;
                    }
                    next = cell1.obj->unk0x70;
                    if (cell1.obj != NULL) {
                        CObject_RemoveRefLink(cell1.obj, cb);
                        cell1.obj = 0;
                    }
                    cell1.obj = next;
                    if (next != NULL) {
                        CObject_AddRefLink(next, cb);
                    }
                    idx += 1;
                }
                if (best != -1) {
                    this->unk0x190 = best;
                    this->unk0x194 = 1;
                }
                if (cell1.obj != NULL) {
                    CObject_RemoveRefLink(cell1.obj, cb);
                    cell1.obj = 0;
                }
            }
            if ((evt->unk0x10 != 0) && (GetChecksum_2(evt->unk0x10, QB_CHILD_ID, &sp34, 0) != 0)) {
                elem = this->unk0x64;
                ca = &cell1;
                ca->next = 0;
                ca->prev = 0;
                ca->obj = elem;
                cb = ca;
                if (elem != NULL) {
                    CObject_AddRefLink(elem, cb);
                }
                idx = 0;
                for (;;) {
                    if (cell1.obj == NULL) {
                        break;
                    }
                    if (sp34 == cell1.obj->unk0x18) {
                        this->unk0x194 = sp34;
                        this->unk0x190 = idx;
                        break;
                    }
                    idx += 1;
                    next = cell1.obj->unk0x70;
                    if (cell1.obj != NULL) {
                        CObject_RemoveRefLink(cell1.obj, cb);
                        cell1.obj = 0;
                    }
                    cell1.obj = next;
                    if (next != NULL) {
                        CObject_AddRefLink(next, cb);
                    }
                }
                if (cell1.obj != NULL) {
                    CObject_RemoveRefLink(cell1.obj, cb);
                    cell1.obj = 0;
                }
            }
        }
        this->unk0x198 = 1;
        if (this->unk0x194 != 0) {
            fn_8004E734(this, 1, 1, 0);
            if (this->unk0x194 != 0) {
                fn_800A54AC(g, QB_FOCUS, this->unk0x194, QB_SYSTEM, evt->unk0x10, 0, lbl_80292AD0);
            }
        }
        fn_800A3B90(evt, this->unk0x18, 0);
    }
    if ((evt->unk0x0 == QB_UNFOCUS) && (this->unk0x198 != 0)) {
        this->unk0x198 = 0;
        if (this->unk0x194 != 0) {
            fn_800A54AC(g, QB_UNFOCUS, this->unk0x194, QB_SYSTEM, 0, 0, lbl_80292AD0);
        }
        fn_800A3B90(evt, this->unk0x18, 0);
    }
    if ((((evt->unk0x0 == QB_PAD_UP) && (this->unk0x1A8 != 0)) ||
         ((evt->unk0x0 == QB_PAD_LEFT) && (this->unk0x1A8 == 0))) &&
        (this->unk0x198 != 0) && (this->unk0x1B8 != 0)) {
        fn_8004E900(this, -1);
        fn_800A3B90(evt, this->unk0x18, 0);
    }
    if ((((evt->unk0x0 == QB_PAD_DOWN) && (this->unk0x1A8 != 0)) ||
         ((evt->unk0x0 == QB_PAD_RIGHT) && (this->unk0x1A8 == 0))) &&
        (this->unk0x198 != 0) && (this->unk0x1B8 != 0)) {
        fn_8004E900(this, 1);
        fn_800A3B90(evt, this->unk0x18, 0);
    }
    return 1;
}
