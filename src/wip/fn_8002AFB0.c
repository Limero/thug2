// WIP DRAFT (non-matching) — C body rebuilt by hand from the DOL disassembly.
// family=m2c range=0x8002AFB0-0x8002B8E4 size=2356B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// =====================================================================
// PARKED 2026-10-30: FAIL (did not compile) -> <see STATUS line>
// The inherited m2c body did not COMPILE: three `memcpy' arity errors
// ("too many arguments to function 'memcpy'" x2, "too few arguments" x1).
// Every one is a hard error in ProDG cc1 2.95.2 even though it is printed
// with a `warning:`-shaped message (AGENTS 6dg).
// =====================================================================
//
// TARGET 0x8002AFB0, want 2356 B = 589 instructions (size:0x934 in symbols.txt).
// ProDG game-code zone: GPR + FPR, NO paired-single / VMX words anywhere in the
// 589 instructions, so tools/ps_diff.py / the capstone-stall caveat do not apply.
//
// ---------------------------------------------------------------------
// FRAME MAP (the want prologue adjusts the stack by 0xd0, saves the link
// register, saves f30 at 0xc0 and f31 at 0xc8, saves r14 onward at 0x78,
// and spills the link value at 0xd4)
//   closed form (AGENTS 6db GPR-only / 6fk FPR): Gsave = 0x78, nSavedGPRs = 18
//   (r14..r31) => L = Gsave-8 = 0x70 of locals; frame = Gsave + 4*n + 8*nFPR
//   = 0x78 + 0x48 + 0x10 = 0xd0.  Locals region r1+0x08 .. r1+0x78.
//     r1+0x08  sp8   16B  {u32 w; f32 f1,f2,f3}   (r20; memcpy src, arg1==3 arm)
//     r1+0x18  sp18  24B  address-taken buffer    (stored to 0x58(r1); memcpy
//                                                   src in the arg1==4 arm)
//     r1+0x30  sp30  16B  {u16 h; f32 f1,f2,f3}   (converted output, loop 2)
//     r1+0x40  sp40   8B  {u16 w; s16 x,y,z}      (r7 = r12 = &sp40)
//     r1+0x48  sp48   8B  {u16 w; s16 x,y,z}      (r8 = r4 = &sp48)
//     r1+0x50  sp50   4B  arg0->unk0x14            (r23 in loop 2)
//     r1+0x54  sp54   4B  fn_8002D018(obj,0)       (memcpy dst base, loop 2)
//     r1+0x58  sp58   4B  &sp18
//     r1+0x5c..0x6f      20B  NO ACCESSOR in want (padding / 8-align slack)
//     r1+0x70  cvt     8B  int->f64 pair {hi = 0x43300000 @+0, lo @+4}
//     r1+0x78  stmw r14 (18 GPRs) .. r1+0xc0 ; f30 @0xc0 ; f31 @0xc8 ; LR @0xd4
//   Modelled with a frame-template struct holding the layout explicitly
//   (AGENTS 6q-86 / 6dy: every interior gap is an explicit `char pad[]`).
//
// ---------------------------------------------------------------------
// DECODED CONSTANTS (all verified present in config/G2TE52/symbols.txt)
//   lbl_80300388 .data    size 0x8   frame counter      (lis -0x7fd0 + 0x388)
//   lbl_80300390 .data    size 0x8   cached {u32,u32} key pair
//   lbl_80362CD8 .bss     size 0x6   u16 palette, 8-byte stride
//   lbl_80362CDE .bss     size 0x7FA u16 palette, 8-byte stride (0x6 apart!)
//   lbl_803634D8 .bss     size 0x800 u16 palette, 8-byte stride (loop-2 table)
//   lbl_80291670 .rodata2 double 0x4330000080000000 (2^52+2^31; the int->f64
//                        pool constant GCC's own expander subtracts)
//   lbl_80291678 .rodata2 float  loop-1 scale, MULTIPLIED
//   lbl_8029167C .rodata2 float  loop-2 scale, DIVIDED
//   0x80026BEC  .text            fn_8002D030's 2nd arg (lis -0x7ffe + 0x6bec)
//   arg1 (r19) selects the emit format: 3 -> scaled f32, 4 -> fn_800264FC then
//   memcpy, anything else -> raw 8-byte quad.  Loop 2's guard is 3<=arg1<=4.
//   flag bits of arg0->unk4 (r6): 0x100 = 16-bit header, 0x2000 = use the
//     arg0->unk0xC u16*3 palette, 0x8000 = byte-swapped components,
//     0x10000 = use the 0x80362CDE palette.
//   descriptor bits of the 2nd s16 (r11): 0x8000 sign, 0x4000 "packed",
//     0x2000/0x1000/0x800 = that component is a palette index.
//
// ---------------------------------------------------------------------
// CALL-SITE ARITY TABLE (arg registers read off want; prototypes taken from the
// PROMOTED callee sources — AGENTS 6dc / 6di "the promoted neighbours are the
// type oracle", including for arity)
//   0x8002AFE8  fn_800144B4  0-arg  (def u64 fn_800144B4(void))
//   0x8002B010  fn_800144B4  0-arg
//   0x8002B038  fn_800144B4  0-arg  -> r3 stored; r4 (=arg1) stored untouched
//   0x8002B8B4  fn_800144B4  0-arg
//   0x8002B044  fn_8002D2A0  0-arg  (def s32 fn_8002D2A0(void))
//   0x8002B05C  fn_8002D3A4  5-arg  (def (Unk_FFAD6788*,s32,s32,s32,s32))
//                                  *** m2c passed only 4 — BUG ***
//   0x8002B074  fn_8002D340  1-arg  (def is 0-arg and reads no r3, but want
//                                  SETS r3=r31, so 1-arg at this site — 6ap-132)
//   0x8002B094  fn_8002D6AC  3-arg  (def (Unk_FFAD6788*,u32,s32))
//   0x8002B0C0  fn_8002D418  6-arg  (def (Unk_FFAD6788*,s32,s32,s32,s32,s32))
//   0x8002B0D4  fn_8002D020  1-arg  -> r16 = obj+0x76  (u16* index array A)
//   0x8002B0E8  fn_8002D028  1-arg  -> r14 = obj+0xEE  (u16* index array B)
//   0x8002B0FC  fn_8002CFF8  1-arg  -> r22 = byte @ obj+0x74 (STRIDE 1)
//   0x8002B108  fn_8002D000  1-arg  -> r15 = byte @ obj+0x75 (STRIDE 2)
//   0x8002B12C  fn_8002D010  2-arg  (r3, r4=0) -> r17 (memcpy dst base, loop 1)
//   0x8002B144  fn_8002D018  2-arg  (r3, r4=0) -> sp54 (memcpy dst base, loop 2)
//   0x8002B5F0  fn_800264FC  2-arg  (sp58, &sp40)   [callee is wip-only]
//   0x8002B5E0 / B604 / B61C / B828 / B840  memcpy  3-arg, each preceded by
//                                  `crclr cr1eq`  => MUST STAY UNPROTOTYPED
//                                  (AGENTS 6an / 6ac-5).  m2c gave them 6, 6
//                                  and 1 arguments — all three were hard errors.
//   0x8002B888  fn_8002D030  3-arg  (def (Unk_C7387A53*,s32,s32))
//   Other m2c bugs fixed here: r22/r15 typed u16* instead of a byte stride;
//   the 0x80362CDE table read at stride 4 (want: stride 8) and typed s32
//   (want: u16); arg0+0x34/0x36 read with lwz (want: lha, i.e. s16);
//   arg0+0x38 masked with an lha (want: (s32)(x<<17)>>24); the strip/stream
//   walkers read with lwz (want: lhz / lhzu / lbz); `idx[i]` must store the
//   running BYTE OFFSET (r26), not the loop index; and the `desc & 0x3800`
//   test, which m2c rendered as a nested `!(desc & 0x3800)`.
//
// ---------------------------------------------------------------------
// BRANCH-TARGET MAP (for the stage-(b) REL14 audit: for a raw want word the
// 14-bit field is a signed WORD displacement, target = branch_VA + 4*sext(f,14))
// The entry block branches below-or-equal from 0x8002AFE0 to 0x8002B00C and
// on nonzero from 0x8002AFF8 to 0x8002B030. From 0x8002B004 an equal branch
// reaches the epilogue at 0x8002B8C8 while an unconditional branch at
// 0x8002B008 reaches 0x8002B030; a nonzero branch at 0x8002B020 also reaches
// 0x8002B030 and an equal branch at 0x8002B02C reaches 0x8002B044. Equal
// branches at 0x8002B06C and 0x8002B09C reach 0x8002B080 and 0x8002B0A8, as
// does a greater-or-equal branch at 0x8002B07C, while an equal branch at
// 0x8002B0C8 reaches the epilogue. Nonzero branches at 0x8002B178 and
// 0x8002B184 reach 0x8002B1B0 and 0x8002B1A8; a nonzero branch at 0x8002B1A4
// returns to 0x8002B17C and an equal branch at 0x8002B1AC reaches 0x8002B650.
// An equal branch at 0x8002B1CC reaches 0x8002B208 with an unconditional
// branch at 0x8002B204 reaching 0x8002B228. An equal branch at 0x8002B234
// reaches 0x8002B498 while a nonzero branch at 0x8002B23C reaches 0x8002B2BC;
// an equal branch at 0x8002B248 reaches 0x8002B280 with an unconditional
// branch at 0x8002B27C reaching 0x8002B50C. Unconditional branches at
// 0x8002B2B8 and 0x8002B494 also reach 0x8002B50C, as does one at 0x8002B4C8,
// while an equal branch at 0x8002B2C0 reaches 0x8002B3A4. Equal branches at
// 0x8002B2C8 and 0x8002B2EC reach 0x8002B2E8 and 0x8002B304, paired with
// unconditional branches at 0x8002B2E4 and 0x8002B300 reaching 0x8002B318
// and 0x8002B31C. Equal branches at 0x8002B320 and 0x8002B344 reach
// 0x8002B340 and 0x8002B35C, paired with unconditional branches at
// 0x8002B33C and 0x8002B358 reaching 0x8002B370 and 0x8002B374. An equal
// branch at 0x8002B378 reaches 0x8002B398 with an unconditional branch at
// 0x8002B394 reaching 0x8002B484. A nonzero branch at 0x8002B39C reaches
// 0x8002B45C with an unconditional branch at 0x8002B3A0 reaching 0x8002B470;
// an equal branch at 0x8002B3A8 reaches 0x8002B3BC with an unconditional
// branch at 0x8002B3B8 reaching 0x8002B3F0, and an equal branch at 0x8002B3C0
// reaches 0x8002B3D8 with an unconditional branch at 0x8002B3D4 also
// reaching 0x8002B3F0. Equal branches at 0x8002B3F4 and 0x8002B40C reach
// 0x8002B408 and 0x8002B424, paired with unconditional branches at
// 0x8002B404 and 0x8002B420 reaching 0x8002B43C twice. Equal branches at
// 0x8002B440 and 0x8002B458 reach 0x8002B454 and 0x8002B470, paired with
// unconditional branches at 0x8002B450 and 0x8002B46C reaching 0x8002B488
// twice. Equal branches at 0x8002B510, 0x8002B530 and 0x8002B538 reach
// 0x8002B528, 0x8002B540 and 0x8002B5E8, with an unconditional branch at
// 0x8002B53C reaching 0x8002B60C. Unconditional branches at 0x8002B5E4 and
// 0x8002B608 both reach 0x8002B620. Nonzero branches at 0x8002B62C and
// 0x8002B64C both return to 0x8002B170. Nonzero branches at 0x8002B688,
// 0x8002B694 and 0x8002B6B4 reach 0x8002B6C0, 0x8002B6B8 and back to
// 0x8002B68C, while an equal branch at 0x8002B6BC reaches 0x8002B874. Equal
// branches at 0x8002B6DC and 0x8002B6E8 reach 0x8002B6E4 and 0x8002B6F8,
// with an unconditional branch at 0x8002B6F4 reaching 0x8002B710. An equal
// branch at 0x8002B714 reaches 0x8002B744 with an unconditional branch at
// 0x8002B740 reaching 0x8002B784. A greater-than branch at 0x8002B78C and a
// less-than branch at 0x8002B794 both reach 0x8002B830, with an unconditional
// branch at 0x8002B82C reaching 0x8002B844. Nonzero branches at 0x8002B850
// and 0x8002B870 both return to 0x8002B680.
//
// ---------------------------------------------------------------------
// LARGEST CONTIGUOUS BYTE-IDENTICAL REGION: none yet.  The inherited body did
// not compile, so it produced NO object at all; this round rewrote the body
// from the disassembly, so there is no shared prefix with the old attempt.
//
// ---------------------------------------------------------------------
// LEVERS MEASURED (tools/test_wip_drafts.py --addr 0x8002AFB0)
//   0. inherited m2c body as committed -> FAIL, 3 memcpy arity errors, no
//      object, so no percentage was readable at all (recorded stratum FAIL).
//   1. full structural rebuild from want + callee-arity/width audit (this file)
//      -> see the STATUS line at the bottom of this header.
//   NOT yet isolated as a separate experiment (read off want, listed for the
//   next round):
//    - dead `mr r7,r10` + `mr r9,r10` in the loop-1 arg1==3 block and
//      `mr r7,r10` + `mr r8,r10` in the loop-2 convert block.  Two
//      un-explainable dead copies of one register in each block; they look
//      like GCC parallel-move residue from a call argument that no longer
//      exists, so the source may really have used a 5-arg memcpy.
//    - the two palette strides (6 for arg0->unk0xC, 8 for the three .bss
//      tables) share no C type, so they must be distinct u16* expressions.
//    - the 20-byte hole at r1+0x5c..0x70 is modelled here as an explicit
//      `char pad5c[0x14]`; if the frame comes out wrong, try AGENTS 6dt's
//      `double` + `"m"` pin instead.
//    - loop-1's skip block computes `end1 = base1 + off` while its tail does
//      `end1 = end1 + off` (want has BOTH forms, at 0x8002B198 and 0x8002B640);
//      transcribed literally.  Same asymmetry in loop 2 (0x8002B6A8 vs
//      0x8002B864).  Worth testing the single-expression form too.
// =====================================================================
#include "types.h"

extern u32   lbl_80300388;
extern u16   lbl_80362CD8[];
extern u16   lbl_80362CDE[];
extern u16   lbl_803634D8[];
extern f64   lbl_80291670;
extern f32   lbl_80291678;
extern f32   lbl_8029167C;
extern char  fn_80026BEC[];

u64  fn_800144B4(void);
s32  fn_8002D2A0(void);
s32  fn_8002D3A4(void *, s32, s32, s32, s32);
s32  fn_8002D340(s32);
s32  fn_8002D6AC(void *, u32, s32);
void *fn_8002D418(void *, s32, s32, s32, s32, s32);
void *fn_8002D020(void *);
void *fn_8002D028(void *);
u32  fn_8002CFF8(void *);
u32  fn_8002D000(void *);
s32  fn_8002D010(void *, s32);
s32  fn_8002D018(void *, s32);
void fn_800264FC(void *, void *);
void fn_8002D030(void *, s32, s32);

typedef struct { u32 w; f32 f1; f32 f2; f32 f3; } Vtx_t;
typedef struct { u16 h; f32 f1; f32 f2; f32 f3; } CVt_t;
typedef struct { u16 w; s16 x; s16 y; s16 z; } Quad_t;
typedef struct { u32 pre:13; u32 flag:1; u32 post:18; } Blk168_t;
typedef union  { s32 w[2]; u64 d; } Key_t;
extern Key_t  lbl_80300390;
typedef union  { u32 w[2]; f64 d; } Cvt_t;

typedef struct {
    Vtx_t  v;                 /* +0x00 -> r1+0x08, 16B */
    char   pad18[0x18];       /* +0x10 -> r1+0x18, 24B address-taken buffer */
    CVt_t  v30;               /* +0x28 -> r1+0x30, 16B */
    Quad_t q40;               /* +0x38 -> r1+0x40,  8B */
    Quad_t q48;               /* +0x40 -> r1+0x48,  8B */
    s32    s50;               /* +0x48 -> r1+0x50 */
    s32    s54;               /* +0x4C -> r1+0x54 */
    void  *s58;               /* +0x50 -> r1+0x58 */
    char   pad5c[0x14];       /* +0x54 -> r1+0x5c, 20B; NO accessor in want */
    Cvt_t  cv;                /* +0x68 -> r1+0x70,  8B shared int->f64 pair */
} Frm_t;

void fn_8002AFB0(void *arg0_, s32 arg1) {
    Frm_t fr;
    s32 flags, count, w, i, end1, end2, off1, off2, hdr;
    s32 first, desc, ver, sp;
    u8 *p, *pnext;
    s16 *p1, *p2;
    u16 *dstA, *dstB, *idx1, *idx2;
    s32 stride1, stride2;
    u8 *base1, *base2;
    void *ctx, *obj;
    Key_t ky;
    f64 pool;
    f32 sc1, sc2;
    Quad_t *q;

    if (lbl_80300388 > 9U) {
        ky.d = fn_800144B4();
        if (lbl_80300390.w[0] != ky.w[0] || lbl_80300390.w[1] != ky.w[1])
            goto reset;
        return;
    }
    ky.d = fn_800144B4();
    if (lbl_80300390.w[0] == ky.w[0] && lbl_80300390.w[1] == ky.w[1])
        goto cont;
reset:
    lbl_80300388 = 0;
    ky.d = fn_800144B4();
    lbl_80300390.d = ky.d;
cont:
    ctx = (void *)fn_8002D2A0();
    count = *(s32 *)((char *)arg0_ + 8);
    ver = fn_8002D3A4(ctx, count, *(s16 *)((char *)arg0_ + 0x34),
                      *(s16 *)((char *)arg0_ + 0x36), arg1);
    if (*(s32 *)((char *)ctx + 0xCC) == 0x32 ||
        (s32)fn_8002D340((s32)ctx) < ver) {
        if (fn_8002D6AC(ctx,
                (u32)((s32)(*(s32 *)((char *)arg0_ + 0x38) << 0x11) >> 0x18),
                ver) != 0)
            *(s32 *)((char *)arg0_ + 0x24) = 0;
    }
    obj = fn_8002D418(ctx, (s32)arg0_, *(s32 *)((char *)arg0_ + 8),
                      *(s16 *)((char *)arg0_ + 0x34),
                      *(s16 *)((char *)arg0_ + 0x36), arg1);
    if (obj == 0)
        return;

    idx1    = (u16 *)fn_8002D020(obj);
    idx2    = (u16 *)fn_8002D028(obj);
    stride1 = (s32)fn_8002CFF8(obj);
    stride2 = (s32)fn_8002D000(obj);
    base1   = *(u8 **)((char *)arg0_ + 0x10);
    base2   = *(u8 **)((char *)arg0_ + 0x14);
    p1      = (s16 *)*(s32 *)((char *)arg0_ + 0x2C);
    p2      = (s16 *)*(s32 *)((char *)arg0_ + 0x30);
    dstA    = (u16 *)fn_8002D010(obj, 0);
    fr.s54  = fn_8002D018(obj, 0);
    fr.s58  = &fr.pad18[0];
    fr.s50  = *(s32 *)((char *)arg0_ + 0x14);
    base2   = (u8 *)fr.s50;
    pool    = lbl_80291670;
    sc1     = lbl_80291678;
    off1    = 0;

    i = 0;
    end1 = (s32)((char *)base1 + (s16)*p1);
loop_13:
    if (*p1 == 0) {
    loop_14:
        if (*p1 == 0) {
            i = (s16)(i + 1) & 0xFFFF;
            end1 = (s32)((char *)base1 + (s16)*p1++);
            idx1[i] = (u16)off1;
            if ((s32)(u16)i != count)
                goto loop_14;
        }
        if ((s32)(u16)i != count)
            goto body_1;
    } else {
    body_1:
        q = &fr.q40;
        p = base1;
        w = *(s32 *)((char *)arg0_ + 4);
        if (w & 0x100) {
            first = (s8)(p[0] | (p[1] << 8));
            desc  = (s8)(p[2] | (p[3] << 8));
            p += 4;
        } else {
            first = (s8)(p[0] | (p[1] << 8));
            desc  = first;
            p += 2;
        }
        q->w = (u16)((first & 0x7FFF) | (desc & 0x8000));
        if (desc & 0x4000) {
            if (!(desc & 0x3800)) {
                u8 ix = *p++;
                if (w & 0x2000) {
                    u16 *pal = *(u16 **)((char *)arg0_ + 0xC);
                    q->x = pal[ix * 3 + 0];
                    q->y = pal[ix * 3 + 1];
                    q->w &= 0x87FF;
                    q->z = pal[ix * 3 + 2];
                } else {
                    u16 *pal = lbl_80362CD8;
                    q->x = pal[ix * 4 + 0];
                    q->y = pal[ix * 4 + 1];
                    q->z = pal[ix * 4 + 2];
                    q->w &= 0x87FF;
                }
            } else if (w & 0x10000) {
                u16 *pal = lbl_80362CDE;
                if (desc & 0x2000) {
                    q->x = pal[*p++ * 4 + 0];
                } else if (w & 0x8000) {
                    q->x = (u16)(*p++ << 8);
                } else {
                    q->x = (u16)(p[0] | (p[1] << 8));
                    p += 2;
                }
                if (desc & 0x1000) {
                    q->y = pal[*p++ * 4 + 0];
                } else if (w & 0x8000) {
                    q->y = (u16)(*p++ << 8);
                } else {
                    q->y = (u16)(p[0] | (p[1] << 8));
                    p += 2;
                }
                if (desc & 0x800) {
                    q->z = pal[*p++ * 4 + 0];
                } else if (w & 0x8000) {
                    q->z = (u16)(*p++ << 8);
                } else {
                    q->z = (u16)(p[0] | (p[1] << 8));
                    p += 2;
                }
                q->w &= 0x87FF;
            } else {
                if (desc & 0x2000) {
                    q->x = *p++;
                } else if (w & 0x8000) {
                    q->x = (u16)(*p++ << 8);
                } else {
                    q->x = (u16)(p[0] | (p[1] << 8));
                    p += 2;
                }
                if (desc & 0x1000) {
                    q->y = *p++;
                } else if (w & 0x8000) {
                    q->y = (u16)(*p++ << 8);
                } else {
                    q->y = (u16)(p[0] | (p[1] << 8));
                    p += 2;
                }
                if (desc & 0x800) {
                    q->z = *p++;
                } else if (w & 0x8000) {
                    q->z = (u16)(*p++ << 8);
                } else {
                    q->z = (u16)(p[0] | (p[1] << 8));
                    p += 2;
                }
                q->w &= 0x87FF;
            }
        } else if (w & 0x8000) {
            q->x = (u16)(p[0] << 8);
            q->y = (u16)(p[1] << 8);
            p += 3;
            q->z = (u16)(p[2] << 8);
        } else {
            q->x = (u16)(p[0] | (p[1] << 8));
            q->y = (u16)(p[2] | (p[3] << 8));
            p += 6;
            q->z = (u16)(p[4] | (p[5] << 8));
        }
        if (w & 0x100)
            q->w = (u16)((q->w & 0x8000) | (first & 0x7FFF));

        if (arg1 == 3) {
            fr.v.w = (fr.v.w & 0xFFFF) |
                     ((u32)q->w << 16) |
                     (((u32)q->w << 17) & 0xFFFE0000);
            fr.cv.w[1] = q->x ^ 0x8000; fr.cv.w[0] = 0x43300000;
            fr.v.f1 = (f32)(fr.cv.d - pool) * sc1;
            fr.cv.w[1] = q->y ^ 0x8000; fr.cv.w[0] = 0x43300000;
            fr.v.f2 = (f32)(fr.cv.d - pool) * sc1;
            fr.cv.w[1] = q->z ^ 0x8000; fr.cv.w[0] = 0x43300000;
            fr.v.f3 = (f32)(fr.cv.d - pool) * sc1;
            memcpy((char *)dstA + off1, &fr.v, stride1);
        } else if (arg1 == 4) {
            fn_800264FC(fr.s58, &fr.q40);
            memcpy((char *)dstA + off1, fr.s58, stride1);
        } else {
            memcpy((char *)dstA + off1, &fr.q40, stride1);
        }
        off1 = (s16)(off1 + stride1) & 0xFFFF;
        if ((s32)p != end1)
            goto loop_13;
        i = (s16)(i + 1) & 0xFFFF;
        end1 = end1 + (s16)*p1++;
        idx1[i] = (u16)off1;
        if ((s32)(u16)i != count)
            goto loop_13;
    }

    i = 0;
    off2 = 0;
    sc2 = lbl_8029167C;
    end2 = (s32)((char *)base2 + (s16)*p2);
loop_73:
    if (*p2 == 0) {
    loop_74:
        if (*p2 == 0) {
            i = (s16)(i + 1) & 0xFFFF;
            end2 = (s32)((char *)base2 + (s16)*p2++);
            idx2[i] = (u16)off2;
            if ((s32)(u16)i != count)
                goto loop_74;
        }
        if ((s32)(u16)i != count)
            goto body_2;
    } else {
    body_2:
        q = &fr.q48;
        p = base2;
        hdr = (s32)p[0];
        sp = 1;
        if (!(hdr & 0x80))
            sp = 0;
        if (hdr & 0x40) {
            q->w = (u16)(hdr & 0x3F);
            p += 1;
        } else {
            q->w = (u16)(base2[1] | (base2[2] << 8));
            p += 3;
        }
        if (sp != 0) {
            u16 *pal = lbl_803634D8;
            u8 ix = *p++;
            q->z = pal[ix * 4 + 2];
            q->x = pal[ix * 4 + 0];
            q->y = pal[ix * 4 + 1];
        } else {
            q->x = (u16)(p[0] | (p[1] << 8));
            q->y = (u16)(p[2] | (p[3] << 8));
            q->z = (u16)(p[4] | (p[5] << 8));
            p += 6;
        }
        base2 = p;
        if (arg1 > 4)
            goto emit_plain;
        if (arg1 < 3)
            goto emit_plain;
        {
            fr.v30.h = q->w;
            fr.cv.w[1] = q->x ^ 0x8000; fr.cv.w[0] = 0x43300000;
            fr.v30.f1 = (f32)(fr.cv.d - pool) / sc2;
            fr.cv.w[1] = q->y ^ 0x8000; fr.cv.w[0] = 0x43300000;
            fr.v30.f2 = (f32)(fr.cv.d - pool) / sc2;
            fr.cv.w[1] = q->z ^ 0x8000; fr.cv.w[0] = 0x43300000;
            fr.v30.f3 = (f32)(fr.cv.d - pool) / sc2;
            memcpy((char *)fr.s54 + off2, &fr.v30, stride2);
        }
        goto emit_done;
    emit_plain:
        memcpy((char *)fr.s54 + off2, q, stride2);
    emit_done: ;
        off2 = (s16)(off2 + stride2) & 0xFFFF;
        if ((s32)p != end2)
            goto loop_73;
        i = (s16)(i + 1) & 0xFFFF;
        end2 = end2 + (s16)*p2++;
        idx2[i] = (u16)off2;
        if ((s32)(u16)i != count)
            goto loop_73;
    }

    *(s32 *)((char *)arg0_ + 0x24) = (s32)obj;
    fn_8002D030(obj, (s32)fn_80026BEC, (s32)arg0_);
    ((Blk168_t *)((char *)*(s32 *)((char *)arg0_ + 0x24) + 0x168))->flag =
        (*(s32 *)((char *)arg0_ + 4) >> 11) & 1;
    lbl_80300388 = lbl_80300388 + 1;
    ky.d = fn_800144B4();
    lbl_80300390.d = ky.d;
}