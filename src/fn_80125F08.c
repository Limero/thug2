// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125F08-0x80125F7C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_8030316C;
extern s32 lbl_8030315C[];
extern bool lbl_80303164[];
s32 fn_80011F94(void *, s32, s32, s32);
void fn_80125F08(s32 arg0, s32 arg1) {
    s32 *slot;
    void *obj;

    slot = &lbl_8030315C[lbl_8030316C];
    obj = (void *)Mem_Alloc2(0x5C);
    *slot = fn_80011F94(obj, 0x10, arg0, arg1);
    lbl_80303164[lbl_8030316C] = 1;
}
