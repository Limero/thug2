// WIP DRAFT (non-matching) — honest-C reconstruction of a GX XF texture-upload kernel.
// family=m2c range=0x80252554-0x80252864 size=784B
//
// PARKED 2026-10-06: unmatchable from C in ngccc (GCC 2.95.2 ProDG). Two
// ingredients of the WANT have no C spelling:
//   * 40 `mtspr 0x39a,data` / `mtspr 0x39b,index` XF-register pushes plus the
//     `mfspr 0x398` PE/FIFO-wait spins. Arbitrary-SPR access is unreachable from
//     C — `mtspr(...)` / `__builtin_mtspr(...)` compile to a CALL, never the
//     opcode (see src/wip/fn_80003300.c and its mtspr census).
//   * `bl fn_80252864` is entered with its operands in the callee-saved r20..r23
//     instead of the ABI r4..r7 — a private hand-written-asm interface
//     (docs/parkings/41, fingerprint #4). The r20..r23 `register` pins below
//     reach it from C (declarations; they emit zero instructions).
// The previous revision transcribed the whole body as inline asm, which is banned
// (a whole-body transcription fakes a match), so it was replaced by this honest
// skeleton. Reachable from C: the prologue arithmetic, the pointer walk and the
// single `bl`; the SPR traffic is not, so the body cannot be aligned.
#include "types.h"

typedef struct {
    u16 n;              /* 0x00: unit count, inner loop count = n >> 4  */
    u16 h;              /* 0x02: texture height in rows                 */
    u16 w;              /* 0x04: texture width in pixels                */
    u16 pad0x06;
    u8 *p0;             /* 0x08 */
    u8 *p1;             /* 0x0C */
    u8 *p2;             /* 0x10 */
} Tex_t;

/* mtspr 0x39a,<data> ; mtspr 0x39b,<index> — GX XF register push (no C spelling). */
extern void GXLoadXf(u32 data, u32 index);
/* `mfspr 0x398` spin until the extracted field is below <limit> (no C spelling). */
extern void GXWaitPe(u32 limit);
/* Reads its operands from r3 and r20..r23 (private, non-ABI interface). */
void fn_80252864(void *cur);

void fn_80252554(Tex_t *t, u8 *row, s32 rs, s32 h, u8 *buf) {
    register u8 *pa0 __asm__("r20");
    register u8 *pa1 __asm__("r21");
    register u8 *pa2 __asm__("r22");
    register u8 *pa3 __asm__("r23");
    u32 n;
    u32 w4;
    u32 rows;
    u32 stride;
    u8 *p0;
    u8 *p1;
    u8 *p2;
    u8 *c0;
    u8 *c1;
    u8 *c2;
    u8 *cur;
    u8 *da;
    u8 *db;
    u8 *q;
    u8 *sw;
    u32 i;

    n = (u32)t->n >> 4;
    w4 = (u32)t->w << 2;
    rows = (u32)(t->h <= h ? t->h : h) >> 3;
    stride = (u32)rs << 1;
    p0 = t->p0;
    p1 = t->p1;
    p2 = t->p2;
    c0 = p0;
    c1 = p1;
    c2 = p2;
    cur = row;
    q = buf + 0x1C0;

    /* prologue: XF push for the first unit, addressed against buf */
    GXLoadXf((u32)c1 & ~0xFu, (u32)buf | 0x16);
    GXLoadXf((u32)c2 & ~0xFu, ((u32)buf + 0x20) | 0x16);
    GXLoadXf((u32)c0 & ~0xFu, ((u32)buf + 0x40) | 0x1A);
    GXLoadXf(((u32)c0 & ~0xFu) + w4, (((u32)buf + 0x40) | 0x1A) + 0x40);
    da = cur;
    GXWaitPe(1);
    cur += 0x20;

    /* unit loop: CTR = n.  The first row enters via the `bdnz` (increment
     * first, n-1 units); each later row enters at body_unit (n units). */
    i = n;
    if (--i != 0)
        goto inc_unit;

after_units:
    if (--rows != 0) {
        p0 += w4 << 1;
        p1 += w4 >> 1;
        p2 += w4 >> 1;
        row += stride << 3;
        c0 = p0;
        c1 = p1;
        c2 = p2;
        cur = row;
        i = n;
        goto body_unit;
    }

    /* epilogue: final conversion + XF push, addressed against buf */
    pa0 = buf + 0x40;
    pa1 = buf;
    pa2 = buf + 0x20;
    pa3 = buf + 0xC0;
    fn_80252864(da);
    pa0 = buf + 0x80;
    pa1 = buf + 0x10;
    pa2 = buf + 0x30;
    pa3 = buf + 0x140;
    fn_80252864(da);
    GXWaitPe(8);
    GXLoadXf((u32)da & ~0xFu, ((u32)buf + 0xC0) | 6);
    GXLoadXf(((u32)da & ~0xFu) + stride, (((u32)buf + 0xC0) | 6) + 0x20);
    GXLoadXf(((u32)da & ~0xFu) + stride * 2, (((u32)buf + 0xC0) | 6) + 0x40);
    GXLoadXf(((u32)da & ~0xFu) + stride * 3, (((u32)buf + 0xC0) | 6) + 0x60);
    GXLoadXf(((u32)da & ~0xFu) + stride * 4, (((u32)buf + 0xC0) | 6) + 0x80);
    GXLoadXf(((u32)da & ~0xFu) + stride * 5, (((u32)buf + 0xC0) | 6) + 0xA0);
    GXLoadXf(((u32)da & ~0xFu) + stride * 6, (((u32)buf + 0xC0) | 6) + 0xC0);
    GXLoadXf(((u32)da & ~0xFu) + stride * 7, (((u32)buf + 0xC0) | 6) + 0xE0);
    return;

inc_unit:
    c1 += 0x20;
    c2 += 0x20;
    c0 += 0x40;

body_unit:
    GXLoadXf((u32)c1 & ~0xFu, (u32)q | 0x16);
    GXLoadXf((u32)c2 & ~0xFu, ((u32)q + 0x20) | 0x16);
    GXLoadXf((u32)c0 & ~0xFu, ((u32)q + 0x40) | 0x1A);
    GXLoadXf(((u32)c0 & ~0xFu) + w4, (((u32)q + 0x40) | 0x1A) + 0x40);

    db = cur;
    pa0 = buf + 0x40;
    pa1 = buf;
    pa2 = buf + 0x20;
    pa3 = buf + 0xC0;
    fn_80252864(cur);
    pa0 = buf + 0x80;
    pa1 = buf + 0x10;
    pa2 = buf + 0x30;
    pa3 = buf + 0x140;
    fn_80252864(cur);
    cur += 0x20;

    sw = buf;
    buf = q;
    q = sw;
    sw = da;
    da = db;
    db = sw;

    GXWaitPe(4);
    GXLoadXf((u32)db & ~0xFu, ((u32)buf + 0xC0) | 6);
    GXLoadXf(((u32)db & ~0xFu) + stride, (((u32)buf + 0xC0) | 6) + 0x20);
    GXLoadXf(((u32)db & ~0xFu) + stride * 2, (((u32)buf + 0xC0) | 6) + 0x40);
    GXLoadXf(((u32)db & ~0xFu) + stride * 3, (((u32)buf + 0xC0) | 6) + 0x60);
    GXLoadXf(((u32)db & ~0xFu) + stride * 4, (((u32)buf + 0xC0) | 6) + 0x80);
    GXLoadXf(((u32)db & ~0xFu) + stride * 5, (((u32)buf + 0xC0) | 6) + 0xA0);
    GXLoadXf(((u32)db & ~0xFu) + stride * 6, (((u32)buf + 0xC0) | 6) + 0xC0);
    GXLoadXf(((u32)db & ~0xFu) + stride * 7, (((u32)buf + 0xC0) | 6) + 0xE0);

    if (--i != 0)
        goto inc_unit;
    goto after_units;
}

// NOTE: WANT overview and why this is parked.
//  - The routine is a NeGo texture-upload / mip-walk kernel: `t` is a 0x14-byte
//    descriptor (u16 count/height/width + three plane pointers), `row` is the
//    destination, `rs` a row stride (scaled x2), `h` a height cap (min with
//    t->h, then >>3 rows), and `buf` a 0x1C0+-byte scratch page.
//  - Every unit performs 4 XF-register pushes (plane addresses masked to 16
//    bytes, `mtspr 0x39a/0x39b`), two `fn_80252864` conversions into buf, then 8
//    more XF pushes of the conversion result at row stride. buf and q are
//    ping-ponged each unit, as are the `da`/`db` row pointers.
//  - WANT loads `t` fields with `lhz` (so n/h/w are u16) and the plane pointers
//    with `lwz`; `arg0` is dead after `mr r3, r4`, i.e. r3 is reused as `cur`.
//  - No C construct emits the SPR pushes or the r20..r23 callee interface, so
//    the object can only ever match a prefix; the file is kept as honest,
//    compile-clean documentation of the algorithm rather than as a match.
