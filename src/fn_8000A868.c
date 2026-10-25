// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A868-0x8000A924 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80311290;
extern s32 lbl_80311294;
extern s32 lbl_80311298;
extern s32 lbl_8031129C;
extern s32 lbl_802FFE98;
void fn_8000F2F8(void *, void *);
void fn_8000F320(void *);
void *Mem_Alloc(s32);
void fn_8000A868(void) {
    u32 *var_r9;
    u32 *var_r11;
    u32 var_ctr;
    u32 var_ctr_2;

    fn_8000F2F8((void *)(s32)lbl_802FFE98, *(void **)((char *)(s32)lbl_802FFE98 + 0x118));
    lbl_80311290 = (s32)Mem_Alloc(0x1011);
    lbl_80311294 = (s32)Mem_Alloc(0x4004);
    lbl_80311298 = (s32)Mem_Alloc(0x4404);
    lbl_8031129C = (s32)Mem_Alloc(0x4004);
    fn_8000F320((void *)(s32)lbl_802FFE98);
    var_ctr = 0x100;
    var_r9 = (u32 *)((char *)lbl_80311298 + 0x4004);
    do {
        *var_r9 = 0x1000;
        var_r9 = (u32 *)((char *)var_r9 + 4);
    } while (--var_ctr != 0);
    var_ctr_2 = 0x1000;
    var_r11 = (u32 *)((char *)lbl_8031129C + 0x3FFC);
    do {
        *var_r11 = 0x1000;
        var_r11 = (u32 *)((char *)var_r11 - 4);
    } while (--var_ctr_2 != 0);
}
