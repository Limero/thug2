// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC364-0x801FC3D8 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_80305F5C;
extern s32 lbl_80305F4C[];
extern bool lbl_80305F54[];
s32 fn_80011F94(void *, s32, s32, s32);
void fn_801FC364(s32 arg0, s32 arg1) {
    s32 *slot;
    void *obj;

    slot = &lbl_80305F4C[lbl_80305F5C];
    obj = (void *)Mem_Alloc2(0x5C);
    *slot = fn_80011F94(obj, 0x38, arg0, arg1);
    lbl_80305F54[lbl_80305F5C] = 1;
}
