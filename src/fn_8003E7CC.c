// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E7CC-0x8003E81C (80B). Byte-identical.

// family=m2c range=0x8003E7CC-0x8003E81C size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_80303280[];
extern s32 lbl_80303290;
s32 *fn_80012110(Unk_C8FEE62D *);
void fn_8003E7CC(s32 arg0) {
    void *entry = lbl_80303280[lbl_80303290];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
