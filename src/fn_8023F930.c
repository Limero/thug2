// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023F930-0x8023F980 (80B). Byte-identical.

// family=m2c range=0x8023F930-0x8023F980 size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_803060C4[];
extern s32 lbl_803060D4;
s32 *fn_80012110(Unk_C8FEE62D *);
void fn_8023F930(s32 arg0) {
    void *entry = lbl_803060C4[lbl_803060D4];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
