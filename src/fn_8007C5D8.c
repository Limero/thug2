// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007C5D8-0x8007C6BC (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { f32 r, g, b, a; } C4;
typedef struct {
    char pad0x00[0x18];
    s32 vtbl;
    s32 unk0x1C;
    char pad0x20[0x80];
    C4 col0;
    C4 col1;
    char pad0xC0[0x1D0];
    s32 nodeCount;
} Cls_8007C5D8;
void fn_8005B314(void *arg0);
void fn_8005B594(void *arg0, s32 arg1);
void fn_8005B5C8(void *arg0, s32 arg1, s32 arg2);
extern f32 lbl_80295D8C;
extern f32 lbl_80295D90;
extern char lbl_80295DB8[];
extern s32 lbl_8030047C;
void *fn_8007C5D8(Cls_8007C5D8 *o) {
    void *pA;
    void *pB;
    f32 c0;
    f32 c1;
    s32 n;
    s32 n2;
    s32 i;
    s32 cnt;

    fn_8005B314(o);
    n = 0x1F;
    o->vtbl = (s32)lbl_80295DB8;
    do {
        n -= 1;
    } while (n != 0);
    pA = (char *)o + 0xA0;
    n2 = 0x1F;
    pB = (char *)o + 0xB0;
    do {
        n2 -= 1;
    } while (n2 != 0);
    o->unk0x1C = 0;
    fn_8005B594(o, 0);
    for (i = 0; i < lbl_8030047C; i++) {
        fn_8005B5C8(o, i, 0);
    }
    c0 = lbl_80295D8C;
    c1 = lbl_80295D90;
    o->col0.r = c0;
    *(f32 *)((char *)pA + 0x4) = c1;
    *(f32 *)((char *)pA + 0x8) = c0;
    *(f32 *)((char *)pA + 0xC) = c1;
    cnt = lbl_8030047C;
    o->col1.r = c0;
    *(f32 *)((char *)pB + 0x8) = c0;
    *(f32 *)((char *)pB + 0x4) = c1;
    *(f32 *)((char *)pB + 0xC) = c1;
    o->nodeCount = cnt;
    return o;
}
