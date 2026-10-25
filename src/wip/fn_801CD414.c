// WIP DRAFT (non-matching) — hand-rebuilt from disasm; scalar init + PS pair copies.
// family=m2c range=0x801CD414-0x801CD540 size=300B
// FLAG: -mps-float -Os
// PARKED (~40% ps_diff raw, cascaded; structure aligned): init-body fully
// reconstructed incl. PS pair-copies via __ps_t. Remaining diffs are 4
// register-web artifacts GCC won't split: (a) want re-materializes
// *(arg0+0xC) into FRESH regs r8/r9/r11 per group (volatile reloads +
// volatile memory barriers still CSE to one r8 web here); (b) b20 base
// wants r7, got r10; (c) p104 pair color f12 vs f13; (d) li r0,0 must sit
// between stfs 4(r11)/8(r11) — staged named-zero (+r barrier) gets
// const-propagated and rematerialized late. Same allocator-artifact family
// as docs/parkings/06 M5.0o (fn_8015E868) / FPR-coloring wall.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
extern f32 lbl_802AD2B8;
extern f32 lbl_802AD2BC;
void fn_801CD414(Unk_7C733D0A *arg0) {
    Unk_6A70655D *o;
    CStruct *p58;
    Unk_64D775D7 *b20;
    CStruct *b60;
    f32 z;
    f32 t13;
    f32 res;
    s32 zero;
    __ps_t p96;
    __ps_t p104;
    res = fn_8014030C(QB_PHYSICS_ROLLING_FRICTION, 1, arg0->unk0xC);
    o = *((void * volatile *)&arg0->unk0xC);
    z = lbl_802AD2B8;
    __asm__ volatile("" ::: "memory");
    arg0->unk0x378 = res;
    p58 = (char *)o + (s32)0x58;
    t13 = lbl_802AD2BC;
    __asm__ volatile("" ::: "memory");
    b20 = (char *)arg0 + (s32)0x20;
    __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0x58) = z;
    __asm__ volatile("" ::: "memory");
    b60 = (char *)arg0 + (s32)0x60;
    __asm__ volatile("" ::: "memory");
    *((f32 *)&p58->unk0x4) = z;
    zero = 0;
    __asm__("" : "+r"(zero));
    *((f32 *)&p58->unk0x8) = z;
    *((f32 *)&p58->unk0xC) = t13;
    __asm__ volatile("" ::: "memory");
    o = *((void * volatile *)&arg0->unk0xC);
    *((f32 *)&o->unk0x7C) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0x80) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0x84) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0x88) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0x90) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0x94) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0x98) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0x9C) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0xA4) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0xA8) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0xAC) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0xB0) = z; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0xB4) = t13; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0x78) = t13; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0x8C) = t13; __asm__ volatile("" ::: "memory");
    *((f32 *)&o->unk0xA0) = t13;
    __asm__ volatile("" ::: "memory");
    o = *((void * volatile *)&arg0->unk0xC);
    arg0->unk0x20 = *((__ps_t *)&o->unk0x78); __asm__ volatile("" ::: "memory");
    arg0->unk0x28 = *((__ps_t *)&o->unk0x80); __asm__ volatile("" ::: "memory");
    arg0->unk0x30 = *((__ps_t *)&o->unk0x88); __asm__ volatile("" ::: "memory");
    arg0->unk0x38 = *((__ps_t *)&o->unk0x90); __asm__ volatile("" ::: "memory");
    b20->unk0x20 = *((__ps_t *)&o->unk0x98); __asm__ volatile("" ::: "memory");
    b20->unk0x28 = *((__ps_t *)&o->unk0xA0); __asm__ volatile("" ::: "memory");
    arg0->unk0x50 = *((__ps_t *)&o->unk0xA8); __asm__ volatile("" ::: "memory");
    arg0->unk0x58 = *((__ps_t *)&o->unk0xB0);
    __asm__ volatile("" ::: "memory");
    *((f32 *)&((Unk_5F85C510 *)arg0)->unk0x60) = z;
    __asm__ volatile("" ::: "memory");
    *((f32 *)&b60->unk0xC) = t13;
    *((f32 *)&b60->unk0x8) = z;
    *((f32 *)&b60->unk0x4) = t13;
    __asm__ volatile("" ::: "memory");
    arg0->unk0x34C = zero;
    __asm__ volatile("" ::: "memory");
    p96 = ((Unk_5F85C510 *)arg0)->unk0x60;
    p104 = arg0->unk0x68;
    __asm__ volatile("" ::: "memory");
    arg0->unk0x70 = p96;
    __asm__ volatile("" ::: "memory");
    arg0->unk0x33C = zero;
    __asm__ volatile("" ::: "memory");
    arg0->unk0x78 = p104;
    __asm__ volatile("" ::: "memory");
    arg0->unk0x80 = p96;
    __asm__ volatile("" ::: "memory");
    arg0->unk0x88 = p104;
}
