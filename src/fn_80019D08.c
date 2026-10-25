// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80019D08-0x80019D58 (80B). Byte-identical.

// family=m2c range=0x80019D08-0x80019D58 size=80B


// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_80303264[];
extern s32 lbl_80303274;
s32 *fn_80012110(Unk_C8FEE62D *);
// CStruct_new @ 0x80019D08
void CStruct_new(s32 arg0) {
    void *entry = lbl_80303264[lbl_80303274];
    if (entry == NULL) {
        Mem_Alloc(arg0);
        return;
    }
    fn_80012110(entry);
}
