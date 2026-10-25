// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FDDA0-0x800FDE38 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern char lbl_8029C490[];
extern void *Mem_Alloc2(s32 size);
extern void fn_80102444(Unk_FFCFB14C * dst, Unk_FFCFB14C * src);

void *fn_800FDDA0(Unk_7A62D47E *arg0) {
    register s32 f_c8 __asm__("r11");
    register s32 f_ce __asm__("r7");
    register u16 f_cc __asm__("r10");
    Unk_7A62D47E *ret;
    __ps_t t;

    ret = Mem_Alloc2(0xD8);
    fn_80102444((Unk_FFCFB14C *)ret, (Unk_FFCFB14C *)arg0);
    f_c8 = arg0->unk0xC8;
    f_ce = *(s32 *)((char *)arg0 + 0xCE);
    f_cc = arg0->unk0xCC;
    ret->unk0xC = (s32)lbl_8029C490;
    ret->unk0xC8 = f_c8;
    t = arg0->unk0xA8;
    ret->unk0xCC = f_cc;
    ret->unk0xA8 = t;
    t = arg0->unk0xB0;
    *(s32 *)((char *)ret + 0xCE) = f_ce;
    ret->unk0xB0 = t;
    t = arg0->unk0xB8;
    ret->unk0x4 |= 0x8000;
    ret->unk0xB8 = t;
    t = arg0->unk0xC0;
    ret->unk0x8 = 0;
    ret->unk0xC0 = t;
    return ret;
}
