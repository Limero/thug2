// WIP DRAFT (PARKED, non-matching) — 90.0% (36/40 insns), 2026-09-20.
// family=hand range=0x8012DF78-0x8012E018 size=160B
// 2026-10-08 root cause for the 4-word residual: the two swapped webs are
// the *compiler-generated loop-increment temporaries* of `for (i = 0; i <= 0xFFF; i++)`
// plus `p++` on the 0xC-byte struct pointer, i.e. `i+1` (want r28, got r27) and
// `p+0xC` (want r27, got r28). Both are loop-inverted into the preheader by the
// compiler and NOTHING in the C names them, so a doc-75 declaration pin has no
// target. The loop variables themselves are already right in both (i in r9, p in
// r29 / `mr r9,r28`-style tails), so this is not a source-spelling problem either.
// Only route: introduce named next-value temporaries and pin them to r28/r27
// (structure: rotated do/while, `ni = i + 1; np = p + 1; i = ni; p = np;` before
// the back-edge test) — unverified, and it risks the 36 words that already match.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Bulk free of the 0x1000 x 0xC slot table at lbl_803032B8: for each of
// 0..0xFFF cells free the cell's 0x8 list (each node frees its 0x4 then
// itself), then the cell's own 0x4, finally the table itself.
//
// Matching keys found (all 36 reachable words agree):
//   * lbl_803032B8 must be declared as the POINTER it is
//     (`extern Unk_41A32F3B *lbl_803032B8;`). With `extern char lbl[]` +
//     a `*(T **)` cast the load lands straight in the loop register and the
//     whole body shifts by one `mr r29, r0` — the test must read the global
//     and then copy it into the callee-saved induction pointer.
//   * The cell type must be a real 0xC struct (Unk_41A32F3B: s32 unk0x0/0x4/
//     0x8); indexing an 0xA4 struct emits `mulli r9, r11, 0xa4` instead of
//     want's plain `addi` induction step.
//   * counter is u32 (`cmplwi r9, 0xfff`) with `i <= 0xFFF`, not `i < 0x1000`.
//
// 2026-10-12: decl-order swap (i first) inert; `register u32 i
// __asm__("r28")` pin -> DIFF (worse). Both reverted.
// 2026-10-16: pinned next-temps route tried two ways, both 70.0% (28/40,
// first-miss@8): (a) rotated do/while with ni=r28/np=r27 and manual
// increments; (b) for with empty incr slot + manual increments at body end
// (char* and s32 np types). The for-incr `i++`/`p++` is load-bearing for the
// entry/preheader shape; manual increments break it before the residual
// region. Reverted.
// PARKED on a pure local-alloc tie: the two loop-increment temps come out
// with the original's registers exchanged. The original increments r9 by 1
// into r28 and adds 0xc to r29 into r27, then copies r28 back to r9 and r27
// back to r29, while this draft produces the same two adds and copies with
// the r27/r28 destinations swapped.
// (both `addi`s and both `mr`s are otherwise identical). Independent of
// source shape — tried and all still 4 misses: for/while/do-while, `p++` vs
// `(u8*)p + 0xC`, increment order both ways, `i++/++i`, void* walker,
// indexed `arr[i]`, for-incr-slot membership (i++ in body + p++ in the
// for-statement, 2026-10-17: identical 4 misses, reverted), and the
// `-fno-gcse` flag the old draft carried.
#include "types.h"
#include "structs.h"
extern Unk_41A32F3B *lbl_803032B8;
void Mem_Free_3(void *);
void fn_8012DF78(void) {
    Unk_41A32F3B *p;
    Unk_41A32F3B *node;
    Unk_41A32F3B *next;
    u32 i;

    if (lbl_803032B8 != NULL) {
        p = lbl_803032B8;
        for (i = 0; i <= 0xFFF; i++) {
            node = (Unk_41A32F3B *)p->unk0x8;
            if (node != NULL) {
                do {
                    next = (Unk_41A32F3B *)node->unk0x8;
                    Mem_Free_3((void *)node->unk0x4);
                    Mem_Free_3(node);
                    node = next;
                } while (node != NULL);
            }
            if (p->unk0x4 != 0) {
                Mem_Free_3((void *)p->unk0x4);
            }
            p++;
        }
        Mem_Free_3(lbl_803032B8);
        lbl_803032B8 = NULL;
    }
}
