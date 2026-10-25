// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012614C-0x801261C0 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_803032A4;
extern s32 lbl_80303294[];
extern s32 lbl_8030329C[];
s32 fn_80011F94(void *, s32, s32, s32);
void fn_8012614C(s32 arg0, s32 arg1) {
    s32 *slot;
    void *obj;

    slot = &lbl_80303294[lbl_803032A4];
    obj = (void *)Mem_Alloc2(0x5C);
    *slot = fn_80011F94(obj, 0x64, arg0, arg1);
    lbl_8030329C[lbl_803032A4] = 1;
}
