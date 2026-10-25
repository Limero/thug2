// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC2A4-0x801FC2F4 (80B). Byte-identical.

// family=m2c range=0x801FC2A4-0x801FC2F4 size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_80305F4C[];
extern s32 lbl_80305F5C;
s32 *fn_80012110(Unk_C8FEE62D *);
void fn_801FC2A4(s32 arg0) {
    void *entry = lbl_80305F4C[lbl_80305F5C];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
