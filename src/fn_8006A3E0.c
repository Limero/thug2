// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006A3E0-0x8006A4B0 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0x10[0x10];
    s16 unk0x10;
    char pad0x12[2];
    s32 unk0x14;
} VT;

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    __ps_t unk0x8;
    __ps_t unk0x10;
    s32 unk0x18;
} S6A3E0;

typedef struct {
    __ps_t a;
    __ps_t b;
} P2;

void fn_800697E8(s32, s32);
s32 *fn_80069838(s32 *);
void fn_80069EB8(s32, void *);
void *Mem_Alloc2(s32);

s32 fn_8006A3E0(S6A3E0 *arg0, s32 arg1) {
    VT *vt;
    s32 r29;
    s32 *d;
    s32 *r30;
    s32 *n;
    volatile s32 sp8;
    s32 cnt;
    s32 nxt;
    P2 *ps_src;
    P2 *ps_dst;

    vt = arg0->unk0x18;
    r29 = ((s32 (*)(void *))vt->unk0x14)((char *)arg0 + vt->unk0x10);
    if (r29 != 0) {
        fn_800697E8(r29, arg1);
        d = fn_80069838((s32 *)r29);
        if (*(s32 *)((char *)d + 0x17C) != 0) {
            d = fn_80069838((s32 *)r29);
            ps_src = (P2 *)((char *)arg0 + 8);
            ps_dst = (P2 *)((char *)d + 0x40);
            ps_dst->a = ps_src->a;
            ps_dst->b = ps_src->b;
            fn_80069EB8(r29, (char *)arg0 + 8);
        }
        r30 = *(s32 **)arg0;
        sp8 = (s32)r30;
        n = (s32 *)Mem_Alloc2(0xC);
        cnt = *(s32 *)((char *)arg0 + 4);
        nxt = r30[2];
        n[0] = r29;
        *(s32 *)((char *)arg0 + 4) = cnt + 1;
        n[2] = nxt;
        n[1] = (s32)r30;
        r30[2] = (s32)n;
        ((s32 *)n[2])[1] = (s32)n;
    }
    return r29;
}
