// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033310-0x80033360 (80B). Byte-identical.

// family=m2c range=0x80033310-0x80033360 size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_803003C0[];
extern s32 lbl_803003D0;
s32 *fn_80012110(Unk_C8FEE62D *);
void fn_80033310(s32 arg0) {
    void *entry = lbl_803003C0[lbl_803003D0];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
