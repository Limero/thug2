// WIP DRAFT (non-matching) — hand reconstruction from the DOL disassembly.
// STATUS: PARKED. 6.5% -> 14.6% (12/186 -> 27/185 masked words; got 180 -> 185
//   words vs want's 186). Round-2 pass, 2026-09-28.
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80078C5C -> DIFF
//   tools/venv/bin/python tools/flagdiff.py 0x80078C5C          -> 27/185 (14.6%)
//
// WHAT THE FUNCTION IS (fully recovered, unchanged from the 2026-09-25 rebuild):
//   Bilinear RGBA texture sample. `fn_80078948` (promoted, src/fn_80078948.c;
//   6 args — the call site really does set r8, and the callee reads r5-r8) gathers
//   the four texels surrounding a fixed-point position on `base` into a 16-byte
//   scratch buffer. This routine clamps the position, splits it into 10-bit
//   fractions and writes 4 blended bytes:
//     out[c] = (w0*tex[0x0+c] + w1*tex[0x4+c] + w2*tex[0x8+c]
//               + w3*tex[0xC+c] + 0x200) >> 10            c = 0..3
//   du = (1.0f/widthScale)*1024.0f, dv likewise for height;
//   stepx = ((w<<10) - w*du) >> 1, stepy = ((h<<10) - h*dv) >> 1.
//   Outer loop = rows (arg2), inner loop = columns (arg1). The two empty
//   `do {} while` spin loops before the main loops are REAL (retail keeps
//   `cmpwi; addi -1; bne`), so they stay in the source.
//
// WHAT CHANGED THIS ROUND (3 real fixes, all verified against the DOL):
//  1. BILINEAR WEIGHTS WERE WRONG. The DOL computes exactly four products:
//        A = fy-0x400   (subfic r9,r18,0x400)      B = fx-0x400  (subfic r0,r17)
//        w1' = A*fx     w0 = A*B     w2' = B*fy     w3 = fx*fy
//     with r18 = fy, r17 = fx. The old body computed `(0x400-fy)*fy` for w1
//     (wrong factor: fy where the DOL uses fx) and `+(0x400-fx)*fy` for w2
//     (right product, wrong SIGN). Corrected to
//        w0 = ((fy-0x400)*(fx-0x400)) >> 10;  w1 = ((fy-0x400)*fx) >> 10;
//        w2 = ((fx-0x400)*fy) >> 10;          w3 = (fx*fy) >> 10;
//     (The game's own formula subtracts w1'/w2'; that is what the binary does
//     and what is reproduced here. Keep the accumulate order 0,1,2,3.)
//  2. L2 PRE-DECREMENT LATCH on the inner spin loop (this really did apply):
//        do { } while (spin_inner-- != 0);   ->   do { } while (--spin_inner != -1);
//     Both run the loop exactly twice, but the post-decrement form makes cc1
//     materialise an extra `mr r0,r9` copy pseudo before the compare, which
//     retail does not have. The pre-decrement form folds into want's exact
//     `li r9,1; cmpwi r9,0; addi r9,r9,-1; bne` (4 words, no copy).
//     The col loop (`col--; ... while (col != 0)` -> `addic. r14,r14,-1; bne`)
//     and the row loop were ALREADY in the right shape — do not "fix" them.
//  3. The two s16 callee args are read through `volatile u16 *` so cc1 cannot
//     fold the sign extension into the load: plain `(s16)fr.q[0].h[1]` gives a
//     single `lha` (1 word), retail has `lhz` + `extsh` (2 words each). The
//     two pointers get spilled to 0x58 which costs 4 prologue words, but the
//     score is index-aligned and that is currently a net win (see DEAD ENDS
//     for the cleaner, lower-scoring form).
//
// KEY STRUCTURAL FACTS THE BODY REPRODUCES (all still verified against the DOL):
//  * ONE escaping frame struct at r1+8 (its address is passed to fn_80078948),
//    which is the only explanation for the four *never-read* `stw` of the
//    bilinear weights at 0x18..0x24. Layout: tex[16] 0x08, wt[4] 0x18,
//    p_base 0x28, p_w 0x2c, p_h 0x30, p_du 0x34, p_dv 0x38, retail hole 0x3c,
//    p_stepx 0x40, p_stepy 0x44, q[2] 0x48/0x4c, p_rowlimit 0x50, p_row 0x54,
//    want's wlim spill 0x58, 8-align pad 0x5c, shared fctiwz->stfd/lwz temp
//    0x60/0x64, stmw r14 at 0x68, LR at 0xb4  =>  frame 0xb0. All 22 slot
//    offsets and the frame size are exact; `stmw r14,0x68(r1)` now matches.
//  * `q[2]` is a `union {s32 i; u16 h[2];}` array: the s32 integer parts are
//    stored at 0x48/0x4c and the callee's two s16 args are read from the HIGH
//    HALFWORDS at 0x4a/0x4e. Retail never initialises those halves.
//  * The texel scratch is `u8 tex[16]` inside the struct so all 16 `lbz` use
//    r1-base displacements (0x08..0x17) and the callee's out pointer is
//    `addi r3, r1, 8`.
//  * Retail recomputes the two complements INSIDE the inner loop, so they must
//    stay inline in the weight expressions; named temps get LICM-hoisted (this
//    body still hoists one of them, see RESIDUAL).
//  * The two clamps are NOT the same shape: the outer one branches on the
//    ORIGINAL y (`cmpwi ypos,0`) and only then copies; the inner one copies
//    first and branches on the copy.
//  * Store order 0,1,2,3 in the source; cc1 emits 0,1,3,2 — which is want's
//    order. Writing m2c's 0,1,3,2 source order emits 0,1,2,3 instead.
//
// RESIDUAL (measured, 27/185 words; 1 word short overall):
//  * All remaining diffs are register-NUMBER or instruction-SCHEDULE only.
//    The arithmetic, frame, slot offsets, callee signature, control flow and
//    texel read order are byte-correct.
//  * RETAIL RUNS ~2 REGISTERS MORE PRESSURED IN THE PROLOGUE. It keeps
//    `width<<10`/`height<<10` in fresh registers (r11/r10) and re-reads
//    0x40/0x44 after the spin loops; this body folds them into r0/r4/r5 and
//    pays two extra `mr` copies and loses the two `lwz` reloads. Forcing the
//    reloads with `volatile` struct members makes it worse (4.8-9.1%).
//  * want's `li r7,1` (the spin init) is scheduled into the MIDDLE of the
//    float block (word 7, between the two `lfs`) and want also emits a dead
//    `mr r8,r9` page-anchor copy. Both are list-scheduler tie-breaks inside
//    the single entry basic block; every source reordering tried is a no-op,
//    because the block is the same either way.
//  * want spills the loop-invariant wlim to 0x58 (`stw`/`lwz` pair, +2 words)
//    and re-reads rowlimit from 0x50 (+1) instead of holding them in registers
//    — i.e. exactly the pressure difference above.
//  * Row-loop webs are HOME-ROTATED: want {out r31, col r14, cx r15, cy r16,
//    fx r17, fy r18, xpos r19, ypos r20}; this body {out r21, col r19,
//    cx/fx r30, ...}. Declaration order (2 permutations) and hard-register
//    pins do not move it (see DEAD ENDS). This is the documented
//    "big-function allocator/scheduler" wall; do not re-grind the arithmetic,
//    frame, struct or loop shape.
//  * x-clamp: want fuses copy+sign-test into `or. r0,r19,r19` + `blt`; cc1
//    always emits `mr`+`cmpwi`+`bge` here (6 source spellings tried, incl. a
//    nested-if layout and an opaque `li 0` birth).
//  * want's two weight complements use `subfic`; this body uses `addi` with
//    the identical value. The `0x400 - fy` spelling DOES produce `subfic` and
//    the same 14.5% score, but cc1 2.95 then drops a sign somewhere in the
//    blend (no `neg` appears and the four products come out negated), so it is
//    NOT semantically verified. Do not switch to it on opcode grounds alone.
//
// DEAD ENDS (all measured this round, all worse or no-ops at 14.5%):
//  * flags (flagdiff): -fno-schedule-insns 3.9%, -fno-schedule-insns2 9.7%,
//    -fno-gcse 6.0%, -fno-expensive-optimizations 6.6%;
//    -fno-sched-spec / -fno-strength-reduce / -fno-branch-count-reg = no-ops.
//    (The 2026-09-25 round already swept 21 singles/pairs including all of
//    the above, plus -fno-rerun-cse-after-loop and -fno-thread-jumps.)
//  * volatile struct members for p_w / p_h / p_stepx / p_stepy / p_rowlimit
//    (to block PRE): 4.8% - 9.1%, in every combination.
//  * L4 (extern FP symbol -> value-identical C literal 1.0f / 1024.0f):
//    EXACTLY no change (14.5% -> 14.5%); also inlining the constants and
//    pre-staging separate du_f/dv_f locals. The float block is not sensitive.
//  * local DECLARATION order (2 permutations: want's persistent-web order, and
//    reverse): no change.
//  * hard-register pins out->r31, xpos->r19, ypos->r20 (all three at once):
//    3.8%.  Pins on fx/fy/cy/cx/col were not attempted: those webs are born
//    late (per AGENTS 6y/70) and register vars are live-from-entry.
//  * opaque `__asm__("li %0,0")` births in either clamp, and the nested-if
//    x-clamp layout: no change.
//  * store-order rotations: fr.wt[0..3] rotated 10.8%, out[0..3] rotated 12.4%.
//  * one spilled volatile pointer for both s16 args (instead of two): 3.2%.
//  * CLEANER FORM OF FIX 3, kept here for the record: named `u16` temps plus a
//    `__asm__("" : "+r"(qa), "+r"(qb))` barrier gives retail's
//    `lhz r5,0x4a(r1); lhz r6,0x4e(r1); extsh; extsh` at the right r1
//    displacements with NO pointer spill — but the object is then 182 words
//    (4 short) and scores 7.0%. Use it if the word-count ever matters more
//    than the masked score.
//  * tools/twin_scan.py --wip 0x80078C5C: no matched byte-twin.
//    tools/near_twin_scan.py --addr 0x80078C5C: no same-size matched function.
//    Nothing to port.
//
// family=m2c range=0x80078C5C-0x80078F44 size=744B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
extern f32 lbl_8029583C;                          /* 1.0f    */
extern f32 lbl_80295840;                          /* 1024.0f */
void fn_80078948(s32 *out, s32 base, s16 a, s16 b, s32 w, s32 h);

/* The whole stack frame is one struct so that its address escapes into
   fn_80078948; that is what keeps the four weight stores alive in retail.
   `pad3c` is a genuine 4-byte hole in the retail frame (nothing in the DOL
   ever references 0x3c, yet 0x40 is stepx). */
struct texframe {
    u8 tex[16];              /* r1+0x08  fn_80078948 out: 4 texels x RGBA */
    s32 wt[4];               /* r1+0x18  bilinear weights (dead stores)   */
    s32 p_base, p_w, p_h;    /* r1+0x28  arg0 / arg1 / arg2 copies        */
    s32 p_du, p_dv;          /* r1+0x34  (1.0f/scale)*1024.0f             */
    s32 pad3c;               /* r1+0x3c  retail frame hole                */
    s32 p_stepx, p_stepy;    /* r1+0x40  per-column / per-row increments   */
    union { s32 i; u16 h[2]; } q[2]; /* r1+0x48 integer parts; the two
                                         callee args come from the high
                                         halfwords @0x4a / @0x4e       */
    s32 p_rowlimit;          /* r1+0x50  (h-1) << 10                     */
    s32 p_row;               /* r1+0x54  row counter                      */
};

void fn_80078C5C(s32 *base, s32 width, s32 height, void *dst,
                 f32 widthScale, f32 heightScale) {
    struct texframe fr;
    volatile u16 *q0h = (volatile u16 *)&fr.q[0];
    volatile u16 *q1h = (volatile u16 *)&fr.q[1];
    s32 w0, w1, w2, w3;
    s32 spin_outer, spin_next, spin_inner;
    s32 row, col, cx, cy, fx, fy;
    s32 xpos, ypos, wlim, hlim;
    u8 *out;
    f32 one, q10;

    one = lbl_8029583C;
    q10 = lbl_80295840;
    fr.p_base = (s32)base;
    fr.p_w = width;
    fr.p_h = height;
    fr.p_du = (s32)((one / widthScale) * q10);
    fr.p_dv = (s32)((one / heightScale) * q10);
    fr.p_stepx = ((width << 10) - width * fr.p_du) >> 1;
    fr.p_stepy = ((height << 10) - height * fr.p_dv) >> 1;

    /* Two empty spin loops survive in the retail code. */
    spin_outer = 1;
    do {
        spin_next = spin_outer - 1;
        spin_inner = 1;
        do { } while (--spin_inner != -1);
        spin_outer = spin_next;
    } while (spin_outer != -1);

    row = 0;
    xpos = fr.p_stepx;
    ypos = fr.p_stepy;
    out = (u8 *)dst;
    if (row < fr.p_h) {
        do {
            hlim = (fr.p_h - 1) << 10;
            fr.p_rowlimit = hlim;
            if (ypos < 0) {
                cy = 0;
            } else {
                cy = ypos;
                if (cy > fr.p_rowlimit) {
                    cy = fr.p_rowlimit;
                }
            }
            fr.p_row = row + 1;
            fy = cy & 0x3FF;
            fr.q[1].i = cy >> 10;
            if (fr.p_w != 0) {
                col = fr.p_w;
                wlim = (fr.p_w - 1) << 10;
                do {
                    cx = xpos;
                    if (cx < 0) {
                        cx = 0;
                    } else if (cx > wlim) {
                        cx = wlim;
                    }
                    fr.q[0].i = cx >> 10;
                    fx = cx & 0x3FF;
                    fn_80078948((s32 *)fr.tex, fr.p_base,
                                (s16)q0h[1], (s16)q1h[1],
                                fr.p_w, fr.p_h);
                    w0 = ((fy - 0x400) * (fx - 0x400)) >> 10;
                    w1 = ((fy - 0x400) * fx) >> 10;
                    w2 = ((fx - 0x400) * fy) >> 10;
                    w3 = (fx * fy) >> 10;
                    fr.wt[0] = w0;
                    fr.wt[1] = w1;
                    fr.wt[2] = w2;
                    fr.wt[3] = w3;
                    out[0] = (u8)((w0 * fr.tex[0] + w1 * fr.tex[4]
                                  + w2 * fr.tex[8] + w3 * fr.tex[0xC]
                                  + 0x200) >> 10);
                    out[1] = (u8)((w0 * fr.tex[1] + w1 * fr.tex[5]
                                  + w2 * fr.tex[9] + w3 * fr.tex[0xD]
                                  + 0x200) >> 10);
                    out[2] = (u8)((w0 * fr.tex[2] + w1 * fr.tex[6]
                                  + w2 * fr.tex[0xA] + w3 * fr.tex[0xE]
                                  + 0x200) >> 10);
                    out[3] = (u8)((w0 * fr.tex[3] + w1 * fr.tex[7]
                                  + w2 * fr.tex[0xB] + w3 * fr.tex[0xF]
                                  + 0x200) >> 10);
                    col--;
                    xpos += fr.p_du;
                    out += 4;
                } while (col != 0);
            }
            row = fr.p_row;
            xpos = fr.p_stepx;
            ypos += fr.p_dv;
        } while (row < fr.p_h);
    }
}
