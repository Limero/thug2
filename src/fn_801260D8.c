// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801260D8-0x8012614C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_803032D0;
extern s32 lbl_803032C0[];
extern s32 lbl_803032C8[];
s32 fn_80011F94(void *, s32, s32, s32);
void fn_801260D8(s32 arg0, s32 arg1) {
    s32 *slot;
    void *obj;

    slot = &lbl_803032C0[lbl_803032D0];
    obj = (void *)Mem_Alloc2(0x5C);
    *slot = fn_80011F94(obj, 0xF8, arg0, arg1);
    lbl_803032C8[lbl_803032D0] = 1;
}
