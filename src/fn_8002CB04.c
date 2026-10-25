// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002CB04-0x8002CB4C (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    u32 f0 : 13;
    u32 f1 : 1;
    u32 f2 : 1;
    u32 f3 : 17;
} T2CB04Flags;
typedef struct {
    s32 unk0x00;
    s32 unk0x04;
    char _08[4];
    s32 unk0x0C;
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    char _24[0x50];
    u8 unk0x74;
    u8 unk0x75;
    char _76[0xF0];
    u16 unk0x166;
    T2CB04Flags bits;
} T2CB04;
register s32 bzero __asm__("r10");
register s32 zero __asm__("r0");
void *fn_8002CB04(void *arg0) {
    T2CB04 *p = (T2CB04 *)arg0;
    bzero = 0;
    zero = 0;
    p->unk0x75 = bzero;
    p->bits.f0 = zero;
    p->unk0x0C = zero;
    p->bits.f2 = 0;
    p->unk0x1C = zero;
    p->unk0x20 = zero;
    p->unk0x04 = zero;
    p->unk0x166 = zero;
    p->unk0x74 = bzero;
    p->unk0x14 = zero;
    p->unk0x18 = zero;
    p->unk0x10 = zero;
    return arg0;
}
