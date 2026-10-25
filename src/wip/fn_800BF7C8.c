// WIP DRAFT (non-matching) — hand-rebuilt from the retail disassembly.
// === PARKED 2026-10-01 ===
// VERDICT: DIFF.  40/382 masked words by tools/ps_diff.py (10.5%); 56/388 (14.4%)
// with relocation masks applied.  want 1552B / got 1528B (-24B, -6 insns) —
// the closest length reached for this fn.  NOT PROMOTABLE.
// INERT: not registered in splits.txt/configure.py — never compiled, not
// counted in objdiff progress. activate via tools/wip.py.
//
// FLAG: -mps-float -fno-strength-reduce
// family=m2c range=0x800BF7C8-0x800BFDD8 size=1552B
//
// WHAT CHANGED THIS ROUND (all measured, all kept — the old body was 8.8%):
//   * both pair-latency delay windows are now counted loops. This is correct,
//     and the previous header's hard-wall claim was wrong. That claim was read
//     off the disassembler's pre-relocation operand field: for branch
//     relocations the addend is the displacement, so a self-branch shows up
//     with a misleading printed target. Plain C does emit the self-targeting
//     counter window. (The masked compare blanks branch displacements, so the
//     displacement never affected the score either way.)
//     docs/parkings/solved/30 makes the same objdump-based argument and needs
//     the same correction.
//   * scratch routed through a pointer makes the compiler hoist the frame
//     address setup, which is exactly the original prologue word (computed
//     mid-argument-setup, before the first call). Worth several masked words
//     by itself.
//   * a zero-code barrier splitting the first-argument web so the rec0 base is
//     not hoisted into yet another callee-saved register. It costs one
//     register copy, but the same body without it drops badly.
//   * offset-walker loops: the strided row loops compute the row address once
//     in the preheader and then walk it down, which is what the original does,
//     instead of re-deriving the scaled index per trip.
//   * the 3-case switch is a real countdown; that is where the original third
//     loop back-edge comes from.
//   * TAIL, semantics fix: retail copies TWO quads out of 0x20 and out of
//     0xB0 (to scr+0x58/0x60 and scr+0xB8/0xC0 — four psq ops the old body
//     did not emit at all) and it re-loads `arg0->unk0C` three more times in
//     that block.  `q_20`/`q_B0` are now `f32[8]` and each of the three
//     groups takes its own `p = arg0->unk0C`.  Census went from -12 to -6.
//
// STILL BLOCKING (why this is parked, worst first):
//  1. Frame too large vs original. The original keeps exactly four callee-saved
//     integer registers and re-materialises the base-plus-offset inside each
//     rec0 loop instead. We need five to seven, and the frame formula only
//     reaches the original size at four. Every attempt to break the rec0
//     address web -- barriers, fresh variables, volatile, CSE-breakers, two
//     differently-spelled bases -- either folds away or buys a register copy
//     and keeps the callee-saved slot anyway.
//  2. Decrement-compare fusion. The original has zero fused words and many
//     compares plus address setups; we emit several fused words and lose the
//     compares with them. The original candidate pair is adjacent there too
//     (one word apart), so the gap is a scheduling difference, not a source
//     shape. No flag lever exists (see below).
//  3. The 3-way min needs the original exact 8-copy chain -- running minimum
//     in one register, third compare against that register, result into a
//     callee-saved float. Written literally we get 6 copies: the compiler
//     coalesces one copy into its source. Output-tied barriers fix step 1 but
//     then coalesce the source with the saved result for step 3 instead.
//     A compiler-version copy-coalescing gap.
//  4. The scaled-reserve product emits one scaled multiply where the original
//     emits two with different destinations. A barrier on the estimate result
//     does not defeat it. Same value-forwarding gap.
//  5. What is left is the ordinary large-function pair allocator problem:
//     the original keeps base, scratch and float registers all live across the
//     checksum calls. Not reachable by restructuring alone.
//
// DEAD ENDS (do not re-run): scheduler and CSE flags -- all rejected or no-ops
// in this compiler, and several named tree flags do not exist. A float pin
// (reverted: no effect, cost a frame slot). Volatile pair lvalues are wrong:
// they emit vector move sequences instead of pair accesses; note the
// disassembler also mislabels ordinary pair words as those vector mnemonics,
// so never trust the mnemonic on its own here. Raw-word branch pads score
// very low and are now unnecessary.
//   Caveat for whoever scores this: ps_diff.py and the relocation-masked
//   count disagree (40/382 vs 56/388) because the masked compare blanks the
//   BD field of every branch.  Quote both.
#include "types.h"
#include "qb_constants.h"

/* ---- 0x1E0-stride record reached through arg0->rows; touched 0xA8..0xE7 ---- */
typedef struct {
    char pad0x00[0xA8];
    f32 f_A8; f32 f_AC; f32 f_B0; f32 f_B4;
    char pad0xB8[8];
    f32 f_C0;
    char pad0xC4[4];
    f32 f_C8; f32 f_CC; f32 f_D0;
    char pad0xD4[0xC];
    f32 f_E0; f32 f_E4;
} Rec1E0;

/* ---- 0x88-stride record at arg0+0x250; touched +4/+0x14/+0x24, 16B quads -- */
typedef struct {
    char pad0x00[4];
    f32 f_04;
    char pad0x08[0xC];
    f32 f_14;
    char pad0x18[0xC];
    f32 f_24;
    char pad0x28[0x60];
} Rec88;

/* ---- arg0 (the skater) ---- */
typedef struct {
    char pad0x00[0xC];
    s32 unk0C;                /* QB script object */
    char pad0x10[0x10];
    f32 q_20[8];              /* 0x20..0x3F  two 16B quads -> scr+0x58/0x60 */
    char pad0x40[0x30];
    f32 q_70[16];             /* 0x70..0xAF  eight 16B quads */
    f32 q_B0[8];              /* 0xB0..0xCF  two 16B quads -> scr+0xB8/0xC0 */
    char pad0xD0[0xA0];
    f32 unk170;
    char pad0x174[0x38];
    s32 unk1AC;               /* count */
    char pad0x1B0[8];
    f32 unk1B8, unk1BC;
    char pad0x1C0[4];
    char pad0x1C4[8];
    f32 unk1CC;               /* f32!  (shared class says s32) */
    char pad0x1D0[0x80];
    Rec88 rec0;               /* 0x250, stride 0x88 */
    char pad0x2D8[0];
    f32 q_2D8[4];             /* 0x2D8..0x2E7 */
    char pad0x2E8[8];
    s32 unk2F0;               /* Rec1E0 rows[] */
    char pad0x2F4[0x1014];
    s32 unk1308;
    char pad0x130C[4];
    f32 q_1310[2];            /* 0x1310 16B quad */
    f32 q_1318[2];            /* 0x1318 16B quad */
    char pad0x1320[0x28];
    s32 unk1348, unk134C;
    char pad0x1350[8];
    s32 unk1358, unk135C, unk1360, unk1364;
} Skater;

extern s32 GetChecksum_3(s32 obj, s32 hash);
extern s32 fn_80062680(s32 arg0);
extern s32 fn_801745B4(s32 arg0);
extern void fn_8009F9AC(s32 arg0, s32 arg1);
extern void fn_800C2320(Skater *arg0);
extern void fn_800C750C(Skater *arg0);
extern f32 lbl_80298F98;
extern f64 lbl_80298FA0;
extern f32 lbl_80298FA8;
extern f32 lbl_80298FAC;
extern s32 lbl_80305EAC;

void fn_800BF7C8(Skater *arg0) {
    __ps_t sp8[8];           /* 0x08..0x47  8-pair copy scratch */
    f32 blkbuf[6];
    f32 *blk = blkbuf;              /* 0x48..0x5F  [a,b]=pair0 [c,d]=pair1 [e,f]=res in */
    union { f64 d; u32 w[2]; } cvt;   /* 0x68..0x6F  int->f64 pool pair (§6j-1) */
    s32 i, j, k;
    s32 base, c1i, c2i, c0i, cnt, off;
    s32 a;
    f32 t0, t1, t2;
    f32 v31;
    __ps_t *rpq;
    Rec1E0 *row, *rp;
    Rec88 *r8;
    s32 *scr;

    arg0->unk1348 = GetChecksum_3(arg0->unk0C, QB_INPUT);
    a = GetChecksum_3(arg0->unk0C, QB_MODEL);
    arg0->unk134C = a;
    a = GetChecksum_3(arg0->unk0C, QB_MODEL);
    base = fn_80062680(*(s32 *)((char *)a + 0x210));

    i = 3;
    do {
        row = (Rec1E0 *)(arg0->unk2F0 + (i * 0x10 - i) * 0x20);
        rpq = (__ps_t *)((char *)base + i * 0x50 + 0xB0);
        i--;
        for (k = 4; k != 0; k--) { }
        sp8[0] = rpq[0];
        sp8[1] = rpq[1];
        sp8[2] = rpq[2];
        sp8[3] = rpq[3];
        sp8[4] = rpq[4];
        sp8[5] = rpq[5];
        sp8[6] = rpq[6];
        sp8[7] = rpq[7];
        row->f_A8 = -((f32 *)&sp8[6])[0];
        row->f_AC = ((f32 *)&sp8[7])[0];
        row->f_B4 = lbl_80298F98;
        row->f_B0 = -((f32 *)&sp8[6])[1];
    } while (i != -1);

    for (k = 4; k != 0; k--) { }
    rpq = (__ps_t *)((char *)base + 0x60);
    sp8[0] = rpq[0];
    sp8[1] = rpq[1];
    sp8[2] = rpq[2];
    sp8[3] = rpq[3];
    sp8[4] = rpq[4];
    sp8[5] = rpq[5];
    sp8[6] = rpq[6];
    sp8[7] = rpq[7];
    arg0->q_2D8[0] = -((f32 *)&sp8[6])[0];
    arg0->q_2D8[1] = ((f32 *)&sp8[7])[0];
    arg0->q_2D8[2] = -((f32 *)&sp8[6])[1];
    arg0->q_2D8[3] = lbl_80298F98;

    rp = (Rec1E0 *)(arg0->unk2F0 + 0x658);
    c1i = -1; c2i = -1; c0i = -1;
    j = 3;
    k = 4;
    do {
        switch (*(s32 *)rp) {
        case 1: c1i = j; break;
        case 2: c2i = j; break;
        case 0: c0i = j; break;
        }
        rp = (Rec1E0 *)((char *)rp - 0x1E0);
        j--;
    } while (--k != 0);

    a = c1i * 0x50;
    c0i = c0i * 0x50;
    cnt = arg0->unk1AC;
    c2i = c2i * 0x50;
    arg0->unk1B8 = fabsf(*(f32 *)((char *)(a + base) + 0xE4)
                      - *(f32 *)((char *)(c0i + base) + 0xE4));
    arg0->unk1BC = fabsf(*(f32 *)((char *)(a + base) + 0xE0)
                      - *(f32 *)((char *)(c2i + base) + 0xE0));

    if (cnt != 0) {
        i = cnt - 1;
        off = (i * 0x10 - i) * 0x20;
        while (i != 0) {
            rp = (Rec1E0 *)(arg0->unk2F0 + off);
            i--;
            t0 = rp->f_C8;
            t1 = rp->f_AC;
            t0 = t0 + t0;
            t2 = rp->f_D0;
            t0 = t1 + t0;
            rp->f_AC = t0;
            t0 = -t0 + t1;
            t1 = arg0->unk170;
            cvt.w[1] = (u32)arg0->unk1AC;
            cvt.w[0] = 0x43300000;
            t1 = t1 * (f32)(cvt.d - lbl_80298FA0);
            t1 = t1 * t2;
            t0 = t0 - lbl_80298FA8 / t1;
            rp->f_C0 = t0;
        }
    }

    v31 = arg0->unk1CC;
    j = 1;
    {
    Rec88 *r8b = (Rec88 *)((char *)arg0 + 0x250);
    do {
        t1 = r8b->f_04;
        t0 = v31;
        if (t1 < t0) t0 = t1;
        v31 = t0;
        t2 = t1 + r8b->f_14;
        t0 = v31;
        if (t2 < t0) t0 = t2;
        v31 = t0;
        t2 = t1 + r8b->f_24;
        v31 = t0;
        if (t2 < t0) v31 = t2;
        t0 = v31;
        r8b = (Rec88 *)((char *)r8b - 0x88);
    } while (--j);
    }

    a = fn_801745B4(lbl_80305EAC);
    arg0->unk1358 = a;
    arg0->unk1360 = GetChecksum_3(a, QB_SKATERCOREPHYSICS);
    arg0->unk1364 = GetChecksum_3(arg0->unk1358, QB_TRIGGER);
    if (arg0->unk1308 == 0) {
        fn_8009F9AC(arg0->unk1358, 1);
    } else {
        arg0->unk135C = GetChecksum_3(arg0->unk1358, QB_ANIMBLENDER);
    }

    blk[0] = lbl_80298FAC;
    blk[3] = lbl_80298FAC;
    blk[1] = lbl_80298FAC;
    blk[2] = lbl_80298FAC;
    if (arg0->unk1AC != 0) {
        i = arg0->unk1AC - 1;
        rpq = (__ps_t *)(arg0->unk2F0 + (i * 0x10 - i) * 0x20 + 0xA8);
        while (i != 0) {
            i--;
            ((__ps_t *)&blk[0])[0] = __builtin_ps_add(((__ps_t *)&blk[0])[0], rpq[0]);
            ((__ps_t *)&blk[2])[0] = __builtin_ps_add(((__ps_t *)&blk[2])[0], rpq[1]);
            off -= 0x1E0;
        }
    }

    cnt = arg0->unk1AC;
    cvt.w[1] = (u32)cnt;
    cvt.w[0] = 0x43300000;
    t0 = (f32)(cvt.d - lbl_80298FA0);
    blk[5] = t0;
    blk[4] = t0;
    ((__ps_t *)&blk[2])[0] = __builtin_ps_muls0(((__ps_t *)&blk[4])[0], __builtin_ps_res(((__ps_t *)&blk[4])[0]));
    ((__ps_t *)&blk[0])[0] = __builtin_ps_muls0(((__ps_t *)&blk[4])[0], __builtin_ps_res(((__ps_t *)&blk[4])[0]));
    blk[3] = lbl_80298FAC;
    blk[1] = v31;
    if (cnt != 0) {
        i = cnt - 1;
        rpq = (__ps_t *)(arg0->unk2F0 + (i * 0x10 - i) * 0x20 + 0xA8);
        while (i != 0) {
            i--;
            rpq[0] = __builtin_ps_sub(((__ps_t *)&blk[0])[0], rpq[0]);
            rpq[1] = __builtin_ps_sub(((__ps_t *)&blk[2])[0], rpq[1]);
            rpq = (__ps_t *)((char *)rpq - 0x1E0);
        }
    }

    j = 1;
    { Skater *ap = arg0; __asm__("" : "+r"(ap)); r8 = &ap->rec0; }
    do {
        rpq = (__ps_t *)r8;
        rpq[0] = __builtin_ps_sub(((__ps_t *)&blk[0])[0], rpq[0]);
        rpq[1] = __builtin_ps_sub(((__ps_t *)&blk[2])[0], rpq[1]);
        r8 = (Rec88 *)((char *)r8 - 0x88);
    } while (--j);

    rpq = (__ps_t *)&arg0->q_2D8[0];
    rpq[0] = __builtin_ps_sub(((__ps_t *)&blk[0])[0], rpq[0]);
    rpq[1] = __builtin_ps_sub(((__ps_t *)&blk[2])[0], rpq[1]);
    rpq = (__ps_t *)&arg0->q_1310[0];
    rpq[0] = __builtin_ps_sub(((__ps_t *)&blk[0])[0], rpq[0]);
    rpq[1] = __builtin_ps_sub(((__ps_t *)&blk[2])[0], rpq[1]);

    fn_800C2320(arg0);
    scr = (s32 *)arg0->unk0C;
    { s32 *p = (s32 *)arg0->unk0C; ((__ps_t *)((char *)p + 88))[0] = ((__ps_t *)&arg0->q_20[0])[0];
      ((__ps_t *)((char *)p + 96))[0] = ((__ps_t *)&arg0->q_20[4])[0]; }
    { s32 *p = (s32 *)arg0->unk0C; ((__ps_t *)((char *)p + 184))[0] = ((__ps_t *)&arg0->q_B0[0])[0];
      ((__ps_t *)((char *)p + 192))[0] = ((__ps_t *)&arg0->q_B0[4])[0]; }
    { s32 *p = (s32 *)arg0->unk0C;
      ((__ps_t *)((char *)p + 120))[0] = ((__ps_t *)&arg0->q_70[0])[0];
      ((__ps_t *)((char *)p + 128))[0] = ((__ps_t *)&arg0->q_70[2])[0];
      ((__ps_t *)((char *)p + 136))[0] = ((__ps_t *)&arg0->q_70[4])[0];
      ((__ps_t *)((char *)p + 144))[0] = ((__ps_t *)&arg0->q_70[6])[0];
      ((__ps_t *)((char *)p + 152))[0] = ((__ps_t *)&arg0->q_70[8])[0];
      ((__ps_t *)((char *)p + 160))[0] = ((__ps_t *)&arg0->q_70[10])[0];
      ((__ps_t *)((char *)p + 168))[0] = ((__ps_t *)&arg0->q_70[12])[0];
      ((__ps_t *)((char *)p + 176))[0] = ((__ps_t *)&arg0->q_70[14])[0]; }
    rpq = (__ps_t *)((char *)scr + 120);
    ((__ps_t *)((char *)scr + 208))[0] = rpq[0];
    rpq = (__ps_t *)((char *)scr + 128);
    ((__ps_t *)((char *)scr + 216))[0] = rpq[0];
    rpq = (__ps_t *)((char *)scr + 136);
    ((__ps_t *)((char *)scr + 224))[0] = rpq[0];
    rpq = (__ps_t *)((char *)scr + 144);
    ((__ps_t *)((char *)scr + 232))[0] = rpq[0];
    rpq = (__ps_t *)((char *)scr + 176);
    ((__ps_t *)((char *)scr + 264))[0] = rpq[0];
    rpq = (__ps_t *)((char *)scr + 152);
    ((__ps_t *)((char *)scr + 240))[0] = rpq[0];
    rpq = (__ps_t *)((char *)scr + 160);
    ((__ps_t *)((char *)scr + 248))[0] = rpq[0];
    rpq = (__ps_t *)((char *)scr + 168);
    ((__ps_t *)((char *)scr + 256))[0] = rpq[0];
    fn_800C750C(arg0);
}
