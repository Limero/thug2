// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012224-0x80012270 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void CompactPool_Free(Unk_C8FEE62D *, s32 *);
extern s32 *lbl_802FFF08[];
void fn_80012224(s32 arg0, void *arg1) {
    void *entry = lbl_802FFF08[arg0];
    if (entry != NULL) {
        CompactPool_Free(entry, (void *)arg1);
        return;
    }
    if (arg1 != 0) {
        Mem_Free2(arg1);
    }
}
