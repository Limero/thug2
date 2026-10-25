// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80253FF4-0x802541C8 (468B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_803CA340;

void fn_8024EBD8(void *heap, void *ptr);
void fn_80257CC4(void *dst, s32 size);
void fn_80255F18(void *p);
void fn_80255F5C(void *p);

extern void *lbl_803CA358[];
extern void *lbl_803CA350[];
extern void *lbl_80308040[];

typedef struct ThugCtx ThugCtx;
struct ThugCtx {
    s32 pad00[2];   /* 0x00 */
    s32 cnt0;       /* 0x08 — walk of arr0                                 */
    s32 cnt1;       /* 0x0C — walk of idx1[]/val1[] via lbl_803CA358[].[1] */
    s32 cnt2;       /* 0x10 — walk of idx2[]/val2[] via lbl_803CA350[].[2] */
    s32 cnt3;       /* 0x14 — walk of idx3[]/val3[] via lbl_80308040[].[2] */
    s32 cnt4;       /* 0x18 — walk of arr4[] (0x2C-stride tail array)      */
    s32 pad1C;
    s32 arr0[64];   /* 0x020 */
    s32 idx1[64];   /* 0x120 */
    s32 val1[64];   /* 0x220 */
    s32 idx2[64];   /* 0x320 */
    s32 val2[64];   /* 0x420 */
    s32 idx3[64];   /* 0x520 */
    s32 val3[64];   /* 0x620 */
    s32 arr4[64];   /* 0x720 */
    char pad820[0x300];
    void *tail;     /* 0xB20 — array of 0x2C-sized records */
};

typedef struct ThugHead ThugHead;
struct ThugHead {
    char pad00[0x1C];
    ThugCtx *ctx;
};

void fn_80253FF4(ThugHead *arg0) {
    ThugCtx *b;
    s32 i;
    s32 *w;
    void **tab;
    void *o;
    s32 heap;
    s32 t;
    register s32 o5 __asm__("r3");
    s32 off;

    b = arg0->ctx;
    if (b != NULL) {
        i = 0;
        if (i < b->cnt0) {
            w = b->arr0;
            do {
                t = w[0];
                w += 1;
                if (t != 0) {
                    heap = lbl_803CA340;
                    fn_8024EBD8(heap, t);
                }
            } while (++i < b->cnt0);
        }
        i = 0;
        if (i < b->cnt1) {
            tab = lbl_803CA358;
            w = b->val1;
            do {
                o = ((void **)tab[w[-0x40]])[1];
                ((void (*)(s32))o)(w[0]);
                w += 1;
            } while (++i < b->cnt1);
        }
        i = 0;
        if (i < b->cnt2) {
            tab = lbl_803CA350;
            w = b->val2;
            do {
                o = ((void **)tab[w[-0x40]])[2];
                ((void (*)(s32))o)(w[0]);
                w += 1;
            } while (++i < b->cnt2);
        }
        i = 0;
        if (i < b->cnt3) {
            tab = lbl_80308040;
            w = b->val3;
            do {
                o = ((void **)tab[w[-0x40]])[2];
                ((void (*)(s32))o)(w[0]);
                w += 1;
            } while (++i < b->cnt3);
        }
        i = 0;
        if (i < b->cnt4) {
            off = 0;
            w = b->arr4;
            do {
                o5 = w[0];
                w += 1;
                if (o5 != 0) {
                    fn_80255F18(o5);
                }
                if (b->tail != 0) {
                    fn_80255F5C((void *)((char *)b->tail + off));
                }
                off += 0x2C;
            } while (++i < b->cnt4);
        }
        if (b->tail != 0) {
            heap = lbl_803CA340;
            fn_8024EBD8(heap, b->tail);
        }
        heap = lbl_803CA340;
        fn_8024EBD8(heap, b);
    }
    fn_80257CC4(arg0, 0x20);
}
