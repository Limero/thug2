// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8008528C-0x80085394 (264B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef struct {
    __ps_t p0, p1;
    u8     b0, b1, b2;
    char   pad0[5];
    __ps_t p2, p3;
    u8     b3, b4, b5;
    char   pad1[5];
    __ps_t p4, p5;
    u8     b6, b7, b8;
    char   pad2[5];
} Dest_t;

/* source element at arg0+0x1800, stride 0xC */
typedef struct {
    s32 w0, w1, w2;
} A_t;

void fn_8005A7E8(void *, void *, __ps_t *, s32, u32);

/* frame template: scratch12 at r1+8, scratchPS[6] at r1+0x18 */
typedef struct {
    s32    a0, a1, a2;
    char   pad[4];
    __ps_t B[6];
} Fr_t;

void fn_8008528C(void *arg0) {
    s32 n;
    s32 i;
    Dest_t *d;
    A_t *s;
    Fr_t fr;

    n = *(s32 *)((char *)arg0 + 0x2A00);
    if (n < 0) {
        return;
    }
    i = 0;
    d = (Dest_t *)((char *)arg0 + 0x2A10);
    s = (A_t *)((char *)arg0 + 0x1800);

    while (i <= *(s32 *)((char *)arg0 + 0x2A00)) {
        fr.a0 = s->w0;
        fr.a1 = s->w1;
        fr.a2 = s->w2;
        fr.B[0] = d->p0;
        fr.B[1] = d->p1;
        fr.B[2] = d->p2;
        fr.B[3] = d->p3;
        fr.B[4] = d->p4;
        fr.B[5] = d->p5;
        fn_8005A7E8(s, &fr.a0, fr.B, 0, 3);
        d->b0 = ((u8 *)&fr.a0)[0];
        d->b1 = ((u8 *)&fr.a0)[1];
        d->b2 = ((u8 *)&fr.a0)[2];
        d->b3 = ((u8 *)&fr.a0)[4];
        d->b4 = ((u8 *)&fr.a0)[5];
        d->b5 = ((u8 *)&fr.a0)[6];
        d->b6 = ((u8 *)&fr.a0)[8];
        d->b7 = ((u8 *)&fr.a0)[9];
        d->b8 = ((u8 *)&fr.a0)[10];
        s++;
        d++;
        i++;
    }
}
