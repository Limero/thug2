// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D16C0-0x801D17AC (236B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_801D16C0(Unk_F65AFC12 *arg0) {
    f32 t[4];
    register __ps_t *pt __asm__("r10");
    register __ps_t *b __asm__("r8");
    register char *p1 __asm__("r9");
    register char *p2 __asm__("r11");
    register char *p3 __asm__("r9");
    register f32 n1 __asm__("fr12");
    register f32 n0 __asm__("fr0");
    register f32 n2 __asm__("fr11");
    register f32 n3 __asm__("fr13");

    pt = (__ps_t *)t;
    b = (__ps_t *)((char *)arg0 + 0x20);
    __asm__("" : "+r"(b));
    p1 = arg0->unk0xC;
    n1 = ((Unk_7BB6AF0E *)p1)->unk0x9C;
    n0 = ((Unk_7BB6AF0E *)p1)->unk0x98;
    n2 = ((Unk_7BB6AF0E *)p1)->unk0xA0;
    n3 = ((Unk_7BB6AF0E *)p1)->unk0xA4;
    t[1] = -n1;
    t[0] = -n0;
    t[2] = -n2;
    t[3] = -n3;
    ((Unk_B1766B04 *)p1)->unk0x98 = pt[0];
    ((Unk_B1766B04 *)p1)->unk0xA0 = pt[1];
    p2 = arg0->unk0xC;
    n1 = ((Unk_7BB6AF0E *)p2)->unk0x7C;
    n0 = ((Unk_7BB6AF0E *)p2)->unk0x78;
    n2 = ((Unk_7BB6AF0E *)p2)->unk0x80;
    n3 = ((Unk_7BB6AF0E *)p2)->unk0x84;
    t[1] = -n1;
    t[0] = -n0;
    t[2] = -n2;
    t[3] = -n3;
    ((Unk_11E536AA *)p2)->unk0x78 = pt[0];
    ((Unk_11E536AA *)p2)->unk0x80 = pt[1];
    p3 = arg0->unk0xC;
    arg0->unk0x20 = ((Unk_0B6E8BDA *)p3)->unk0x78;
    arg0->unk0x28 = ((Unk_0B6E8BDA *)p3)->unk0x80;
    arg0->unk0x30 = ((Unk_0B6E8BDA *)p3)->unk0x88;
    arg0->unk0x38 = ((Unk_0B6E8BDA *)p3)->unk0x90;
    b[4] = ((Unk_0B6E8BDA *)p3)->unk0x98;
    b[5] = ((Unk_0B6E8BDA *)p3)->unk0xA0;
    arg0->unk0x50 = ((Unk_0B6E8BDA *)p3)->unk0xA8;
    arg0->unk0x58 = ((Unk_0B6E8BDA *)p3)->unk0xB0;
    arg0->unk0x3B4 ^= 1;
}
