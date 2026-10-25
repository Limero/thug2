// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800142FC-0x8001448C (400B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern f32 lbl_80290A20;   /* 0.25f  */
extern f64 lbl_80290A28;   /* 0.25   */
extern f32 lbl_802FFF48;
extern f32 lbl_802FFF4C;
extern s32 lbl_802FFE6C;
extern s64 lbl_802FFF50;   /* frame counter */
extern char lbl_803142B8[];

typedef union {
    s64 q;
    struct {
        s32 hi;
        s32 lo;
    } h;
} Tim;

typedef struct {
    f32 f0;
    f32 f1;
    f64 f2;
    s32 arr[4];
    Tim cur;
    Tim prev;
    s32 idx;
} St;

extern s64 fn_800144A0(void);
extern f32 fn_800144D4(void);

void fn_800142FC(void) {
    volatile double _dummy;
    St *g = (St *)lbl_803142B8;
    s32 *p;
    s32 i;
    register s32 v __asm__("r11");
    s32 n;
    s32 sumA;
    s32 sumB;
    s32 k;
    register s32 clo __asm__("r11");

    lbl_802FFF50 += 1;
    g->prev = g->cur;
    g->cur.q = fn_800144A0();
    i = g->idx;
    clo = g->cur.h.lo;
    g->arr[i] = clo - g->prev.h.lo;
    g->idx = i + 1;
    if (g->idx == 4) {
        g->idx = 0;
    }
    p = g->arr;
    sumB = 0;
    sumA = 0;
    for (k = 0; k < 4; k++) {
        v = *p++;
        sumA += v;
        if ((u32)(v - 2) > 8U) {
            v = 1;
        }
        if (v > 4) {
            v = 4;
        }
        sumB += v;
    }
    *(f32 *)lbl_803142B8 = (f32)sumB * lbl_80290A20;
    *(f64 *)((char *)lbl_803142B8 + 8) = (f64)sumA * lbl_80290A28;
    lbl_802FFF48 = lbl_802FFF4C;
    n = lbl_802FFE6C;
    *(f32 *)((char *)lbl_803142B8 + 4) = *(f32 *)lbl_803142B8 / (f32)n * fn_800144D4();
}
