// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800679E8-0x80067BA4 (444B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void fn_80062D44(void *arg0);
extern f32 lbl_8029466C;
extern char lbl_80294670[];
extern char lbl_80294688[];
s32 Mem_Alloc(s32);
void fn_80062BBC(void *arg0);

Unk_DCEB657B *fn_800679E8(Unk_DCEB657B *arg0, s32 arg1, s32 arg2) {
    s32 ctr;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 off;
    s32 buf;
    u8 fill;
    void *base;
    void *p;

    fn_80062D44(arg0);
    i = arg2 - 1;
    arg0->unk0xF8 = arg1;
    arg0->unk0x84 = arg2;
    arg0->unk0x20 = (s32)lbl_80294670;
    arg0->unk0x8 = (s32)lbl_80294688;
    arg0->unk0x94 = 0;
    base = Mem_Alloc((arg2 * 0x30) | 8) + 8;
    *(s32 *)((char *)base - 8) = arg2;
    p = base;
    if (arg2 != 0) {
        do {
            fn_80062BBC(p);
            p += 0x30;
        } while (0 != i--);
    }
    arg0->unk0x100 = (s32)base;
    arg0->unk0x124 = Mem_Alloc((arg2 * 3) << 2);
    buf = Mem_Alloc(8);
    j = 1;
    do {
    } while (0 != j--);
    arg0->unk0x114 = buf;
    buf = Mem_Alloc(8);
    k = 1;
    do {
    } while (0 != k--);
    arg0->unk0x118 = buf;
    buf = Mem_Alloc(8);
    l = 1;
    do {
    } while (0 != l--);
    arg0->unk0x11C = buf;
    fill = 0x80;
    ctr = 2;
    off = 0;
    do {
        *(u8 *)(off + arg0->unk0x114) = fill;
        *(u8 *)(off + arg0->unk0x114 + 1) = fill;
        *(u8 *)(off + arg0->unk0x114 + 2) = fill;
        *(u8 *)(off + arg0->unk0x114 + 3) = fill;
        *(u8 *)(off + arg0->unk0x118) = fill;
        *(u8 *)(off + arg0->unk0x118 + 1) = fill;
        *(u8 *)(off + arg0->unk0x118 + 2) = fill;
        *(u8 *)(off + arg0->unk0x118 + 3) = fill;
        *(u8 *)(off + arg0->unk0x11C) = fill;
        *(u8 *)(off + arg0->unk0x11C + 1) = fill;
        *(u8 *)(off + arg0->unk0x11C + 2) = fill;
        *(u8 *)(off + arg0->unk0x11C + 3) = fill;
        off += 4;
        ctr -= 1;
    } while (ctr != 0);
    arg0->unk0x110 = lbl_8029466C;
    arg0->unk0x128 = (s32)(arg0->unk0x128 | 4);
    return arg0;
}
