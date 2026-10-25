// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC3D8-0x801FC44C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_80305F70;
extern s32 lbl_80305F60[];
extern bool lbl_80305F68[];
s32 fn_80011F94(void *, s32, s32, s32);
void fn_801FC3D8(s32 arg0, s32 arg1) {
    s32 *slot;
    void *obj;

    slot = &lbl_80305F60[lbl_80305F70];
    obj = (void *)Mem_Alloc2(0x5C);
    *slot = fn_80011F94(obj, 0x14, arg0, arg1);
    lbl_80305F68[lbl_80305F70] = 1;
}
