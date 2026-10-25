// PARKED 2026-10-03: DIFF, 95/178 words (46.6% masked; want_got.py
// "diffs 95 46.63%"), object .text 736B vs want 712B (6 extra insns).
// reproduce: cd <repo> && \
// LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//       tools/test_wip_drafts.py --addr 0x800EDB3C
//   Baseline was DIFF 20.2% (m2c body). What this rewrite fixed:
//   (a) QB_CHAINID/ QB_LOCK_POS/ QB_LINK_INDEX/ QB_FIRST_LINK/ QB_LAST_LINK /
//       QB_DIST/ QB_LINK_ON/ QB_LINK_OFF/ QB_HIDE calls + the circular
//       walker loop are right; LOCKPOS now matches want WORD-FOR-WORD from the
//       prologue through 0x800EDC7C (the m2c draft had `0; 0;` there).
//   (b) `volatile` on the walker pointers cur/end is LOAD-BEARING: want keeps
//       both in memory (0x18/0x20 in case LOCKPOS, 0x08/0x10 in case
//       SETCOLLINFO) and re-reads `arg0->unk0x1C` every iteration.  Without
//       volatile ngccc keeps cur in r30 and drops the end store; with it the
//       callee-saved set becomes r27-r31 exactly as want (was r26-r29).
//   (c) the guard `if (cur != end)` must test NON-volatile temporaries
//       (`c0 = head ? head->next : 0; cur = c0; end = head; if (c0 != head)`)
//       — testing the volatile pair adds 2 lwz+cmpw want doesn't have.
//   (d) 4-byte pad slots are needed between cur/end and after end (want has
//       0x1c and 0x24 unused; see `volatile s32 pad_a/pad_b`).
//   REMAINING DIFF, in order of value:
//   1. CASE SETCOLLINFO's walker slots land at 0x1c/0x24 (ngccc reuses case
//      LOCKPOS's pad slots) instead of want's 0x08/0x10.  want's layout is
//      vec@0x08(16B) cur@0x18 pad@0x1c end@0x20 pad@0x24 chainid@0x28
//      link@0x2c | cur2@0x08 pad@0xc end2@0x10 chainid2@0x30 link2@0x34,
//      i.e. the vec's 16-byte slot is SHARED with case SETCOLLINFO's four
//      4-byte slots (exact-size slot reuse), so those decls must be reached
//      first in ngccc's slot walk.  Reordering the two case BODIES to
//      SETCOLLINFO-first shrinks the frame to 0x48 instead — wrong.
//   2. The LOCKPOS copy is want's 7-instruction
//      mulli/psq_l/add/addi/psq_st 0(r9)/psq_l/psq_st 8(r9); see the note on
//      Vec_t below for the four shapes already measured.
//   3. `psq_stx`/duplicate-mulli and the 4 stw shape; also got keeps a
//      `stw r0,0x684(r11)` only if Base_t's pads are mis-sized (a real bug I
//      hit — pad24 must be 0x654, not 0x658, or dist/link_on/link_off slide
//      4 bytes late and a phantom store lands at 0x684).
//   RULED OUT: -Os (frame drops to 0x38, wrong); 8-byte-aligning the pointer
//   type to stretch cur/end slots (no effect — GCC sizes pointer slots at 4);
//   QB_CHAIN_SETVISIBILITY is 0x982C70E5 in qb_constants.h and the binary's
//   `lis r0,-0x67d4` is the same value (earlier "0x988270E5" was a misread);
//   declaring the copy as `__ps_t` array pairs, `dst[link*10]` indexed pairs,
//   or per-member `dst->v0/v1` (all measured, see below).
//   NEXT IDEA: after fixing (1), try expressing the copy as a 16-byte write
//   through a `Vec_t *` whose address comes from `&((Link_t *)cur->base)[link]`
//   — ngccc folds a constant field offset into the store displacement
//   whenever the index is a scalar multiply (giving psq_st 40/48(r9)), but it
//   keeps an explicit `addi` when the +0x28 is folded into the INDEXED form
//   `(char *)base + 0x28` treated as an array base.  Neither yet produced
//   psq_st 0(r9)/8(r9); a frame-struct (recipes' pad idiom) destination is the
//   other untried shape.
// WIP DRAFT (non-matching) — C body re-derived from the original disassembly
// family=m2c range=0x800EDB3C-0x800EDE04 size=712B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(void *, s32, s32 *, s32);
s32 GetVector(void *, s32, void *, s32);
s32 GetFloat(void *, s32, f32 *, s32);
s32 GetInteger(void *, s32, s32 *, s32);
s32 ContainsFlag(void *, s32);

/* 16-byte vector out of GetVector(QB_LOCK_POS).  MEASURED: this 4-field
 * POD assignment scores best (46.6%) but emits 4 lwz + 4 stw; a body of two
 * explicit __ps_t element writes DOES emit the psq_l/psq_st pair run want
 * has (45.5%) yet uses psq_stx + a duplicated mulli instead of want's
 * materialised `addi r9,0x28` + psq_st 0(r9)/8(r9).  Both are one small
 * shape away; see the PARKED note. */
typedef struct {
    f32 x, y, z, w;
} Vec_t;
/* chain link record: 0x50 bytes, lock position as a PS pair at +0x28 */
#define LINK_VEC_OFS 0x28
#define LINK_STRIDE_P 0x50
/* chain data block hung off each walker node.  The trailing __ps_t only
 * exists to give Base_t 8-byte alignment: want's walker-pointer slots are
 * 8 apart (0x18/0x20, 0x08/0x10), i.e. 8-aligned pointer slots. */
typedef struct {
    s32 id;
    char pad4[0x1C];
    s32 nlinks;
    char pad24[0x654];
    f32 dist;
    s32 link_on;
    s32 link_off;
    __ps_t pad_align;
} Base_t;
/* circular walker node: {chain data block, next} */
typedef struct Node_s {
    Base_t *base;
    struct Node_s *next;
} Node_t;

s32 fn_800EDB3C(Unk_C8FEE62D *arg0, s32 arg1, CStruct *arg2) {
    u32 swv1;

    switch (swv1 = arg1) {
    case QB_CHAIN_LOCKPOS: {
        Vec_t vec;
        s32 chainid;
        s32 link;
        Node_t *volatile cur;
        volatile s32 pad_a;
        Node_t *volatile end;
        volatile s32 pad_b;
        Node_t *head;
        Node_t *c0;
        chainid = 0;
        GetChecksum_2(arg2, QB_CHAINID, &chainid, 1);
        GetVector(arg2, QB_LOCK_POS, &vec, 1);
        head = (Node_t *)arg0->unk0x1C;
        c0 = (head != NULL) ? head->next : NULL;
        cur = c0;
        end = head;
        if (c0 != head) {
            do {
                if (cur->base->id == chainid) {
                    s32 ret;
                    link = 0;
                    ret = GetInteger(arg2, QB_LINK_INDEX, &link, 0);
                    if (ret == 0) {
                        if (ContainsFlag(arg2, QB_FIRST_LINK) != 0) {
                            link = ret;
                        } else if (ContainsFlag(arg2, QB_LAST_LINK) == 0) {
                            link = cur->base->nlinks - 1;
                        }
                    }
                    *(Vec_t *)((char *)cur->base + LINK_VEC_OFS + link * LINK_STRIDE_P) = vec;
                }
                end = (Node_t *)arg0->unk0x1C;
                cur = cur->next;
            } while (cur != end);
        }
        return 1;
    }
    case QB_CHAIN_SETCOLLINFO: {
        s32 chainid2;
        s32 link2;
        Node_t *volatile cur2;
        volatile s32 pad_c;
        Node_t *volatile end2;
        volatile s32 pad_d;
        Node_t *head2;
        Node_t *c1;
        chainid2 = 0;
        GetChecksum_2(arg2, QB_CHAINID, &chainid2, 1);
        head2 = (Node_t *)arg0->unk0x1C;
        c1 = (head2 != NULL) ? head2->next : NULL;
        cur2 = c1;
        end2 = head2;
        if (c1 != head2) {
            do {
                if (cur2->base->id == chainid2) {
                    link2 = 0;
                    GetFloat(arg2, QB_DIST, &cur2->base->dist, 0);
                    if (GetInteger(arg2, QB_LINK_ON, &link2, 0) != 0) {
                        cur2->base->link_on = link2;
                    }
                    if (GetInteger(arg2, QB_LINK_OFF, &link2, 0) != 0) {
                        cur2->base->link_off = link2;
                    }
                }
                end2 = (Node_t *)arg0->unk0x1C;
                cur2 = cur2->next;
            } while (cur2 != end2);
        }
        return 1;
    }
    case QB_CHAIN_SETVISIBILITY:
        arg0->unk0x48 = ContainsFlag(arg2, QB_HIDE);
        return 1;
    default:
        return 2;
    }
}