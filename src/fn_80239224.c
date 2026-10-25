// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80239224-0x80239298 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_802FFE98;
extern s32 lbl_803060AC;

s32 fn_80243EF0(void);
void fn_8000F2F8(s32, s32);
s32 Mem_Alloc2(s32);
s32 fn_802435B8(s32, s32);
s32 fn_80243638(s32, s32);
void fn_8000F320(s32);

void fn_80239224(char *arg0) {
    s32 temp_r29;
    s32 temp_r0;
    s32 obj;
    s32 *field;

    temp_r29 = fn_80243EF0();
    field = (s32 *)(arg0 + 0x177CC);
    temp_r0 = lbl_802FFE98;
    fn_8000F2F8(temp_r0, *(s32 *)(temp_r0 + 0x12C));
    obj = fn_802435B8(Mem_Alloc2(0x108), 0);
    *field = obj;
    fn_80243638(obj, temp_r29);
    fn_8000F320(lbl_802FFE98);
    lbl_803060AC = temp_r29;
}
