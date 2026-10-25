// RE-TRIAGED 2026-10-17: still 24.4% (re-measured, body unchanged). Residues
// are all global-alloc LUID ties / unconditional combine folds per below;
// no untried lever identified. Parking as-is.
// PARKED @ 24.4% masked (55/223 words), 2026-09-26 round.  Was 4.2%.
// 223/223 words now (exact length), correct frame, exact dispatch tree, correct
// control flow, correct callee arity.  Residue is ~25 words of register/schedule
// tie-breaks + one combine-time reassociation; see the residue list at the bottom.
//   verification: tools/venv/bin/python tools/score_body.py 0x8001D814 src/wip/fn_8001D814.c
// RESIDUE (want -> got), all pure regalloc/scheduler/algebra:
//  1. 0xD898 case0/0xD9B8 case2/0xDA54 case3: want `addi rX,n+1` BEFORE
//     `mr r30,first`; got emits the ret copy first.  15 source orderings tried
//     (decl-init vs assign, nn before/after the guard, inline n+1, function-scope
//     nn, dup assignment, r-before-nn, ret-after-store) - all identical.  The
//     `ret` pseudo is function-global so its copy wins every LUID tie.
//  2. 0xD924 case1: want `subf r10,top-r` + `mr r30,r10` (ret and bump pointer
//     kept in two registers); got coalesces ret/top into r30 (one `subf r30`).
//     top has only one post-copy use so local-alloc folds them.  Blocked copy
//     attempts: ntop temp, top=ntop, u32 top, ret=then top=ret, per-caller arity.
//  3. 0xD96C/0xDA08 cases 2/3 guard: want `last-0x400` then `topC-(...)`; got
//     combine reassociates to `topC+0x400` then `-last`.  7 spellings tried
//     (named room/lo/guard temps, inline, size>K, (u32) cast, (a-b)+c, split
//     +=) - fold is unconditional, so also moves the topC load earlier.
//  4. 0xDAB0/0xDB28 tail loops + 0xDACC/0xDAF0: want keeps the loop bound in the
//     count's own register (r10) and COPIES it to r4 for the loop (the loop body
//     clobbers r10); got allocates the bound to r6, which the body does not
//     clobber, so no copy - and r4/r5/r6 then rotate for &tblA/acc, which also
//     cascades into loop 2's &flagB/acc colouring.  12 variants tried
//     (cnt/n/postdec/predec/inline, shared function-scope n, 4 declaration
//     orders, with/without the tbl and fl locals, do/for/while, for/while-form
//     guard, explicit loop-limit temp) - the allocator always picks r6.
//  5. 0xD8E0 case1: the countB `lis` anchor lands 4 words later than want.
// FLAGS: -fno-schedule-insns2 18.2%, -fno-schedule-insns 16.9%, -fno-gcse 12.9%,
// -fno-sched-spec 24.4%, -fno-strength-reduce 24.4% - all WORSE than 24.4%.
// Return type (u32/s32/void*) and pool signedness (s32 - u32 would need cmplwi)
// make no difference; s32 pool + u32 size is what the DOL shows.
//
// WHAT THIS ROUND FIXED (the m2c draft was semantically wrong in 5 ways):
//  - m2c emitted the arena as `(char *)IDX + 0x80362A04` (index+base swapped)
//    for every in-use-flag store: the tables/flags are BASE+index, and the
//    s32* table index must be an element index.  Tables are now typed arrays
//    (`extern s32 lbl_803627E4[]`) - the typed-array form also reproduces
//    retail's lwzx/stwx with the BASE in rA, the raw-address-cast form does not.
//  - m2c read `temp_r7_3` in cases 2/3 while never assigning it (the countC/D
//    read and the `last` read were two separate loads in the original).
//  - m2c's second free-space loop had `acc += p[0] - p[-1]`; retail sums
//    `p[-1] - p[0]` (table B fills downward, so that is the positive block size).
//  - m2c put the whole tail INSIDE `default:`, so cases 1/2/3 `goto` it and the
//    case-0 body falls through - that reorders every block.  The tail belongs
//    after the switch; retail's layout is the compare tree, then case bodies in
//    ascending case order, then the tail.
//  - The switch needs a 5th, EMPTY case label at value 4.  Without it gcc's
//    balance_case_nodes splits 4 cases at index 1 (`cmpwi r4,1` first); with it
//    the split is index 2, which is retail's exact tree
//    (==2 / >2{==3} / ==0 / ==1 / default, bodies 0,1,2,3 in order).  The empty
//    label emits nothing (jump-threaded into the default), so the construct is
//    free but load-bearing for the tree.
// Also established: `fn_8001DB98` is `u32 fn_8001DB98(void)` (0-arg, returns
// `top - tblA[countA]`; the call sites use `cmplw`, and a prototype is required
// to avoid the `crclr cr1eq` retail does not have).  The arena is one contiguous
// .bss block (tblA[100]@0x803627E4, tblB[32]@0x80362974, tblC[2]@0x803629F4,
// tblD[2]@0x803629FC, flagA[100]@0x80362A04, flagB[32]@0x80362A68,
// flagC@0x80362A88, flagD@0x80362A8C, countA..D@0x80362A94..A0, bump
// pointer@0x80362AA8, watermarkC@0x80362AB4, watermarkD@0x80362AB8) but every
// access is an independent symbol reference, so separate externs are correct.
// WIP DRAFT (non-matching) — hand-reconstructed from the DOL disassembly
// family=m2c range=0x8001D814-0x8001DB98 size=900B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress.  activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"

/* Arena state.  Pool 0/1 bump the shared pointer at lbl_80362AA8 up/down;
   pools 2/3 grow the two 2-slot window tables inward from a watermark, keeping
   0x400 clear of it.  The in-use flag array for each table is byte-indexed with
   the same index as that table, so the free-space sums at the end walk both
   tables.  Table B fills downward, which is why its sum is p[-1] - p[0]. */
extern s32  lbl_803627E4[];   /* [100] ascending block table   */
extern s32  lbl_80362974[];   /* [ 32] descending block table  */
extern s32  lbl_803629F4[];   /* [  2] upper window table      */
extern s32  lbl_803629FC[];   /* [  2] lower window table      */
extern char lbl_80362A04[];   /* [100] in-use flags, ascending */
extern char lbl_80362A68[];   /* [ 32] in-use flags, descending*/
extern char lbl_80362A88[];   /* [  2] in-use flags, upper     */
extern char lbl_80362A8C[];   /* [  2] in-use flags, lower     */
extern s32  lbl_80362A94;     /* ascending table count         */
extern s32  lbl_80362A98;     /* descending table count        */
extern s32  lbl_80362A9C;     /* upper window table count      */
extern s32  lbl_80362AA0;     /* lower window table count      */
extern char lbl_80362AA8[];   /* shared bump pointer (s32)     */
extern s32  lbl_80362AB4;     /* upper watermark               */
extern s32  lbl_80362AB8;     /* lower watermark               */
extern char lbl_803001C0[];   /* low-water mark (u32)          */
extern s32  lbl_803001C4;     /* free bytes, ascending table   */
extern s32  lbl_803001C8;     /* free bytes, descending table  */

u32 fn_8001DB98(void);

u32 fn_8001D814(u32 size, s32 pool) {
    u32 ret;
    s32 i;   /* shared by both free-space loops: retail keeps it in r7 in each */
    ret = 0;
    switch (pool) {

    /* pool 0: take from the top of the bump-pointer block */
    case 0:
        if (fn_8001DB98() < size) { while (1) { } }   /* not enough room: spin */
        {
            s32 n = lbl_80362A94;
            s32 last = lbl_803627E4[n];
            if (last + size <= *(s32 *)&lbl_80362AA8) {
                s32 nn = n + 1;
                ret = last;
                lbl_803627E4[nn] = ret + ((size + 0x1F) & QB_UNKNOWN_0xFFFFFFE0);
                lbl_80362A04[n] = 1;
                lbl_80362A94 = nn;
            }
        }
        break;

    /* pool 1: carve from the bottom, moving the bump pointer down */
    case 1:
        if (fn_8001DB98() < size) { while (1) { } }
        {
            s32 n = lbl_80362A94;
            s32 *ta = lbl_803627E4;
            s32 top = *(s32 *)&lbl_80362AA8;
            if ((u32)(top - size) >= (u32)ta[n]) {
                s32 r = (size + 0x1F) & QB_UNKNOWN_0xFFFFFFE0;
                s32 nb = lbl_80362A98;
                s32 *tb = lbl_80362974;
                top = top - r;
                ret = top;
                tb[nb] = ret;
                lbl_80362A68[nb] = 1;
                lbl_80362A98 = nb + 1;
                *(s32 *)&lbl_80362AA8 = top;
            }
        }
        break;

    /* pool 2 / 3: the 2-slot window tables, guarded 0x400 from their watermark */
    case 2:
        {
            s32 *tbl = lbl_803629F4;
            s32 last = tbl[lbl_80362A9C];
            s32 room = lbl_80362AB4 - (last - 0x400);
            if (room < size) { while (1) { } }
            {
                s32 nn = lbl_80362A9C;
                s32 *tb = lbl_803629F4;
                s32 fst = tb[nn];
                if (fst + size <= lbl_80362AB4 + 0x400) {
                    s32 n2 = nn + 1;
                    ret = fst;
                    tb[n2] = ret + ((size + 0x1F) & QB_UNKNOWN_0xFFFFFFE0);
                    lbl_80362A88[nn] = 1;
                    lbl_80362A9C = n2;
                }
            }
        }
        break;

    case 3:
        {
            s32 *tbl = lbl_803629FC;
            s32 last = tbl[lbl_80362AA0];
            s32 room = lbl_80362AB8 - (last - 0x400);
            if (room < size) { while (1) { } }
            {
                s32 nn = lbl_80362AA0;
                s32 *tb = lbl_803629FC;
                s32 fst = tb[nn];
                if (fst + size <= lbl_80362AB8 + 0x400) {
                    s32 n2 = nn + 1;
                    ret = fst;
                    tb[n2] = ret + ((size + 0x1F) & QB_UNKNOWN_0xFFFFFFE0);
                    lbl_80362A8C[nn] = 1;
                    lbl_80362AA0 = n2;
                }
            }
        }
        break;

    /* empty label at value 4: costs no code, but it is what makes gcc balance
       the 5-node case list at index 2, i.e. retail's dispatch tree */
    case 4:
        break;
    }

    /* low-water mark of the bump pointer */
    {
        u32 v = fn_8001DB98();
        if (v < *(s32 *)&lbl_803001C0) {
            *(s32 *)&lbl_803001C0 = v;
        }
    }
    /* free space still available between consecutive blocks of each table */
    {
        s32 n = lbl_80362A94 - 1;
        lbl_803001C4 = 0;
        i = 0;
        if (i < n) {
            char *fl = lbl_80362A04;
            s32 *tbl = lbl_803627E4;
            s32 acc = 0;
            do {
                char f = fl[i];
                s32 nx = i + 1;
                if (f == 0) {
                    acc += tbl[nx] - tbl[i];
                }
                i = nx;
            } while (i < n);
            lbl_803001C4 = acc;
        }
    }
    {
        s32 n = lbl_80362A98 - 1;
        lbl_803001C8 = 0;
        i = 0;
        if (i < n) {
            char *fl = lbl_80362A68;
            s32 *p = lbl_80362974;
            s32 acc = 0;
            do {
                if (fl[i] == 0) {
                    acc += p[-1] - p[0];
                }
                i++;
                p++;
            } while (i < n);
            lbl_803001C8 = acc;
        }
    }
    return ret;
}
