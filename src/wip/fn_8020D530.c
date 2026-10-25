// WIP DRAFT (non-matching) — SNAPS-intrinsic reconstruction (2026-08)
// PARKED 16.3% (-mps-float): retry 2026-08-25 with product-array staging
// (__ps_t pr[2] through which both muls0 results flow) -> +3.5% only. Want's
// integrator block additionally (a) splats via pair(arg0+0x40).hi NOT a scalar
// (muls0 by m[3]), tried, regressed; (b) keeps a DEAD sp20 store of arg0->0x88
// across bl fn_8020F1D4 plus a DEAD psq_l f11,32(r1) before its reload — both
// are want-extra dead ops in the S6x-89 GCC-always-removes class; (c) spills
// products to r1+8/r1+16 with base r28=&sp8 and reloads ONE — array staging
// alone doesn't reproduce the spill+partial-reload scheduling. Frame still
// 0x30 vs want 0x48.
// family=m2c range=0x8020D530-0x8020D764 size=564B
// RECONSTRUCTED with __builtin_ps_* (SNAPS) intrinsics: the two idiom blocks
// now emit the exact ps_muls0 / ps_merge00 / ps_sum0 opcodes the game uses
// (previously the __ps_t arithmetic fused into ps_madd/ps_mul). Compiles to
// 536B vs the 564B WANT; the sole remaining gap is scheduler/register-alloc:
// the game spills the two products to a stack pair slot (sp8/sp16 + a base
// pointer) and reloads one, while ProDG 3.9.3 keeps both in registers. See
// docs/parkings/06-paired-single-ops.md (M5.0h) + docs/plan-snaps-doc06.md.
// NOTE: uses the compiler's builtin __ps_t + SN_PS_type union (== sn_ps);
// the in-tree SN_PS.h is redundant for 3.9.3 (its SN_PS_type typedef just
// restates the builtin, and its ps_* macros alias __builtin_ps_*).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
extern char lbl_802AF450[];
extern f32 lbl_802AF4E0;
extern f32 lbl_802AF4E4;
extern f32 lbl_802AF4E8;
extern s32 lbl_80302BD8;
// FLAG: -mps-float
#include "qb_constants.h"
#include "structs.h"

void fn_8020F938(Unk_830733AE *);
void fn_80213E48(Unk_C7387A53 *);
void fn_8020D764(Unk_E8083225 *, CStruct *);
void GetStructure(s32, s32);
void GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_8020E014(void *);
void fn_8020ED80(Unk_C7387A53 *);
void fn_8020F1D4(Unk_3CB21567 *);
void fn_8020F5F8(Unk_BAF2D600 *);
s32 fn_800EB8F8(s32 *, CStruct *, s32 *);
f32 sqrtf(s32);
void fn_801ED360(Unk_56FA3D0E *);

void fn_8020D530(Unk_7497A58C *arg0) {
    f32 sp18;
    f32 sp20;
    f32 sp30;
    SN_PS_type dot;
    s32 temp_r30;
    s32 temp_r3;
    Unk_073F5245 *temp_r3_2;

    fn_8020F938(arg0);
    fn_80213E48(arg0);
    fn_8020D764(arg0, (char *)arg0 + 0x38);
    if (arg0->unk0x80 == QB_SKID) {
        GetStructure(QB_WALK_PARAMETERS, 0);
        GetFloat(QB_WALK_PARAMETERS, QB_PEGGED_DURATION_FOR_SKID, &sp18, 1);
        if (arg0->unk0x194C < sp18) {
            arg0->unk0x80 = QB_STAND;
        }
    }
    temp_r3 = fn_8020E014(arg0);
    if (temp_r3 != 0) {
        fn_8020ED80(arg0);
    } else {
        arg0->unk0x1948 = temp_r3;
    }
    arg0->unk0x1A3C = 0;
    if (arg0->unk0x1C != 0
        || (temp_r30 = *(s32 *)(arg0->unk0x184C + 0x30), temp_r30 != 0)) {
        lbl_80302BD8 = 0;
        return;
    }
    sp20 = arg0->unk0x88;
    {
        __ps_t *m = (__ps_t *)((char *)arg0 + 0x28);
        __ps_t pr[2];
        __ps_t s = *(__ps_t *)&sp20;
        pr[0] = __builtin_ps_muls0(m[2], s);
        pr[1] = __builtin_ps_muls0(m[3], s);
        m[0] = __builtin_ps_add(m[0], pr[0]);
        m[1] = __builtin_ps_add(m[1], pr[1]);
    }
    fn_8020F1D4(arg0);
    if (arg0->unk0x1C != 0
        || *(s32 *)(arg0->unk0x184C + 0x30) != 0) {
        lbl_80302BD8 = temp_r30;
        return;
    }
    fn_8020F5F8(arg0);
    temp_r3_2 = fn_800EB8F8(arg0->unk0x1850, (char *)arg0 + 0x28, (char *)arg0 + 0x70);
    if (temp_r3_2 != 0) {
        __ps_t *v = (__ps_t *)((char *)arg0 + 0x38);
        v[0] = temp_r3_2->unk0xB8;
        v[1] = temp_r3_2->unk0xC0;
        arg0->unk0x48 = lbl_802AF4E0;
        arg0->unk0x3C = lbl_802AF4E0;
        {
            __ps_t zz = __builtin_ps_mul(v[1], v[1]);
            zz = __builtin_ps_merge00(zz, *(__ps_t *)&lbl_802AF450);
            dot.ps = __builtin_ps_madd(v[0], v[0], zz);
            dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        }
        if (dot.flt.hi > lbl_802AF4E4) {
            sp30 = lbl_802AF4E8 / sqrtf(temp_r3_2);
            {
                __ps_t *dst = (__ps_t *)((char *)arg0 + 0x50);
                __ps_t s = *(__ps_t *)&sp30;
                dst[0] = __builtin_ps_muls0(v[0], s);
                dst[1] = __builtin_ps_muls0(v[1], s);
            }
        }
    }
    fn_801ED360(arg0->unk0x1858);
    lbl_80302BD8 = 0;
}
