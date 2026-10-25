// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128F44-0x80128F94 (80B). Byte-identical.

// family=m2c range=0x80128F44-0x80128F94 size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_8030315C[];
extern s32 lbl_8030316C;
s32 *fn_80012110(Unk_C8FEE62D *);
void fn_80128F44(s32 arg0) {
    void *entry = lbl_8030315C[lbl_8030316C];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
