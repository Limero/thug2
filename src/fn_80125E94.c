// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125E94-0x80125F08 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_80303274;
extern s32 lbl_80303264[];
extern bool lbl_8030326C[];
s32 fn_80011F94(void *, s32, s32, s32);
void fn_80125E94(s32 arg0, s32 arg1) {
    s32 *slot;
    void *obj;

    slot = &lbl_80303264[lbl_80303274];
    obj = (void *)Mem_Alloc2(0x5C);
    *slot = fn_80011F94(obj, 0x08, arg0, arg1);
    lbl_8030326C[lbl_80303274] = 1;
}
