// WIP DRAFT (PARKED 4.4% plain-C semantic) — hand-rebuilt from disasm
// family=m2c range=0x8024F4B0-0x8024F5C0 size=272B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARK REASON (verified, do not re-grind):
// fn_8024F4B0 is HAND-WRITTEN ASSEMBLY (NeGo texture-upload kernel family,
// docs/parkings/41 class; see also §6ay-236 fingerprints). Evidence:
//  1. It saves ELEVEN callee-saved registers as individual stw (r16, r14, r15,
//     r20-r27) INTERLEAVED with body computation — and r20-r27 are NEVER USED
//     in the body. They exist purely to shield the ABI-violating helper
//     fn_8024F5C0, which uses r20-r27 as copy temps with no prologue of its
//     own. No C source can make ngccc save registers it does not use; and
//     ngccc emits saves only as contiguous stmw spans anyway (probe:
//     exactly-2-reg live-across-call case still yields "stwu -80; stmw 14").
//  2. All six calls to fn_8024F5C0 pass (src, stride, dst) in NONSTANDARD
//     regs (r12=src, r14=stride, r15=dst); the helper (0x8024F5C0, 0x9C bytes:
//     dcbz/lwz-x8/add/stw-x8/dcbst/add, repeated = two stride-separated 32B
//     row copies per call) takes no ABI args at all.
//  3. LR is held in r16 (mflr r16 ... mtlr r16); ngccc uses r0.
// Consequence: any plain-C body scores ~3% (prologue/frame/call-sequence
// words only). The body below is the honest semantic reconstruction — luma
// tile (4 calls = 8 rows) + half-resolution chroma planes (1 call each) —
// kept asm-free per policy; it compiles and documents the algorithm, but it
// can never byte-match. Do not re-grind scheduling/pins/flags against it.
//
// SCORE: 3/68 words (4.4%) via tools/diff_near.py 0x8024F4B0 — the three
// matching words are unavoidable frame-skeleton pieces, not body content.
// TYPE NOTES from the DOL (not guesses):
//  - arg3 is a POINTER (lwz r11,8(r6)), same descriptor shape as arg0.
//  - x (arg1) and y (arg2) are UNSIGNED: both halvings are srwi, so the
//    params are u32, not s32 (an s32 draft emits srawi and loses a word).
//  - height is a u16 (lhz r7,4(r3)); stride (h*4) and row-pair (h*8) match
//    a 4-bytes-per-pixel / 8-byte-pair layout.
#include "types.h"

// Plane descriptor shared by src (arg0) and dst (arg3): u16 height at +4,
// three plane base addresses at +8/+C/+10. Matches Unk_1D9F1A68's layout
// (u16@4, s32@8/C/10); planes are byte addresses so they are u8 * here.
typedef struct YUVTileDesc {
    u8 _0[4];
    u16 h;
    u16 _6;
    u8 *plane0;
    u8 *plane1;
    u8 *plane2;
} YUVTileDesc;

// Helper fn_8024F5C0 copies TWO stride-separated 32-byte rows: it reads 8
// words from src, advances src by stride, stores to dst, advances dst by
// stride, then repeats once more (dcbz/dcbst cache hints included). The real
// register contract is (r12=src, r14=stride, r15=dst) with r20-r27 trashed —
// NOT the ABI (r3,r4,r5) this prototype uses. Declared with the honest arity
// so the call sites below read correctly; calls can never link-match.
extern void fn_8024F5C0(u8 *src, u32 stride, u8 *dst);

void fn_8024F4B0(YUVTileDesc *src_desc, u32 x, u32 y, YUVTileDesc *dst_desc) {
    u32 h;
    u32 t;
    u32 off;
    u32 stride;
    u32 rowpair;
    u8 *src;
    u8 *dst;

    // Luma phase (full resolution).
    y <<= 4;
    h = src_desc->h;
    t = y * h;
    src = src_desc->plane0;
    dst = dst_desc->plane0;
    x <<= 6;
    off = t + x;
    src += off;
    dst += off;
    stride = h * 4;
    rowpair = h * 8;
    fn_8024F5C0(src, stride, dst);
    fn_8024F5C0(src + 0x20, stride, dst + 0x20);
    src += rowpair;
    dst += rowpair;
    fn_8024F5C0(src, stride, dst);
    fn_8024F5C0(src + 0x20, stride, dst + 0x20);

    // Chroma phases (half resolution: height, y and x all halved).
    h >>= 1;
    y >>= 1;
    t = y * h;
    src = src_desc->plane1;
    dst = dst_desc->plane1;
    x >>= 1;
    stride = h * 4;
    off = t + x;
    src += off;
    dst += off;
    fn_8024F5C0(src, stride, dst);
    src = src_desc->plane2;
    dst = dst_desc->plane2;
    src += off;
    dst += off;
    fn_8024F5C0(src, stride, dst);
}
