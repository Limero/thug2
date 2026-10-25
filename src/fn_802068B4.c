// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802068B4-0x80206938 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_802FFE98;
extern s32 lbl_80366478;
void fn_8000F2F8(void *, s32);
s32 fn_8005CA70(s32, s32, s32, s32, s32);
void fn_8000F320(void *);
void fn_8005C070(s32, s32);
void fn_8005C580(s32);
void fn_8005CC88(s32, s32);

void fn_802068B4(void *arg0, s32 arg1) {
    s32 texture;
    fn_8000F2F8((void *)(s32)lbl_802FFE98, *(s32 *)((char *)(s32)lbl_802FFE98 + 0x118));
    texture = fn_8005CA70(lbl_80366478, arg1, 1, 1, 0);
    fn_8000F320((void *)(s32)lbl_802FFE98);
    fn_8005C070(*(s32 *)((char *)arg0 + 0x20), texture);
    fn_8005C580(texture);
    fn_8005CC88(lbl_80366478, texture);
}
