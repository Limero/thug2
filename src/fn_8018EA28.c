// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018EA28-0x8018EC08 (480B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80301A38;
extern s32 lbl_80305EAC;
extern __ps_t lbl_802A95D8;
extern f32 lbl_802A9658;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void AddInteger(CStruct *, s32, s32);
s32 fn_800A398C(s32, s32);
s32 fn_801745B4(s32);
f32 sqrtf(f32);

/* position: 0x58 = {x,y} pair, 0x5C = y (re-read as a scalar by the caller),
 * 0x60 = {z,-} pair.  0x58/0x60 are __ps_t so they emit psq_l; the 0x5C lane
 * is read through the union so it stays a plain lfs (doc 06). */
typedef union {
    __ps_t p;
    struct { f32 hi; f32 lo; } f;
} PSV;

typedef struct {
    char pad0x0[0x58];
    PSV u58;
    PSV u60;
} POS;

bool fn_8018EA28(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 spC;
    POS *a;
    POS *b;
    __ps_t n12;
    __ps_t o13;
    __ps_t q10;
    __ps_t p0;
    __ps_t k11;
    __ps_t dxy;
    __ps_t sq;
    __ps_t dzp;
    __ps_t mg;
    __ps_t acc;
    PSV u;
    f32 dyy;
    f32 d2;
    f32 sqf;
    f32 t;
    f32 dist;
    register f32 ay __asm__("fr12");
    s32 tot;
    s32 feet;
    s32 inches;

    GetChecksum_2((CStruct *)arg0->unk0x20, QB_DISTANCE_RECORD_OBJECT, &sp8, 1);
    a = (POS *)fn_800A398C(*(s32 *)&lbl_80301A38, sp8);
    b = (POS *)fn_801745B4(*(s32 *)&lbl_80305EAC);
    /* `goto block_5` (not two inline `return 0`s) so all three fail paths share
     * the single `li r3,0` block at the tail — 79.2% -> 95.0%. */
    if (b == NULL) {
        goto block_5;
    }
    if (a == NULL) {
        goto block_5;
    }
    n12 = a->u58.p;
    o13 = b->u58.p;
    q10 = b->u60.p;
    p0 = a->u60.p;
    k11 = lbl_802A95D8;
    dxy = __builtin_ps_sub(o13, n12);
    sq = __builtin_ps_mul(dxy, dxy);
    dzp = __builtin_ps_sub(q10, p0);
    mg = __builtin_ps_merge00(dzp, k11);
    acc = __builtin_ps_madds0(mg, mg, sq);
    u.p = __builtin_ps_sum0(acc, acc, acc);
    /* sqf is reloaded from the 0x10(r1) pair slot into f0 and copied, so it has
     * to be its own named local (`t = u.f.hi - d2` loses the fmr entirely). */
    ay = a->u58.f.lo;
    dyy = b->u58.f.lo - ay;
    sqf = u.f.hi;
    d2 = dyy * dyy;
    t = sqf - d2;
    dist = sqrtf(t);
    /* both feet and inches are computed BEFORE either AddInteger so the
     * lis/ori 0x2AAAAAAB magic lands where the want has it. */
    feet = (s32)(dist / lbl_802A9658);
    inches = (s32)dist % 12;
    tot = (s32)dist;
    AddInteger((CStruct *)arg0->unk0x20, QB_CURRENT_DISTANCE_FEET, feet);
    AddInteger((CStruct *)arg0->unk0x20, QB_CURRENT_DISTANCE_INCHES, inches);
    spC = 0;
    GetInteger((CStruct *)arg0->unk0x20, QB_MINIGAME_RECORD, &spC, 0);
    if (dist > (f32)spC) {
        AddInteger((CStruct *)arg0->unk0x20, QB_MINIGAME_RECORD, tot);
        AddInteger((CStruct *)arg0->unk0x20, QB_RECORD_FEET, feet);
        AddInteger((CStruct *)arg0->unk0x20, QB_RECORD_INCHES, inches);
        return true;
    }
    goto block_5;
block_5:
    return false;
}
