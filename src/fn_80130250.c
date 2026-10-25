// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80130250-0x801302F0 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8012FDC0(CStruct *);
void fn_80130250(CStruct *arg0) {
    u16 sp8;
    s32 var_r29;
    s32 var_r3;
    s32 temp_r9;
    void *temp_r11;
    void *restore;
    var_r29 = 0;
    temp_r9 = (s32)arg0->unk0x10 + 1;
    arg0->unk0x10 = (void *)temp_r9;
    fn_8012CB60(&sp8, temp_r9);
    temp_r11 = arg0->unk0x10;
    arg0->unk0x10 = (void *)(temp_r11 + 2);
    restore = (void *)(temp_r11 + sp8);
    if ((s32) *(u8 *)((char *)temp_r11 + 0x2) == 0x39) {
        var_r29 = 1;
        arg0->unk0x10 = (void *)(temp_r11 + 3);
    }
    var_r3 = fn_8012FDC0(arg0);
    if (arg0->unk0x10 != NULL) {
        if (var_r29 != 0) {
            var_r3 ^= 1;
        }
        if (var_r3 == 0) {
            arg0->unk0x10 = restore;
        }
    }
}