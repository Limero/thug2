// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A16B8-0x800A17EC (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
#include "dolphin/SN_PS.h"

// file-local typedefs: the shared Unk_* classes are wrong for this walk
// (see the byte-proven siblings src/fn_800A71E0.c / src/fn_800A7264.c, and
// src/fn_800A15DC.c for the s16-offset dispatch shape).
typedef struct V16B8 { char _0[0x38]; s16 unk0x38; s32 (*unk0x3C)(void *); } V16B8;
typedef struct C16B8 { char _0[0x2C]; V16B8 *unk0x2C; } C16B8;
typedef struct N16B8 {
    char _0[0x10];
    C16B8 *unk0x10;
    char _14[0x44];
    __ps_t unk0x58;
    __ps_t unk0x60;
} N16B8;
typedef struct G16B8 { char _0[0xC]; N16B8 *unk0xC; } G16B8;
typedef struct A16B8 { char _0[4]; G16B8 *unk0x4; G16B8 *unk0x8; s32 unk0xC; } A16B8;

extern f32 lbl_80297BD0;
extern char lbl_80297BD8[];
extern __ps_t lbl_80297B28;
extern char lbl_80297BF0[];

N16B8 *fn_800A71E0(A16B8 *, G16B8 *, s32);
N16B8 *fn_800A7264(A16B8 *);

s32 fn_800A16B8(N16B8 *arg0, s32 arg1) {
    A16B8 sp8;
    SN_PS_type res;
    __ps_t f0;
    __ps_t f10;
    __ps_t f11;
    __ps_t f12;
    __ps_t f13;
    f32 best;
    s32 bestcand;
    s32 cand;
    f32 x;
    f32 y;
    V16B8 *vt;
    void *cont;
    G16B8 *blk;
    register A16B8 *sp28 __asm__("r28");
    register s32 key __asm__("r29");

    {
        register A16B8 *sp30 __asm__("r30");
        sp30 = &sp8;
        sp30->unk0x4 = 0;
        sp30->unk0x8 = (G16B8 *)lbl_80297BD8;
        key = arg1;
        blk = (G16B8 *)lbl_80297BF0;
        cont = (void *)arg0->unk0x10;
        sp28 = &sp8;
        vt = ((C16B8 *)cont)->unk0x2C;
        cand = (s32)fn_800A71E0(sp30, ((s32 (*)(void *))vt->unk0x3C)(cont + vt->unk0x38), key);
    }
    if (cand == arg0) {
        register A16B8 *a3 __asm__("r3");
        __asm__ volatile("mr %0,%1" : "=r"(a3) : "r"(sp28));
        cand = (s32)fn_800A7264(a3);
    }
    if (cand == 0) {
        /* the sentinel is already live in a callee-saved reg here */
        sp28->unk0x8 = blk;
        return 0;
    }
    best = lbl_80297BD0;
    bestcand = cand;
    do {
        f13 = arg0->unk0x58;
        f12 = ((N16B8 *)cand)->unk0x58;
        f0 = arg0->unk0x60;
        f10 = ((N16B8 *)cand)->unk0x60;
        f13 = __builtin_ps_sub(f13, f12);
        f11 = lbl_80297B28;
        f13 = __builtin_ps_mul(f13, f13);
        f0 = __builtin_ps_sub(f0, f10);
        f0 = __builtin_ps_merge00(f0, f11);
        f0 = __builtin_ps_madds0(f0, f0, f13);
        f0 = __builtin_ps_sum0(f0, f0, f0);
        f0 = __builtin_ps_rsqrte(f0);
        f0 = __builtin_ps_res(f0);
        res.ps = f0;
        x = res.flt.hi;
        y = x;
        if ((cand != arg0) && (y < best)) {
            best = y;
            bestcand = cand;
        }
        cand = (s32)fn_800A7264(&sp8);
    } while (cand != 0);
    /* rematerialised here, NOT through blk (that gives 75 words, 2 short) */
    sp28->unk0x8 = (G16B8 *)lbl_80297BF0;
    return bestcand;
}
