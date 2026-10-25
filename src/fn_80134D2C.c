// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134D2C-0x80134D7C (80B). Byte-identical.

// family=m2c range=0x80134D2C-0x80134D7C size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_80303418[];
extern s32 lbl_80303428;
s32 *fn_80012110(Unk_C8FEE62D *);
void fn_80134D2C(s32 arg0) {
    void *entry = lbl_80303418[lbl_80303428];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
