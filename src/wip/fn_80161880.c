// WIP DRAFT (non-matching) — semantic PS reconstruction
// family=m2c range=0x80161880-0x80161A00 size=384B
// PARKED 2026-10-03: 92.7% (-mps-float), 89/96 words. IMPROVED from 91.7%:
// `F.w80 = F.wa0;` must be written BEFORE `F.b88 = byte_value;` -- want emits
// [stb r9,0x88(r1)][stw r0,0x80(r1)] in that order (the radius w80 store is
// scheduled before the id-byte b88 store even though b88 is assigned first).
// That swap also flips the r0/r9 allocation coin on both operands.
// RESIDUAL (3 words, 0x80161968..70) is one rotated hoist window. The original
// zeroes r8, loads the id byte at displacement 3 off the live r30 base into
// r9, and builds the payload address into r29 off the stack pointer plus 0x50,
// while this draft builds the payload address first, re-derives the id byte
// at frame offset 0x93 into r9, and zeroes r8 last.
// Two independent knobs at once: (a) emission order of the `li r8,0` (the
// w50=0 constant) vs the `addi` for `payload = &F.w50`, and (b) want indexes
// the id byte off the LIVE `id_ptr` base r30 (r1+0x90, disp 3) while ngccc
// re-derives r1+0x93.  Ruled out: reading via `((u8 *)id_ptr)[3]` (63.5%),
// hoisting `F.w50 = 0` to the top of the tail (89.6%), moving `F.p2c = payload`
// after `F.b28` (85.4%) or after `F.h2a` (84.4%), moving `F.h2a` before
// `F.b28` (88.5%), taking `payload` at its use site, `u8`/`((u8*)&F.id90)[3]`
// spellings, and -fno-sched-spec / -fno-expensive-optimizations /
// -fno-strength-reduce (all no-ops). -fno-schedule-insns2 is much worse (75%).
// No inline assembly or fake body transcription is used.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RE-MEASURED 2026-10-05 (round rt1). Still 92.7% (-mps-float), same three
// words, and the tail is EXTREMELY sensitive to statement order: 12 reorderings
// of the six tail statements (`payload`/`F.f84`/`byte_value`/`F.w80`/`F.b88`/
// `F.w50`) all collapse to 51.0-53.1%, i.e. the current order is the only one
// in the NEAR band and it is worth ~40 points. Do NOT permute this tail.
// Reading the id byte through the live base (`((u8 *)id_ptr)[3]`, which is
// exactly what want's `lbz r9,3(r30)` says) is 51.0% and length-mismatched
// (384B want vs 360B object): making `id_ptr` address-taken-through kills the
// rematerialisation of the frame base and r28/r29 swap roles, so the spelling
// that is RIGHT for the one instruction is wrong for the whole function.
// Zero-code `"+r"` barriers inside the tail: 51.0% (`base`), 52.1% (`off`).
// Coin-flip parked; the current body is the best known.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;

typedef struct fr {
    __ps_t q0;
    __ps_t q1;
    __ps_t q2;
    __ps_t q3;
    u8 b28;
    u8 pad29;
    u16 h2a;
    void *p2c;
    s32 unk8;
    s32 w34;
    u8 b38;
    u8 pad39[0x17];
    s32 w50;
    u8 pad54[4];
    __ps_t v58;
    __ps_t v60;
    __ps_t v68;
    __ps_t v70;
    s32 w78;
    s32 w7c;
    s32 w80;
    f32 f84;
    u8 b88;
    u8 pad89[7];
    union {
        s32 w;
        u8 b[4];
    } id90;
    s32 w94;
    s32 w98;
    f32 f9c;
    s32 wa0;
} fr;

s32 fn_8021B55C(s32, s32);
void fn_80137CB4(void *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetVector(CStruct *, s32, void *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8013DE78(void *, void *);

bool ScriptBroadcastProjectile(CStruct *arg0) {
    fr F;
    s32 handle;
    void *payload;
    s32 *id_ptr;
    s32 byte_value;
    s32 header_size;

    handle = fn_8021B55C(lbl_80305F9C, 0);
    if (handle != 0) {
        id_ptr = &F.id90.w;
        fn_80137CB4(&F.b28);
        GetChecksum_2(arg0, QB_OBJID, id_ptr, 0);
        GetChecksum_2(arg0, QB_TYPE, &F.w94, 0);
        GetChecksum_2(arg0, QB_AMMO_TYPE, &F.w98, 0);
        GetVector(arg0, QB_POS, &F.q0, 0);
        GetVector(arg0, QB_VEL, &F.q2, 0);
        GetFloat(arg0, QB_SCALE, &F.f9c, 0);
        GetInteger(arg0, QB_RADIUS, &F.wa0, 0);
        payload = &F.w50;
        F.f84 = F.f9c;
        byte_value = F.id90.b[3];
        F.w80 = F.wa0;
        F.b88 = byte_value;
        F.w50 = 0;
        F.w78 = F.w94;
        F.w7c = F.w98;
        F.p2c = payload;
        F.b28 = 0x83;
        header_size = 0x40;
        F.h2a = header_size;
        F.w34 = 2;
        F.b38 = 8;
        F.v58 = F.q0;
        F.v60 = F.q1;
        F.v68 = F.q2;
        F.v70 = F.q3;
        fn_8013DE78(handle, &F.b28);
    }
    return true;
}
