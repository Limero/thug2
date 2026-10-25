// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC2F4-0x801FC344 (80B). Byte-identical.

// family=m2c range=0x801FC2F4-0x801FC344 size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_80305F60[];
extern s32 lbl_80305F70;
s32 *fn_80012110(Unk_C8FEE62D *);
void fn_801FC2F4(s32 arg0) {
    void *entry = lbl_80305F60[lbl_80305F70];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
