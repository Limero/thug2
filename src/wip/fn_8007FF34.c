// family=m2c range=0x8007FF34-0x800804E4 size=1456B
//
// REBUILD (2026-10-07, ) — from-scratch reconstruction of
// fn_8007FF34, replacing the 0.55% m2c husk (which modelled the stack matrices
// as file-scope `static s32 spXX` and typed the float slots `s32`, so every FPR
// web was dead-code-eliminated and the frame collapsed 0x130 -> 0x40).
// Source of truth: build/G2TE52/asm/auto_01_8007FF34_text.s (364 insns).
//
// WHAT THE FUNCTION IS (skater node update):
//   fn_8007FF34(Obj *arg0, s32 mode)
//     if (mode != 0) {
//       if (arg0->node30 != NULL) {          /* has its matrix node */
//         A  = node30's 4x4 (+8), but A's LAST ROW is replaced by
//              (lbl_80296278, lbl_80296278, lbl_80296278, lbl_8029627C);
//         rot = rotation built by fn_80003EB0(rot, (f32)mode * lbl_80296288);
//         res = A * rot;                     /* 16 unrolled dot products */
//         rot = res; rot's last row = the node's ORIGINAL last row;
//         write rot back to node30+8;
//       } else {                             /* mode 0 object: gather/scatter */
//         arg0->unk44 = mode;
//         n   = arg0->vt[0x128/8].fn(arg0 + vt[0x128/8].adj);
//         buf = Mem_Alloc(n * 16);
//         <n-1-iteration countdown loop>
//         arg0->vt[0x130/8].fn(arg0 + vt[0x130/8].adj, buf);
//         if (n > 0) for (i = n; i != 0; i--) {
//              switch (mode) {   /* 1: swap x/z about (unk38,unk40)
//                                   2: mirror about (unk38,unk40)
//                                   3: mirror swap */ }
//              p += 4;
//         }
//         arg0->vt[0x140/8].fn(arg0 + vt[0x140/8].adj, buf);
//         Mem_Free(buf);
//       }
//     }
//     arg0->unk44 = mode;
//
// FRAME (retail, derived by walking every (r1) access — this is exact):
//   r1+0x08 A[16] f32     (the node's matrix, 64 B)
//   r1+0x48 v[4]  f32     (the replacement bottom row, written scalar, read psq)
//   r1+0x58 rot[16] f32   (fn_80003EB0's output; later the final matrix)
//   r1+0x98 res[16] f32   (A * rot)
//   r1+0xd8 pp[2] f32*    ({&A, &rot}; only pp[0] is ever read)
//   r1+0xe0 8 B           GCC's own int->float magic-double temp (not a local)
//   r1+0xe8 stmw r26..r31 (0x18)   r1+0x100 stfd f26..f31 (0x30)
//   stwu -0x130 ; LR at +0x134 (= 0x130 frame + the 8-byte linkage area).
// A single struct of exactly 0xD8 B (+ its 0xE0 temp) reproduces all of it:
// 0x40+0x10+0x40+0x40+8 = 0xD8, then GCC's saves land at 0xe8/0x100 by itself.
//
// TWO `bdnz $` SELF-TARGETING 4-ITERATION WINDOWS (retail +0x60, +0xDC) are
// reproduced with the documented plain-C empty counted loop (recipes 73 /
// doc-30 `for (spin = 0; spin < 4; spin++) { }` — ngccc keeps it and lowers it
// to `li r0,4; mtctr r0; bdnz $`).  NO inline asm: the `bdnz $`/`.long` forms
// are only needed when the plain loop fails to survive.
//
// The short countdown after Mem_Alloc is NOT constant-count, so it is not a
// doloop: retail is `cmpwi r31,0 ; subi r9,r31,1 ; beq ; [cmpwi r9,0 ; subi
// r9,r9,1 ; bne]` == `if (n != 0) { i = n-1; while (i-- != 0) { } }`.
//
// OPEN / UNVERIFIED (no compiler available in this slice):
//  1. The two empty loops above — kept as empty loops per the documented
//     recipe, but an empty `for` body may still be deleted by ngccc.
//  2. v[0..3] store order.  Retail emits 0x48(x), 0x54(w), 0x50(z), 0x4c(y),
//     i.e. NOT plain reverse of an ascending run; written ascending here.
//  3. The 16 dot products are written ascending/left-assoc, which reproduces
//     retail's `fmuls a1*b10 ; fmadds a0*b00+t ; fmadds a2*b20+t ; fmadds
//     a3*b30+t` nesting (the second term's product is the fmuls).  Whether GCC
//     CSEs each rot[k*4+j] into the same callee-saved f26..f31 across the four
//     output rows depends on the allocator; retail loads each exactly once.
//  4. `angle = (f32)arg1 * lbl_80296288` is what emits retail's
//     xoris/stw/lis 0x4330/stw/lfd/fsub/frsp/fmuls int->float sequence (the
//     `lfd lbl_80296280` is the compiler's own 2^52 magic, so it must NOT be
//     declared here).
//  5. arg0 field names are invented; only the offsets are known (0x14 vtable,
//     0x30 matrix node, 0x38/0x40 f32 pair, 0x44 s32).
#include "types.h"

/* vtable slot: { s16 this-adjust ; ... ; s32 fn } — retail reads the adjust
   with `lha` and the entry with `lwz` 4 bytes later, so entries are 8 B.
   Slots used: +0x128 (37), +0x130 (38), +0x140 (40). */
typedef struct {
    s16 adj;
    u16 pad;
    s32 (*fn)(); /* K&R: called with 1 and with 2 args */
} VSlot;

typedef struct {
    char pad0[0x14];
    VSlot *vt;   /* 0x14 */
    char pad1[0x18];
    f32 *node;   /* 0x30 */
    f32 unk38;   /* 0x38 */
    f32 unk3C;   /* 0x3C */
    f32 unk40;   /* 0x40 */
    s32 unk44;   /* 0x44 */
} Obj;

typedef struct {
    f32 A[16];   /* 0x08 */
    f32 v[4];    /* 0x48 */
    f32 rot[16]; /* 0x58 */
    f32 res[16]; /* 0x98 */
    f32 *pp[2];  /* 0xd8 */
} Frame;         /* 0xd8 B */

extern f32 lbl_80296278;
extern f32 lbl_8029627C;
extern f32 lbl_80296288;

void *fn_80003EB0(void *, f32);
void *Mem_Alloc(s32);
void Mem_Free(void *);

void fn_8007FF34(Obj *arg0, s32 arg1) {
    Frame fr;
    __ps_t *src;
    __ps_t *dst;
    f32 *mp;
    f32 *vp;
    f32 *buf;
    s32 n;
    s32 spin;
    s32 i;
    f32 x;
    f32 z;

    if (arg1 != 0) {
        if (arg0->node != 0) {
            src = (__ps_t *)((char *)arg0->node + 8);

            for (spin = 0; spin < 4; spin++) { }

            ((__ps_t *)fr.A)[0] = src[0];
            ((__ps_t *)fr.A)[1] = src[1];
            ((__ps_t *)fr.A)[2] = src[2];
            ((__ps_t *)fr.A)[3] = src[3];
            ((__ps_t *)fr.A)[4] = src[4];
            ((__ps_t *)fr.A)[5] = src[5];
            ((__ps_t *)fr.A)[6] = src[6];
            ((__ps_t *)fr.A)[7] = src[7];

            /* the replacement bottom row: written as scalars, read back as pairs */
            ((f32 *)fr.v)[0] = lbl_80296278;
            ((f32 *)fr.v)[1] = lbl_80296278;
            ((f32 *)fr.v)[2] = lbl_80296278;
            ((f32 *)fr.v)[3] = lbl_8029627C;

            for (spin = 0; spin < 4; spin++) { }

            ((__ps_t *)fr.A)[6] = ((__ps_t *)fr.v)[0];
            ((__ps_t *)fr.A)[7] = ((__ps_t *)fr.v)[1];

            fn_80003EB0(fr.rot, (f32)arg1 * lbl_80296288);

            fr.pp[0] = fr.A;
            fr.pp[1] = fr.rot;
            mp = (f32 *)fr.pp[0];

            fr.res[0]  = mp[0]  * fr.rot[0]  + mp[1]  * fr.rot[4]  + mp[2]  * fr.rot[8]  + mp[3]  * fr.rot[12];
            fr.res[1]  = mp[0]  * fr.rot[1]  + mp[1]  * fr.rot[5]  + mp[2]  * fr.rot[9]  + mp[3]  * fr.rot[13];
            fr.res[2]  = mp[0]  * fr.rot[2]  + mp[1]  * fr.rot[6]  + mp[2]  * fr.rot[10] + mp[3]  * fr.rot[14];
            fr.res[3]  = mp[0]  * fr.rot[3]  + mp[1]  * fr.rot[7]  + mp[2]  * fr.rot[11] + mp[3]  * fr.rot[15];
            fr.res[4]  = mp[4]  * fr.rot[0]  + mp[5]  * fr.rot[4]  + mp[6]  * fr.rot[8]  + mp[7]  * fr.rot[12];
            fr.res[5]  = mp[4]  * fr.rot[1]  + mp[5]  * fr.rot[5]  + mp[6]  * fr.rot[9]  + mp[7]  * fr.rot[13];
            fr.res[6]  = mp[4]  * fr.rot[2]  + mp[5]  * fr.rot[6]  + mp[6]  * fr.rot[10] + mp[7]  * fr.rot[14];
            fr.res[7]  = mp[4]  * fr.rot[3]  + mp[5]  * fr.rot[7]  + mp[6]  * fr.rot[11] + mp[7]  * fr.rot[15];
            fr.res[8]  = mp[8]  * fr.rot[0]  + mp[9]  * fr.rot[4]  + mp[10] * fr.rot[8]  + mp[11] * fr.rot[12];
            fr.res[9]  = mp[8]  * fr.rot[1]  + mp[9]  * fr.rot[5]  + mp[10] * fr.rot[9]  + mp[11] * fr.rot[13];
            fr.res[10] = mp[8]  * fr.rot[2]  + mp[9]  * fr.rot[6]  + mp[10] * fr.rot[10] + mp[11] * fr.rot[14];
            fr.res[11] = mp[8]  * fr.rot[3]  + mp[9]  * fr.rot[7]  + mp[10] * fr.rot[11] + mp[11] * fr.rot[15];
            fr.res[12] = mp[12] * fr.rot[0]  + mp[13] * fr.rot[4]  + mp[14] * fr.rot[8]  + mp[15] * fr.rot[12];
            fr.res[13] = mp[12] * fr.rot[1]  + mp[13] * fr.rot[5]  + mp[14] * fr.rot[9]  + mp[15] * fr.rot[13];
            fr.res[14] = mp[12] * fr.rot[2]  + mp[13] * fr.rot[6]  + mp[14] * fr.rot[10] + mp[15] * fr.rot[14];
            fr.res[15] = mp[12] * fr.rot[3]  + mp[13] * fr.rot[7]  + mp[14] * fr.rot[11] + mp[15] * fr.rot[15];

            ((__ps_t *)fr.rot)[0] = ((__ps_t *)fr.res)[0];
            ((__ps_t *)fr.rot)[1] = ((__ps_t *)fr.res)[1];
            ((__ps_t *)fr.rot)[2] = ((__ps_t *)fr.res)[2];
            ((__ps_t *)fr.rot)[3] = ((__ps_t *)fr.res)[3];
            ((__ps_t *)fr.rot)[4] = ((__ps_t *)fr.res)[4];
            ((__ps_t *)fr.rot)[5] = ((__ps_t *)fr.res)[5];
            ((__ps_t *)fr.rot)[6] = ((__ps_t *)fr.res)[6];
            ((__ps_t *)fr.rot)[7] = ((__ps_t *)fr.res)[7];

            /* the outgoing matrix keeps the node's ORIGINAL bottom row */
            ((__ps_t *)fr.rot)[6] = src[6];
            ((__ps_t *)fr.rot)[7] = src[7];

            dst = (__ps_t *)((char *)arg0->node + 8);
            dst[0] = ((__ps_t *)fr.rot)[0];
            dst[1] = ((__ps_t *)fr.rot)[1];
            dst[2] = ((__ps_t *)fr.rot)[2];
            dst[3] = ((__ps_t *)fr.rot)[3];
            dst[4] = ((__ps_t *)fr.rot)[4];
            dst[5] = ((__ps_t *)fr.rot)[5];
            dst[6] = ((__ps_t *)fr.rot)[6];
            dst[7] = ((__ps_t *)fr.rot)[7];
        } else {
            arg0->unk44 = arg1;

            n = arg0->vt[37].fn((char *)arg0 + arg0->vt[37].adj);

            buf = (f32 *)Mem_Alloc(n * 16);

            if (n != 0) {
                i = n - 1;
                while (i-- != 0) { }
            }

            arg0->vt[38].fn((char *)arg0 + arg0->vt[38].adj, buf);

            if (n > 0) {
                vp = buf;
                for (i = n; i != 0; i--) {
                    switch (arg1) {
                    case 1:
                        x = vp[0];
                        z = vp[2];
                        vp[0] = arg0->unk38 + (z - arg0->unk40);
                        vp[2] = arg0->unk40 + (arg0->unk38 - x);
                        break;
                    case 2:
                        x = vp[0];
                        z = vp[2];
                        vp[0] = arg0->unk38 + (arg0->unk38 - x);
                        vp[2] = arg0->unk40 + (arg0->unk40 - z);
                        break;
                    case 3:
                        x = vp[0];
                        z = vp[2];
                        vp[0] = arg0->unk38 + (arg0->unk40 - z);
                        vp[2] = arg0->unk40 + (x - arg0->unk38);
                        break;
                    }
                    vp += 4;
                }
            }

            arg0->vt[40].fn((char *)arg0 + arg0->vt[40].adj, buf);

            Mem_Free(buf);
        }
    }
    arg0->unk44 = arg1;
}

// ---------------------------------------------------------------------------
// SUPERSEDED BODY (m2c husk) — earlier findings preserved verbatim below.
// The body above replaced it (worker rebuild + measured-diff repair loop,
// 2); keep these notes, they are still the local lore.
// ---------------------------------------------------------------------------
// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 0.3% while git revision b84f19fe8 scores 0.5%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 14 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
//
// PARKED 2026-10-07: 0.55% (2/364 words) — TIER C; no
// bounded fix reaches this body.
// FIRST DIVERGENCE = the prologue/frame. The want claims a 0x130 frame while
// saving six doubles for f26 through f31 at 0x100 through 0x128, then saving
// r26 and up at 0xe8 and the link register at 0x134, for six FPR plus six GPR
// saves. The current output instead claims only a 0x40 frame while saving
// from r27 at 0x2c and the link register at 0x44, with no float saves at all.
// Root cause (m2c husk, same class as fn_800C1538): the 4x4 float matrix and
// the `&vec[0]`/`&vec[1]` pointer pair were modelled as file-scope
// `static s32` (sp5C..sp94, spD8) with `s32`-cast element reads, so ngccc
// DCEs every FPR web and the frame collapses to 0x40.  Want addresses all of
// it off r1 (`lfs f26,0x68(r1)`, `psq_l f0,0(r31)` with an r1-based r31),
// i.e. real stack `f32`/`__ps_t` locals.
// THIS PASS made the only 1:1-justified edits: the matrix slots became `f32`
// LOCALS and the element reads became `*(f32 *)` (want `lfs fN,N(r9)`).  That
// removes the integer-math corruption but does NOT reproduce the psq pair
// copies — a faithful body needs a rebuild.
// REBUILD PLAN (concrete, for the next agent): want is a rigid-body rotation
// build — `fn_80003EB0(&m, lbl_80296278, lbl_8029627C, angle*lbl_80296288,
// 0, lbl_80296288)` builds the 3x3 at r1+0x58; then 8 `psq_l/psq_st` pairs
// (disp 0,8,..,0x38 from r31 to r11) copy a 16-lane f32 4x4 between two stack
// arrays; then a 4x4 * vector product (`fmadds` chains from 0x124 on, using
// lfs f26=0x68, f27=0x58, f30=0x6c, f29=0x5c, f28=0x7c, f24/25=0x60/0x64)
// writes 16 outputs; then the `*(arg0+0x14)->vcall(0x128, arg0+off, r)`
// gather, `Mem_Alloc(count*0x10)`, the per-element x/z swap loop (arg1==1 vs
// >1 vs else, `-(v-c)+c` forms) and the 0x144 scatter + Mem_Free, all of
// which the draft already has.  Model the two stack matrices as `f32 a[4][4]`
// (or `__ps_t a[8]`) so the psq run and the 0x130 frame fall out.
