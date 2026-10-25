// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F4C4-0x8009F514 (80B). Byte-identical.

// family=m2c range=0x8009F4C4-0x8009F514 size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_80303220[];
extern s32 lbl_80303230;
s32 *fn_80012110(Unk_C8FEE62D *);
void fn_8009F4C4(s32 arg0) {
    void *entry = lbl_80303220[lbl_80303230];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
