// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800777F0-0x80077840 (80B). Byte-identical.

// family=m2c range=0x800777F0-0x80077840 size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_8030147C[];
extern s32 lbl_8030148C;
s32 *fn_80012110(Unk_C8FEE62D *);
void fn_800777F0(s32 arg0) {
    void *entry = lbl_8030147C[lbl_8030148C];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
