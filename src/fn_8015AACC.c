// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015AACC-0x8015AC48 (380B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern bool lbl_80305DF4;
extern s32 lbl_803A00D0[];
s32 Script_RunScript(s32, s32, s32, s32, s32);
s32 CStruct_delete(CStruct *, s32);
void Mem_Free(void *);
// DIAGNOSED (sched dumps via -da; dumps removed after): sched1 emits
// [stw][cmp] for block 11 (both ready t=1, same-cycle LSU+IU, LSU prints
// first) and sched2 keeps it; but the analogous single-store block 2 is
// re-chained by sched2 to [cmp][stw]. Difference: block 11's stw1 has an
// in-block anti-dep successor (stw2, volatile order), giving it height to
// tie cmp; block 2's lone store has height 0 < cmp height 1 so cmp wins.
// Tried from this: CStruct*-typed sp28 to break the TBAA anti-dep (inert —
// volatile forces aliasing in sched-deps), deleting stw2 (realloc to
// saved regs, confounded), sp20-inside-loop (realloc, 93.7%). Untried:
// a type/decl shape that removes stw1's in-block successor without
// changing bytes. All branch targets positionally verified (0 mismatches)
// so this is pure scheduling, no hidden CFG difference.
// PARKED: 97.9% — sole residue is one scheduler coin-flip at loop2 entry. The
// original orders the r0-versus-r11 compare, the sp20 store, the sp28 store
// and the end-merge branch, while this draft stores sp20 first and only then
// compares before the sp28 store and branch. It resists statement reordering,
// duplicated/crossjumped arms (grew function), assignment-in-condition,
// double-compare CSE, -fno-schedule-insns/-insns2/-sched-spec/-
// sched-interblock/-rerun-loop-opt/-unroll-loops. Everything else EXACT.
bool ScriptFlushCutsceneDestroyList(void) {
    volatile s32 sp8[2];
    volatile s32 sp10[2];
    volatile s32 sp18[2];
    volatile s32 sp20[2];
    volatile s32 sp28[2];
    volatile s32 sp30[2];
    volatile s32 sp38[2];
    volatile s32 sp40[2];
    volatile s32 sp48[2];
    volatile s32 sp50[2];
    CStruct *head;
    void *cand;
    void *curscan;
    CStruct *objptr;
    CStruct *advcur;
    void *advnext;
    void *termv;
    Unk_C7387A53 *entry;
    CStruct *head2;
    void *cand2;
    CStruct *cursor2;
    void *n2;
    void *n2b;
    void *headchk;
    void *latcha;
    void *latchb;
    s32 n30;
    void *term2;
    s32 *listp;
    s32 zero;

    head = (void *)lbl_803A00D0[0];
    lbl_80305DF4 = 1;
    sp8[0] = (s32)head;
    cand = NULL;
    if (head != NULL) {
        cand = *((void * *)&head->unk0x4);
    }
    sp10[0] = (s32)cand;
    if (cand != head) {
        zero = 0;
        do {
            curscan = (void *)sp10[0];
            objptr = *(void **)curscan;
            Script_RunScript(objptr->unk0x8, objptr->unk0xC, 0, 0, 0);
            entry = *(void **)(void *)sp10[0];
            if (entry != NULL) {
                if (entry->unk0xC != 0) {
                    CStruct_delete(entry->unk0xC, 3);
                    entry->unk0xC = zero;
                }
                Mem_Free(entry);
            }
            advcur = (void *)sp10[0];
            termv = (void *)sp8[0];
            advnext = *((void * *)&advcur->unk0x4);
            sp10[0] = (s32)advnext;
        } while (advnext != termv);
    }
    head2 = (void *)lbl_803A00D0[0];
    listp = lbl_803A00D0;
    cand2 = NULL;
    if (head2 != NULL) {
        cand2 = *((void * *)&head2->unk0x4);
    }
    sp20[0] = (s32)cand2;
    /* Non-volatile alias for this one store: it is the SECOND volatile store
       in the block, so its presence gives the first store an in-block
       anti-dependency and enough height to tie the cmpw.  Dropping the
       qualifier on this store only (the slot is still read volatile in the
       latch) should let sched2 re-chain the block to [cmpw][stw][stw]. */
    *(s32 *)(void *)&sp28[0] = (s32)head2;
    if (cand2 != head2) {
        do {
            cursor2 = (void *)sp20[0];
            headchk = (void *)listp[0];
            sp40[0] = (s32)cursor2;
            n2 = *((void * *)&cursor2->unk0x4);
            sp38[0] = (s32)cursor2;
            sp20[0] = (s32)n2;
            sp50[0] = (s32)cursor2;
            n2b = *((void * *)&cursor2->unk0x4);
            sp48[0] = (s32)cursor2;
            sp38[0] = (s32)n2b;
            if (cursor2 != headchk) {
                *(s32 *)(*((void * *)&cursor2->unk0x8) + 4) = cursor2->unk0x4;
                *(s32 *)(*((void * *)&cursor2->unk0x4) + 8) = cursor2->unk0x8;
                Mem_Free(cursor2);
                listp[1] -= 1;
            }
            n30 = sp38[0];
            latcha = (void *)sp20[0];
            latchb = (void *)sp28[0];
            sp30[0] = n30;
        } while (latcha != latchb);
    }
    lbl_80305DF4 = 0;
    sp18[0] = sp20[0];
    return true;
}
