// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800629D4-0x80062AD4 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 fn_80102A40(void *, void *, void *, void *, void *, void *, void *);
extern s32 fn_80103234(void *);
extern void fn_8000728C(f32 *, f32 *);
bool fn_800629D4(Unk_FFAD6788 *arg0, CStruct *arg1) {
    s32 off;
    s32 i;
    char *bb;
    char *p5;
    char *p6;
    char *p3;
    char *p7;
    char *q;
    char *base;
    s32 count;
    s32 n;
    s32 o7;
    s32 t3;

    count = arg1->unk0x4;
    base = (char *)arg1 + 0x10;
    arg0->unk0x8C = (s32) base;
    arg0->unk0x88 = count;
    n = arg1->unk0xC;
    p3 = base + (count << 6);
    t3 = (s32)(n * 3LL);
    p5 = p3 + t3;
    p5 = (char *)(((s32)p5 + 3) & 0xFFFFFFFC);
    q = p5 + (n * 0xA);
    if (n & 1) {
        q = q + 2;
    }
    o7 = *(s32 *)q;
    p6 = q + 4;
    i = 0;
    p7 = p6 + o7;
    if (i < arg1->unk0x4) {
        bb = (char *)arg0 + 0x90;
        off = 0;
        do {
            fn_80102A40((char *)(s32)arg0->unk0x8C + off, (void *)(s32)arg0->unk0xC8, p3, 0, p5, p6, p7);
            i++;
            fn_80103234((char *)(s32)arg0->unk0x8C + off);
            fn_8000728C((f32 *)bb, (f32 *)(off + (s32)arg0->unk0x8C + 0x10));
            fn_8000728C((f32 *)bb, (f32 *)(off + (s32)arg0->unk0x8C + 0x20));
            off += 0x40;
        } while (i < arg1->unk0x4);
    }
    return true;
}
