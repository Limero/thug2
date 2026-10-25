// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128EF4-0x80128F44 (80B). Byte-identical.

// family=m2c range=0x80128EF4-0x80128F44 size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_80303170[];
extern s32 lbl_80303180;
s32 *fn_80012110(Unk_C8FEE62D *);
void fn_80128EF4(s32 arg0) {
    void *entry = lbl_80303170[lbl_80303180];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
