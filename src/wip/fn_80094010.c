// WIP DRAFT (non-matching) — fully hand-reconstructed from the want
// disassembly (the m2c body was unusable: it had invented file-static
// "sp10/sp14/sp18/unkspE" stack reads and a 0x98 frame for a 0x848 want).
// family=m2c range=0x80094010-0x80094564 size=1364B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// MEASURED 2026-10-04: object is EXACTLY 1364 B / 341 insns (== want), 12.32 %
// masked-EXACT (was 2.1 % / DIFF). Every basic block now emits the same
// *sequence of instruction kinds* as the want, at the same stack offsets for the
// int->double scratch slot (0x810/0x814) and the same literal pool entries.
//
// PARKED — remaining blocker is pure cc1 register allocation, which is
// downstream of RTL differences C cannot reach directly:
//   * GPR set: want saves r21-r31 (11), draft saves r22-r31 (10). The want
//     keeps 11 values simultaneously live (incl. two that are already dead:
//     r22 = f->tbl2 dies in loop A, r30 is reused n*6 -> ab -> fw), so cc1
//     never needs to recycle their slots.
//   * FP loop: want puts 0x43300000 in r3 and the loop counter in r4; draft
//     puts them in r4 and r30. Every `stw rX,0x810(r1)` in the loop therefore
//     mismatches (~20 words).
//   * FPR permutation: want has half=f7, fw=f8, fh2=f9; draft has fw=f7,
//     fh2=f8, half=f9. 2^52->f10 and 1.25*2^52->f13 agree. Source order of
//     those three assignments was measured (first/middle/last) and makes NO
//     difference, so this is decided by cc1's pseudo ordering, not by C.
//   * frame: want 0x848 with the save area at 0x81c. Frame = local bytes +
//     4*saved_regs, so 0x848 needs BOTH 11 saved regs (+4) and 4 more local
//     bytes above the cvt temp (+4). cvt at 0x810 is reached with
//     LOCAL_BYTES=0x804; the extra 4 bytes have no natural home in this C.
// Negative results / things already ruled out (do not retry blindly):
//   * `(f32)(f64)x` already emits the full magic (stw 0x43300000 / stw x /
//     lfd / fsub / frsp). Writing the union + `- lbl_80297238` by hand is
//     IDENTICAL and double-subtracts if you also keep the cast.
//   * `-fno-schedule-insns2`, `(u8)` casts on the tbl indices, and moving the
//     `half`/f8/f9 assignments were all measured: no improvement.
//   * The want's `lis r8,0xFFFF8029 / lwz r0,-0x4a20(r8)` access to
//     lbl_8037B5E0 cannot be reproduced standalone: cc1 only emits that
//     base+offset form when the .bss section layout is known.
#include "types.h"

#define BSWAP32(x) ((((x) >> 24) & 0xFF) | (((x) >> 8) & 0xFF00) | (((x) << 8) & 0xFF0000) | ((x) << 24))
#define BSWAP16(x) ((u32)((((x) << 8) & 0xFF00) | ((x) >> 8)))

extern f64 lbl_80297238;   /* 2^52        */
extern f32 lbl_80297240;   /* 0.5f        */
extern f64 lbl_80297248;   /* 1.25 * 2^52 */
extern void *lbl_8037B5E0;

void *fn_80023E94(void *);
void *Mem_Alloc2(s32);
void *Mem_Alloc(s32);
void *memcpy(void *, const void *, u32);
extern void memset(void *, s32, u32);
void DCFlushRange(void *, u32);

typedef struct {
    s32 f0;
    s32 f1;
    s32 count;
    s32 w;
    s32 h;
} FontHdr;

typedef struct {
    f32 x0, x1, x2, x3;
    u16 k0, k1, k2, pad;
} Glyph;

typedef struct {
    u16 a, b, c;
} CharRec;

typedef struct {
    u16 a, b, c, d;
} Metric;

typedef struct {
    s32    w0;
    Metric m;
    s32    w1;
} GlyphHdr;

#define LOCAL_BYTES 0x804
typedef union {
    FontHdr  hdr;
    GlyphHdr gh;
    CharRec  ch[LOCAL_BYTES / 6];
    u8       raw[LOCAL_BYTES];
} Local;

typedef struct {
    s32    v0;
    s32    v1;
    Glyph *glyphs;
    u8     tbl[0x100];
    u8     tbl2[0x20];
    u8     mode;
    void  *next;
    u8    *data;
    u8    *dataend;
    s32    w;
    s32    h;
    s32    pad;
    f32    scale;
} FontInst;

void *fn_80094010(u8 *arg0) {
    u8 *p;
    u8 ch;
    FontHdr *fh;
    FontInst *f;
    Local tmp;
    s32 v0;
    s32 v1;
    s32 n;
    s32 i;
    u8 *cp;
    u8 *mstart;
    s32 msize;
    s32 fw;
    s32 fh2;
    s32 ab;
    f32 f8;
    f32 f9;
    f32 half;
    Metric *m;
    Glyph *g;
    CharRec *c;
    u8 *align;
    s32 j;

    m = &tmp.gh.m;
    p = arg0;
    if (*p != 0) {
        do {
            ch = *p;
            if ((u32)(ch - 0x41) <= 0x19) {
                *p = ch + 0x20;
            }
            p++;
        } while (*p != 0);
    }
    fh = fn_80023E94(arg0);
    f = Mem_Alloc2(0x18C);
    tmp.hdr = *fh;
    v0 = BSWAP32(tmp.hdr.w);
    v1 = BSWAP32(tmp.hdr.h);
    n = BSWAP32(tmp.hdr.count);
    f->v0 = v0;
    f->v1 = v1;
    f->mode = tmp.hdr.f1 >> 24;
    memset(f->tbl, 0, 0x100);
    memset(f->tbl2, 0, 0x20);
    f->glyphs = Mem_Alloc(n * 0x18);
    cp = (u8 *)fh + 0x14;
    memcpy(&tmp, cp, n * 6);
    cp += n * 6;

    if (f->mode == 1) {
        i = 0;
        g = f->glyphs;
        c = tmp.ch;
        if (i < n) {
            do {
                s16 t;
                g->k2 = 0;
                g->k2 = BSWAP16(c->a);
                t = BSWAP16(c->b);
                if (t >= 0) {
                    f->tbl[t] = (u8)i;
                } else {
                    f->tbl2[~t] = (u8)i;
                }
                g++;
                c++;
            } while (++i < n);
        }
        mstart = cp + 0x10;
        msize = n * 8;
    } else if (f->mode == 2) {
        i = 0;
        g = f->glyphs;
        c = tmp.ch;
        if (i < n) {
            do {
                u32 a;
                u32 b;
                g->k2 = 0;
                g->k2 = BSWAP16(c->a);
                a = BSWAP16(c->b);
                b = BSWAP16(c->c);
                f->tbl[a] = (u8)i;
                if ((a >> 8) != 0xFF) {
                    f->tbl[a >> 8] = (u8)i;
                }
                if ((b & 0xFF) != 0xFF) {
                    f->tbl[b & 0xFF] = (u8)i;
                }
                if ((b >> 8) != 0xFF) {
                    f->tbl[b >> 8] = (u8)i;
                }
                g++;
                c++;
            } while (++i < n);
        }
        mstart = cp + 0x10;
        msize = n * 8;
    } else {
        mstart = cp + 0x10;
        msize = n * 8;
    }

    if (f->tbl2[0x1F] != 0) {
        for (i = 0; i < 0x100; i++) {
            if (f->tbl[i] == 0 && i != 0x41 && i != 0x61) {
                f->tbl[i] = f->tbl2[0x1F];
            }
            if (i <= 0x1E && f->tbl2[i] == 0) {
                f->tbl2[i] = f->tbl2[0x1F];
            }
        }
    }

    tmp.gh = *(GlyphHdr *)cp;
    fw = BSWAP16(tmp.gh.m.a);
    fh2 = BSWAP16(tmp.gh.m.b);
    ab = fw * fh2;
    align = (u8 *)(((u32)mstart + 0x1F) & ~(u32)0x1F);
    for (j = ab + 0x1FF; j >= 0; j--) {
        align[j] = mstart[j];
    }
    DCFlushRange(align, ab + 0x200);
    f->data = align;
    f->w = fw;
    f->h = fh2;
    f->dataend = align + ab;
    memcpy(&tmp, mstart + ab + 0x220, msize | 4);

    half = lbl_80297240;
    f8 = (f32)(f64)fw;
    f9 = (f32)(f64)fh2;
    g = f->glyphs;
    i = n;
    if (i > 0) {
        do {
            u32 u0 = BSWAP16(m->a);
            u32 u1 = BSWAP16(m->b);
            u32 u2 = BSWAP16(m->c);
            u32 u3 = BSWAP16(m->d);
            g->x0 = ((f32)(f64)u0 + half) / f8;
            g->x1 = ((f32)(f64)u1 + half) / f9;
            g->k0 = u2;
            g->k1 = u3;
            g->x2 = g->x0 + ((f32)(f64)u2 + half) / f8;
            g->x3 = g->x1 + ((f32)(f64)u3 + half) / f9;
            g++;
            m++;
        } while (--i != 0);
    }

    f->next = lbl_8037B5E0;
    lbl_8037B5E0 = f;
    f->scale = (f32)(f64)f->glyphs[f->tbl[0x49]].k0;
    return f;
}
