// WIP DRAFT (non-matching) — fn_801B4278
// family=m2c range=0x801B4278-0x801B4404 size=396B
// extra_cflags: -mps-float -fno-schedule-insns
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Semantics recovered from the want (see PARKED note at the end):
//   arg0->unk0xC is a 2-float-pair object (f58/f60); arg0->f68/f70 are two
//   separate floats 8 bytes apart; arg0->fA4 is f32.
//   Local pool = 9 8-byte `union {__ps_t p; f32 w[2];}` slots at r1+0x08:
//     V0 = f68-f58, V1 = f70-f60 (later normalised), V2/V3 = sub->{f58,f60}
//     V4/V5 = the 4-float out-vector (only .x/.y copied back to sub)
//     V6/V7 = &out passed to fn_801B7484, V8 = {1/len, 1.0f}
//   Globals: 0x802ABFB8 = 0.0f (K, merged into the dot product),
//            0x802AC054 = 1000.0f, 0x802AC058 = 0.0f, 0x802AC05C = 1.0f.
#include "types.h"
#include "dolphin/SN_PS.h"

extern char lbl_802ABFB8[];
extern f32 lbl_802AC054;
extern f32 lbl_802AC058;
extern f32 lbl_802AC05C;

typedef union { __ps_t p; f32 w[2]; } S;

typedef struct SubO {
    char pad0x0[0x58];
    __ps_t f58;
    __ps_t f60;
} SubO;

typedef struct Obj {
    char pad0x0[0xC];
    SubO *unk0xC;
    char pad0x10[0x58];
    __ps_t f68;
    __ps_t f70;
    char pad0x78[0x2C];
    f32 fA4;
} Obj;

typedef struct Hnd {
    char pad0x0[0x30];
    f32 f30;
} Hnd;

void Script_RunScript(s32, s32, s32, s32, s32);
Hnd *GetChecksum_3(SubO *, s32);
void fn_801B5BBC(Obj *);
void fn_801B7484(Obj *, void *);
void fn_800D9DB0(Hnd *);

/* K = the 0.0f pair at 0x802ABFB8; W = the squared-length accumulation;
   MAG = its pair-sum, i.e. |dx,dy|^2.  Written as macros so the whole
   expression is duplicated (mag / mag2 / rsqrte) and cc1 CSEs it back into
   ONE ps_mul/ps_merge00/ps_madd/ps_sum0 chain -- which is what the want has. */
#define K (*(__ps_t *)&lbl_802ABFB8[0])
#define W (__builtin_ps_madd(__builtin_ps_merge00(__builtin_ps_mul(V[1].p, V[1].p), K), V[0].p, V[0].p))
#define MAG (__builtin_ps_sum0(W, W, W))

void fn_801B4278(Obj *arg0) {
    S V[9];
    SubO *sub;
    __ps_t r;
    f32 th;
    f32 mag;
    f32 mag2;
    Hnd *hnd;
    f32 *pf;

    sub = arg0->unk0xC;
    V[0].p = __builtin_ps_sub(arg0->f68, sub->f58);
    V[1].p = __builtin_ps_sub(arg0->f70, sub->f60);
    th = lbl_802AC054;
    mag = MAG;
    if (mag <= th) {
        Script_RunScript(0x44EB4098, 0, (s32)sub, 0, 0);
        return;
    }
    mag2 = MAG;
    if (mag2 > lbl_802AC058) {
        r = __builtin_ps_rsqrte(MAG);
        V[8].p = r;
        V[0].p = __builtin_ps_muls0(V[0].p, r);
        V[8].w[1] = lbl_802AC05C;
        V[1].p = __builtin_ps_mul(V[1].p, V[8].p);
    }
    hnd = GetChecksum_3(arg0->unk0xC, 0x0A015E17);
    fn_801B5BBC(arg0);
    sub = arg0->unk0xC;
    V[2].p = sub->f58;
    V[3].p = sub->f60;
    pf = (f32 *)&V[4].w[0];
    pf[0] = (V[0].w[0] * hnd->f30) * arg0->fA4 + V[2].w[0];
    pf[1] = V[2].w[1];
    pf[2] = (V[1].w[0] * hnd->f30) * arg0->fA4 + V[3].w[0];
    pf[3] = lbl_802AC05C;
    sub->f58 = *(volatile __ps_t *)&pf[0];
    sub->f60 = *(volatile __ps_t *)&pf[1];
    V[6].p = V[2].p;
    V[7].p = V[3].p;
    fn_801B7484(arg0, &V[6]);
    fn_800D9DB0(hnd);
}
#undef MAG
#undef W
#undef K

// PARKED 2026-10-03: 18.18% 404B/396B, frame 0x70 vs want 0x60.
// Full decompilation above (every ps_*/psq_* op in the want is emitted, in
// order, with the right frame offsets 0x08..0x4F); only the frame size and
// FPR choices differ.
//
// PROVEN BLOCKER: the want keeps TWO paired-single values live in FPRs across
// the conditional `Script_RunScript` call (f11 = V0 from `ps_sub` is reused by
// `ps_madd` at +0x24 AND `ps_muls0` at +0x58; f13 = the `ps_sum0` result is
// reused by `ps_rsqrte` at +0x44), with NO stack slot for either -- want frame
// 0x60 == exactly V[9] (0x48 at r1+0x08) + 4 pad + stmw r29 (0x54..0x5f).
// ngccc 2.95.3 under -mps-float cannot do that. Measured with 4 probe TUs:
//   * PS value live across a branch, used only by PS ops  -> frame +0x00
//   * the same value ALSO converted to f32 (any f32 use) -> frame +0x10
//     (it gets an 8-byte slot + an stfd/lfd pair)
//   * same with `register __ps_t`, with `S`/`SN_PS_type` wrapper, or with the
//     value as an unnamed CSE'd temporary -> identical +0x10.
// Both `mag`/`mag2` (f32 copies of the sum0 result) are exactly that case, so
// the sum0 result lands at r1+0x60 and the frame grows to 0x70. The project's
// matched siblings (src/fn_801B19DC.c, fn_801B27F8) get round this with
// `register __ps_t x __asm__("frN")` FPR pins, which is out of scope here.
//
// Secondary residual (why the body is not simply "one instruction short"):
// the want re-reads V[1] from memory (`psq_l f0,8(r29); ps_mul f0,f0,f0`)
// but uses V[0] straight out of the register (`ps_madd f0,f11,f11,f0`).
// Making V volatile forces the V[0] reload too; making it non-volatile (what
// is here) lets cc1 CSE the duplicated MAG chain but keeps V[1] in f10.
// Getting both needs the same pinned-register trick.
//
// RE-TRIAGED 2026-10-19: sweep still DIFF — the FPR-pin wall stands
// (needs `register __ps_t` pins, out of scope). Parked as-is.
// FLAG DISCLOSURE: 18.18% needs the per-object `-fno-schedule-insns` on top of
// `-mps-float` (with -mps-float alone this body scores 16.16%). Retail was
// built WITH a scheduler, so the flag is a fitted crutch, not the cause; it
// just makes cc1 emit our statement order literally, which is much closer to
// retail's. See recipes §7q for the same caveat on another PS draft.
