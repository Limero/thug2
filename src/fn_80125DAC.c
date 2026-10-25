// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125DAC-0x80125E20 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_80303428;
extern s32 lbl_80303418[];
extern s32 lbl_80303420[];
s32 fn_80011F94(void *, s32, s32, s32);
void fn_80125DAC(s32 arg0, s32 arg1) {
    s32 *slot;
    void *obj;

    slot = &lbl_80303418[lbl_80303428];
    obj = (void *)Mem_Alloc2(0x5C);
    *slot = fn_80011F94(obj, 0x18, arg0, arg1);
    lbl_80303420[lbl_80303428] = 1;
}
