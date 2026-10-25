// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006AC08-0x8006AF2C (804B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
#include "dolphin/SN_PS.h"

extern const f32 lbl_80294AD4; /* 0.0f   */
extern const f32 lbl_80294AD8; /* 60.0f  */
extern const f32 lbl_80294ADC; /* 1.0f   */
extern f32 lbl_80294AE0;       /* pi     */
extern f32 lbl_80294AE4;       /* 180.0f */
extern f32 lbl_80294AE8;       /* 100000.0f */
extern f32 lbl_80294AEC;       /* 15000.0f  */
extern __ps_t lbl_80294A90;    /* { 0.0f, 0.0f } */
extern s32 lbl_80366478;

/* the two pairs at +0x78 / +0xB0 are initialised as scalars but consumed as
 * paired singles by the normalise block, so they need both views */
typedef union {
    struct { f32 x, y, z, w; } f;
    __ps_t ps[2];
} Vec4;

typedef struct {
    char pad0x00[0x1C];
    s32 unk0x1C;        /* fn_8005CF80(globals, QB_TEXTURE checksum) */
    s32 unk0x20;        /* QB_BlendMode checksum */
    char pad0x24[0x44];
    f32 unk0x68;        /* size */
    f32 unk0x6C;        /* fov */
    f32 unk0x70;        /* aspect */
    s32 unk0x74;        /* subdrecursiondepth */
    Vec4 unk0x78;       /* proj_dir, normalised in place */
    Vec4 unk0x88;       /* copy of the normalised proj_dir */
    char pad0x98[0x10];
    f32 unk0xA8;        /* max_range */
    s32 unk0xAC;        /* lock_bone checksum */
    Vec4 unk0xB0;       /* offset */
    f32 unk0xC0;        /* Angle, converted to radians */
    f32 unk0xC4;        /* lod_dist */
    f32 unk0xC8;        /* suspend_dist */
    s32 unk0xCC;        /* flag bits: 1=enabled 2=has size 4=has fov */
} S_AC08;

s32 GetVector(CStruct *, s32, void *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, void *, s32);
s32 fn_8005CF80(s32, s32);
void fn_8006AF2C(S_AC08 *);

void fn_8006AC08(S_AC08 *arg0, CStruct *arg1) {
    f32 zero;
    f32 sixty;
    f32 one;
    SN_PS_type s;
    __ps_t d;
    __ps_t p1;
    __ps_t p0;
    __ps_t q;
    s32 sp8;
    s32 spC;
    s32 sp10;
    Vec4 *v;
    Vec4 *w;

    zero = lbl_80294AD4;
    sixty = lbl_80294AD8;
    one = lbl_80294ADC;

    arg0->unk0x68 = zero;
    arg0->unk0x6C = sixty;
    arg0->unk0x70 = one;
    v = &arg0->unk0x78;
    v->f.x = zero;
    v->f.y = zero;
    v->f.z = zero;
    v->f.w = one;
    GetVector(arg1, QB_PROJ_DIR, v, 1);

    /* len2 = |proj_dir|^2 ; if it is non-zero scale xy,z by 1/sqrt(len2) and
     * leave w (pair lane 1 of ps[1]) at 1.0f.  fn_8006AF2C consumes the
     * normalised copy at +0x88. */
    p1 = v->ps[1];
    p0 = v->ps[0];
    d = __builtin_ps_mul(p1, p1);
    d = __builtin_ps_merge00(d, lbl_80294A90);
    d = __builtin_ps_madd(p0, p0, d);
    d = __builtin_ps_sum0(d, d, d);
    s.ps = d;
    if (s.flt.hi > zero) {
        d = __builtin_ps_rsqrte(d);
        s.ps = d;
        s.flt.lo = one;
        q = s.ps;
        v->ps[0] = __builtin_ps_muls0(p0, d);
        v->ps[1] = __builtin_ps_mul(p1, q);
    }
    arg0->unk0x88.ps[0] = v->ps[0];
    arg0->unk0x88.ps[1] = v->ps[1];

    arg0->unk0xA8 = zero;
    GetFloat(arg1, QB_MAX_RANGE, &arg0->unk0xA8, 1);

    if (GetFloat(arg1, QB_SIZE, &arg0->unk0x68, 0)) {
        arg0->unk0xCC = (arg0->unk0xCC & ~4) | 2;
    } else if (GetFloat(arg1, QB_FOV, &arg0->unk0x6C, 0)) {
        GetFloat(arg1, QB_ASPECT, &arg0->unk0x70, 0);
        arg0->unk0xCC = (arg0->unk0xCC | 4) & ~2;
    }

    arg0->unk0xAC = 0;
    GetChecksum_2(arg1, QB_LOCK_BONE, &arg0->unk0xAC, 0);

    w = &arg0->unk0xB0;
    w->f.x = lbl_80294AD4;
    w->f.y = lbl_80294AD4;
    w->f.z = lbl_80294AD4;
    w->f.w = lbl_80294ADC;
    GetVector(arg1, QB_OFFSET, w, 0);

    arg0->unk0xC0 = lbl_80294AD4;
    GetFloat(arg1, QB_ANGLE, &arg0->unk0xC0, 0);

    sp8 = 0;
    arg0->unk0xC0 = arg0->unk0xC0 * lbl_80294AE0 / lbl_80294AE4;
    GetChecksum_2(arg1, QB_TEXTURE, &sp8, 1);

    arg0->unk0x20 = QB_BLEND;
    GetChecksum_2(arg1, QB_BLENDMODE, &arg0->unk0x20, 0);

    spC = 0;
    GetInteger(arg1, QB_SUBDRECURSIONDEPTH, &spC, 0);
    arg0->unk0x74 = spC;
    arg0->unk0x1C = fn_8005CF80(lbl_80366478, sp8);

    sp10 = 0;
    GetInteger(arg1, QB_ENABLED, &sp10, 0);
    if (sp10 != 0) {
        arg0->unk0xCC |= 1;
    } else {
        arg0->unk0xCC &= ~1;
    }

    arg0->unk0xC4 = lbl_80294AE8;
    GetFloat(arg1, QB_LOD_DIST, &arg0->unk0xC4, 0);
    arg0->unk0xC8 = lbl_80294AEC;
    GetFloat(arg1, QB_SUSPEND_DIST, &arg0->unk0xC8, 0);
    fn_8006AF2C(arg0);
}
