// range 0x8006FBCC-0x8006FC80 (180B). Byte-identical.
// Identification: double-buffered object-pool reclaim, called from the item
// constructor fn_8006FB1C (when its arg1 & 1). The pool selector
// lbl_8030148C toggles per frame; this object's `this` either falls inside
// pool[lbl_8030148C]'s range (fn_800120EC = [lo, hi) range check) and is
// prepended to that pool's free list (CompactPool_Free), else the sibling pool
// [lbl_8030148C ^ 1] is tried, else the object is actually freed via
// Mem_Free2. lbl_8030147C = the 2-entry pool table.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void *lbl_8030147C[];
extern s32 lbl_8030148C;
s32 fn_800120EC(CStruct *, void *);
void CompactPool_Free(Unk_C8FEE62D *, s32 *);

void fn_8006FBCC(void *arg0) {
    void *cand = lbl_8030147C[lbl_8030148C];
    if (cand != 0 && fn_800120EC(cand, arg0) != 0) {
        CompactPool_Free(cand, arg0);
    } else {
        cand = lbl_8030147C[lbl_8030148C ^ 1];
        if (cand != 0 && fn_800120EC(cand, arg0) != 0) {
            CompactPool_Free(cand, arg0);
        } else if (arg0 != 0) {
            Mem_Free2((s32)arg0);
        }
    }
}
