// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800964EC-0x80096588 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
s32 Mem_Alloc2(s32);
s32 fn_80098B00(s32, s32);
extern char PSMTXRotRad[];
extern char lbl_8037B8F8[];
extern char lbl_8037B928[];
extern char lbl_8037B958[];
extern char lbl_8037B988[];
extern f32 lbl_80297484;
extern f32 lbl_80297488;
extern f32 lbl_8029748C;
extern f32 lbl_80297490;
extern s32 lbl_803018A8;
void fn_800964EC(void) {
    s32 *gp;
    s32 v;
    gp = &lbl_803018A8;
    v = fn_80098B00(Mem_Alloc2(0x18), 8);
    *gp = v;
    ((s32 (*)(s32, s32, f32)) PSMTXRotRad)((s32)lbl_8037B8F8, 0x79, lbl_80297484);
    ((s32 (*)(s32, s32, f32)) PSMTXRotRad)((s32)lbl_8037B928, 0x79, lbl_80297488);
    ((s32 (*)(s32, s32, f32)) PSMTXRotRad)((s32)lbl_8037B958, 0x79, lbl_8029748C);
    ((s32 (*)(s32, s32, f32)) PSMTXRotRad)((s32)lbl_8037B988, 0x79, lbl_80297490);
}
