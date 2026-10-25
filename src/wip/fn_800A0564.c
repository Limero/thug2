// PARKED a30 (2026-10-03): DIFF 26.6% masked (102 bad of 139 words; 102 = the
// 139-word got padded 1 insn to 556B vs the 552B symbol). Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800A0564
//
// WHAT IS ACTUALLY LEFT (single root cause): want parks `&fr.v[0]` in r31
// (`addi r31, r1, 8` in the PROLOGUE, then `mr r3, r31` at both call sites and
// `stfsx f13, r31, r25` in the slow path) => 8 saved GPRs, `stmw r24, 0x20(r1)`.
// We emit 7 saved GPRs, `stmw r25, 0x24(r1)`, and REMATERIALISE `addi r3, r1, 8`
// / `addi r11, r1, 8` at each use instead. That one missing prologue insn makes
// the compiled body 556B, so EVERYTHING from +0x30 on is off by one word, and
// the callee-saved window is shifted by one register, which is the other ~60
// diff words (arg0 r29 vs r30, arg2 r25 vs r24, base r6 vs r7, i r26 vs r25,
// rj r29 vs r28, k*4 r28 vs r29, ri r31 vs r26).
//
// RULED OUT THIS ROUND (all measured, all WORSE or identical):
//  * `f32 *o = fr.v;` used at the two helper calls + the slow-path stores
//    (v1), only at the helper calls (v4), only at the stores (v6), declared
//    before vs after every other local (v3b): ALL give 10.8%. It DOES fix
//    `stmw r24, 0x20(r1)` and does put the address in a callee-saved reg, but
//    ngccc's local-allocator always hands the (whole-function-range) array
//    pseudo the SECOND callee-saved slot -- `addi r25, r1, 8` -- because arg2
//    (var_r5, live from entry) sorts first. One extra early pseudo shifts the
//    whole window by one and costs more than the rematerialisation it removes.
//  * Interleaved local declarations `i, ri, j, rj, k, rk` (matching want's
//    r25..r30 order): byte-identical output to the current file. Local
//    declaration order has ZERO effect on ngccc allocation here.
//  * Branch polarity swap to `if (tr <= 0.0f) {slow} else {fast}`: want's
//    `ble` to the slow path proves `tr > 0.0f` is the retail spelling; the
//    swap emits `cror cr0un,cr0eq,cr0lt` + `bns` and inverts the join test to
//    `bge`. Strictly worse.
//  * **The lbl_80297B74/78/7C float constants are NOT part of the diff.**
//    `tools/want_vs_got.py` prints `lis r9, 0` / `lfs f0, 0(r9)` as mismatches
//    because the draft is scored unlinked, but compile_fn masks R_PPC_ADDR16_HA
//    (low 16 bits of the `lis`) and R_PPC_ADDR16_LO (low 16 bits of the `lfs`
//    displacement), so those 6 words score as MATCHES. Do not spend a compile
//    on them. (This is a masked scorer, so it is the *want* bytes that are
//    masked too - `lis r9, 0x8029` vs `lis r9, 0` compare equal.)
//
// NEXT IDEA (the only one I believe in): want's r31 is almost certainly NOT a
// cc1 pseudo. cc1's 7 pseudos would then be r24..r30 in the order
// arg2, i, ri, j, rj, k, rk (exactly want's r24,r25,r27,r28,r29,r30 with r26
// and the interleaving) and r31 would be a RELOAD pseudo - reload allocates
// after cc1 and takes the first free callee-saved reg, i.e. r31 - and reload
// keeps it in a register instead of rematerialising only because the value is
// needed in several reload regions (pre-call / post-call / join). So the lever
// is to make reload see the address as non-rematerialisable in the fast-path
// region while keeping ONE pseudo (any extra address pseudo would add a 9th
// callee-saved reg and the frame only has 8 slots). Corroborating detail:
// want mixes `lfs f1, 8(r1)` (v[0]), `lfs f2, 0xc(r1)` (v[1]), `stfs 0x14(r1)`
// (v[3]) with `lfs f3, 8(r31)` (v[2]) in the SAME join block - impossible from
// one spelling, because reload picks the form at RTL time and CSE does not
// unify `frame+0x10` with `(plus <reg> 8)` across the post-call reload region
// boundary. That implies the retail source spells v[2] through a pointer to
// v[0] and v[0]/v[1]/v[3] directly - try `fn_8012788C(ctx, QB_QUAT, fr.v[0],
// fr.v[1], o[2])` / `o[2] = -o[2];` on top of a pointer form that still lets
// reload allocate r31 (v2 in <scratch> was never measured: v1 + those
// two v[2] reads, expected ~10.8%).
//
// WIP DRAFT (non-matching) - hand-reconstructed from the DOL disassembly.
// range=0x800A0564-0x800A078C size=552B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// SCORE: 26.6% masked. tools/test_wip_drafts.py --addr 0x800A0564 => DIFF.
// Compiled object is 556B vs the 552B symbol range (1 instruction long).
// NOT promotable.
//
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_80297B74[];
extern f32 lbl_80297B78[];
extern f32 lbl_80297B7C[];

f32 sqrtf(f32);
void fn_8002C8FC(void *o, f32 v);
void fn_8002C904(void *o, f32 a, f32 b, f32 c);
s32 fn_8012788C(s32 ctx, s32 hash, f32 x, f32 y, f32 z);

typedef struct {
    char pad0[0x78];
    f32 m[3][4];
} Mtx_t;

s32 fn_800A0564(Mtx_t *self, s32 unused, CScript *arg2) {
    struct { f32 v[4]; char pad[8]; } fr;
    f32 (*mb)[4];
    f32 *ri;
    f32 *rj;
    f32 *rk;
    f32 t;
    f32 tr;
    s32 i;
    s32 j;
    s32 k;

    mb = &self->m[0];
    tr = self->m[0][0] + self->m[1][1] + self->m[2][2];
    if (tr > lbl_80297B74[0]) {
        t = sqrtf(tr + lbl_80297B78[0]);
        fn_8002C8FC(fr.v, t * lbl_80297B7C[0]);
        t = lbl_80297B7C[0] / t;
        fn_8002C904(fr.v,
                    (self->m[2][1] - self->m[1][2]) * t,
                    (self->m[0][2] - self->m[2][0]) * t,
                    (self->m[1][0] - self->m[0][1]) * t);
    } else {
        i = 0;
        if (self->m[1][1] > self->m[0][0]) {
            i = 1;
        }
        ri = mb[i];
        if (self->m[2][2] > ri[i]) {
            i = 2;
        }
        j = (i + 1) % 3;
        k = (j + 1) % 3;
        ri = mb[i];
        rj = mb[j];
        rk = mb[k];
        t = sqrtf(ri[i] - (rj[j] + rk[k]) + lbl_80297B78[0]);
        fr.v[i] = t * lbl_80297B7C[0];
        t = lbl_80297B7C[0] / t;
        fr.v[j] = (rj[i] + ri[j]) * t;
        fr.v[k] = (rk[i] + ri[k]) * t;
        fr.v[3] = (rk[j] - rj[k]) * t;
    }
    if (fr.v[3] < lbl_80297B74[0]) {
        fr.v[0] = -fr.v[0];
        fr.v[1] = -fr.v[1];
        fr.v[2] = -fr.v[2];
    }
    fn_8012788C(arg2->unk0x18, QB_QUAT, fr.v[0], fr.v[1], fr.v[2]);
    return 1;
}
