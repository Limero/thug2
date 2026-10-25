// WIP DRAFT (non-matching) — structural reconstruction from the decoded WANT.
// family=m2c range=0x80091E98-0x80092040 size=424B
// FLAG: -mps-float
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// RECONSTRUCTED 2026-10-06. The previous m2c body
// was 12 words (64B vs 424B, 0.00%) — m2c emitted `0;` placeholders for all 41
// paired-single words and a bogus file-scope `static s32 sp18`.  This body
// replaces it with the real structure, decoded off the WANT disassembly.
//
// WHAT THE FUNCTION IS: a 5-argument record builder.  Caller fn_800775B4 (matched,
// byte-identical) proves the signature:
//     fn_80091E98(a, a+0x10, a+0x20, a+0x30, int)   /* arg0..arg3, arg4 in r7 */
// It takes the current index from the global count lbl_803017E8, indexes the
// 0x60-byte record array lbl_80377AD8 (0x1800/0x60 = 64 records), zero-heads the
// record, stamps a type tag pair (0,1) plus arg4 at +8, copies four 16-byte
// vectors (arg0..arg3) into +0x10/+0x20/+0x30/+0x40, computes a cross/normalise
// result into +0x50/+0x58, and finally bumps lbl_803017E8.
//
// DECODE OF THE WANT (addresses 0x80091E98..0x8009203C):
//   * r27 = 0x80300000 page, `lwz r0,0x17E8(r27)` = lbl_803017E8 (count).
//   * r9 = lbl_80377AD8, off = count*0x60; `stwx r10(0),r9,r0` = rec[0] = 0.
//   * r11 = off+base -> rec; stw r7(arg4) at rec+8; stw r29(1) at rec+4.
//   * 8x `psq_l`/`psq_st` copy arg0..arg3 (16B each) into rec+0x10/0x20/0x30/0x40.
//   * 0x80091F44..0x80092024 is a paired-single block of 25 opcode-4 words.
//     The decoded operation order starts with subtracts into f12 from f12 and
//     f13, into f9 from f9 and f13, into f11 from f11 and f10, and into f0 from
//     f0 and f10, then merge10s into f10 from f11 and f12 and into f13 from f0
//     and f9, then multiplies into f13 from f11 and f13 and into f10 from f10
//     and f0, then a merge00 into f12 from f12 and f11, then a multiply into
//     f12 from f12 and f0, then a subtract into f13 from f13 and f10, then a
//     merge00 into f0 from f13 and f13, a merge10 into f0 from f12 and f12, a
//     subtract into f12 from f12 and f0, a merge10 into f13 from f13 and f12,
//     a move into f0 from f12, a multiply of f0 by itself, a merge00 of f0 with
//     the lbl_80297174 pair, a multiply-add of f0 with f11, a sum of f0, a
//     float compare of f13 against f12 holding the lbl_802971A4 threshold, a
//     branch to 0x80092028, a reciprocal square root into f13 from f0, a
//     scaled multiply into f0 from f11 and f13, and the stores to rec+0x50
//     and rec+0x58.
//     i.e. a cross-product into rec+0x50/0x58, then, if the squared length
//     exceeds the lbl_802971A4 threshold, a reciprocal-sqrt normalise.
//   * scalars: lbl_802971A0 (lfs), lbl_802971A4 (threshold, lfs),
//     lbl_80297174 (PS pair used as the merge00 addend).
//   * tail: `lwz r9,0x17E8(r27); addi r9,r9,1; stw r9,0x17E8(r27)`.
//
// PARKED 2026-10-19: still 0.0% DIFF (want 424B/0x60 frame vs got 300B/0x18).
// Retried principled vector typing (args void* -> __ps_t*, direct lanes, no
// casts). Zero movement — frame/spill gap unchanged, PS homes unbound in C.
// PARKED 2026-10-06. Blocker: paired-single register allocation +
// the compiler-chosen stack spill slots (sp+0x08..0x44).  The deterministic
// prefix (header stores + the 8 psq copy pairs) is believed faithful; the PS
// tail below is the decoded op ORDER expressed with the SN_PS `ps_*` macros,
// but the exact merge/madd operand roles, the r1+0x18..0x44 scratch traffic and
// the final store set are a hypothesis — GCC 2.95's PS allocator picks homes
// that C pins do not bind (docs/parkings/15 + AGENTS-recipes PS notes).  No
// inline asm and no transcribed instructions; the body is honest C.
//
// WANT vs GOT is not measurable from here (no compiler in this slice): the
// draft is INERT, so the DOL stays byte-identical regardless.
#include "types.h"
#include "structs.h"
#include "dolphin/SN_PS.h"

extern char lbl_80377AD8[];   /* .bss  0x1800 = 64 records of 0x60 */
extern char lbl_803017E8[];   /* .data count/index */
extern char lbl_80297174[];   /* .rodata2 PS pair */
extern char lbl_802971A0[];   /* .rodata2 float */
extern char lbl_802971A4[];   /* .rodata2 float threshold */

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSU_80091E98;

typedef struct {
    s32 unk0x0;          /* +0x00 = 0   */
    s32 unk0x4;          /* +0x04 = 1   */
    s32 unk0x8;          /* +0x08 = arg4 */
    s32 unk0xC;
    __ps_t blk0x10[2];   /* from arg0 */
    __ps_t blk0x20[2];   /* from arg1 */
    __ps_t blk0x30[2];   /* from arg2 */
    __ps_t blk0x40[2];   /* from arg3 */
    __ps_t out0x50[2];   /* computed  */
} Rec_80091E98;

void fn_80091E98(__ps_t *arg0, __ps_t *arg1, __ps_t *arg2, __ps_t *arg3, s32 arg4) {
    Rec_80091E98 *rec;
    __ps_t *b0;
    __ps_t *b1;
    __ps_t *b3;
    s32 idx;
    __ps_t v0;
    __ps_t v9;
    __ps_t v10;
    __ps_t v11;
    __ps_t v12;
    __ps_t v13;
    __ps_t out;
    __ps_t rsq;
    PSU_80091E98 dot;

    idx = *(s32 *)lbl_803017E8;
    rec = (Rec_80091E98 *)(lbl_80377AD8 + idx * 0x60);

    rec->unk0x0 = 0;
    rec->unk0x8 = arg4;
    rec->unk0x4 = 1;

    b0 = arg0;
    b1 = arg1;
    b3 = arg3;

    rec->blk0x10[0] = b0[0];
    rec->blk0x10[1] = b0[1];
    rec->blk0x20[0] = b1[0];
    rec->blk0x20[1] = b1[1];
    rec->blk0x30[0] = arg2[0];
    rec->blk0x30[1] = arg2[1];
    rec->blk0x40[0] = b3[0];
    rec->blk0x40[1] = b3[1];

    /* Paired-single cross product of (arg0->arg1) x (arg0->arg3). */
    v13 = b0[1];
    v12 = ps_sub(b1[1], v13);
    v9 = ps_sub(b3[1], v13);
    v10 = b0[0];
    v11 = ps_sub(b1[0], v10);
    v0 = ps_sub(b3[0], v10);
    v10 = ps_merge10(v11, v12);
    v13 = ps_merge10(v0, v9);
    v13 = ps_mul(v11, v13);
    v10 = ps_mul(v10, v0);
    v12 = ps_mul(ps_merge00(v12, v11), ps_merge00(v0, v9));
    v13 = ps_sub(v13, v10);
    out = ps_merge00(v13, v13);

    /* Second output lane: fold the merged cross term. */
    v0 = ps_sub(v12, ps_merge10(v12, v12));
    v13 = ps_merge10(v13, v0);

    rec->out0x50[0] = v13;
    rec->out0x50[1] = out;

    /* Squared length vs lbl_802971A4; normalise if it exceeds the threshold. */
    v0 = ps_mul(out, out);
    v0 = ps_merge00(v0, *(__ps_t *)lbl_80297174);
    v0 = ps_madd(v13, v0, v13);
    dot.ps = ps_sum0(v0, v0, v0);
    if (dot.flt.hi > *(f32 *)lbl_802971A4) {
        rsq = ps_rsqrte(dot.ps);
        rec->out0x50[0] = ps_muls0(v13, rsq);
        rec->out0x50[1] = ps_mul(out, rsq);
    }

    *(s32 *)lbl_803017E8 = idx + 1;
}
