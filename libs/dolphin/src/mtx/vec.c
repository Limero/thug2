#include <dolphin/dolphin.h>
#include <dolphin/mtx.h>
#include <sdk_math.h>

// Constants externed to auto-asm (extern route, docs/dolphin-sdk.md s9.17).

extern const f32 lbl_803CB06C; // 0.5f
extern const f32 lbl_803CB070; // 3.0f




asm void PSVECAdd(const __REGISTER Vec* a, const __REGISTER Vec* b, __REGISTER Vec* ab) {
    psq_l f2, Vec.x(a), 0, 0
    psq_l f4, Vec.x(b), 0, 0
    ps_add f6, f2, f4
    psq_st f6, Vec.x(ab), 0, 0
    psq_l f3, Vec.z(a), 1, 0
    psq_l f5, Vec.z(b), 1, 0
    ps_add f7, f3, f5
    psq_st f7, Vec.z(ab), 1, 0
}



void PSVECScale(const __REGISTER Vec* src, __REGISTER Vec* dst, __REGISTER f32 scale) {
    __REGISTER f32 vxy, vz, rxy, rz;

    asm {
        psq_l vxy, 0x0(src), 0, 0
        psq_l vz, 0x8(src), 1, 0
        ps_muls0 rxy, vxy, scale
        psq_st rxy, 0x0(dst), 0, 0
        ps_muls0 rz, vz, scale
        psq_st rz, 0x8(dst), 1, 0
    }
}



void PSVECNormalize(const __REGISTER Vec* src, __REGISTER Vec* unit) {
    __REGISTER float c_half = lbl_803CB06C;
    __REGISTER float c_three = lbl_803CB070;
    __REGISTER float v1_xy;
    __REGISTER float v1_z;
    __REGISTER float xx_zz;
    __REGISTER float xx_yy;
    __REGISTER float sqsum;
    __REGISTER float rsqrt;
    __REGISTER float nwork0;
    __REGISTER float nwork1;

    asm {
        psq_l v1_xy, 0x0(src), 0, 0
        ps_mul xx_yy, v1_xy, v1_xy
        psq_l v1_z, 0x8(src), 1, 0
        ps_madd xx_zz, v1_z, v1_z, xx_yy
        ps_sum0 sqsum, xx_zz, v1_z, xx_yy
        frsqrte rsqrt, sqsum
        fmuls nwork0, rsqrt, rsqrt
        fmuls nwork1, rsqrt, c_half
        fnmsubs nwork0, nwork0, sqsum, c_three
        fmuls rsqrt, nwork0, nwork1
        ps_muls0 v1_xy, v1_xy, rsqrt
        psq_st v1_xy, 0x0(unit), 0, 0
        ps_muls0 v1_z, v1_z, rsqrt
        psq_st v1_z, 0x8(unit), 1, 0
    }
}



f32 PSVECMag(const __REGISTER Vec* v) {
    __REGISTER f32 vxy, vzz;
    __REGISTER f32 sqmag, rmag;
    __REGISTER f32 nwork0, nwork1;
    __REGISTER f32 c_three, c_half, c_zero;

    c_half = lbl_803CB06C;

    asm {
        psq_l vxy, 0x0(v), 0, 0
        ps_mul vxy, vxy, vxy
        lfs vzz, 0x8(v)
        fsubs c_zero, c_half, c_half
        ps_madd sqmag, vzz, vzz, vxy
        ps_sum0 sqmag, sqmag, vxy, vxy
        fcmpu cr0, sqmag, c_zero
        beq L_000005F0
        frsqrte rmag, sqmag
    }

    c_three = lbl_803CB070;

    asm {
        fmuls nwork0, rmag, rmag
        fmuls nwork1, rmag, c_half
        fnmsubs nwork0, nwork0, sqmag, c_three
        fmuls rmag, nwork0, nwork1
        fmuls sqmag, sqmag, rmag
    L_000005F0:
    }

    return sqmag;
}



asm void PSVECCrossProduct(const __REGISTER Vec* a, const __REGISTER Vec* b, __REGISTER Vec* axb) {
    psq_l f1, Vec.x(b), 0, 0
    lfs f2, Vec.z(a)
    psq_l f0, Vec.x(a), 0, 0
    ps_merge10 f6, f1, f1
    lfs f3, Vec.z(b)
    ps_mul f4, f1, f2
    ps_muls0 f7, f1, f0
    ps_msub f5, f0, f3, f4
    ps_msub f8, f0, f6, f7
    ps_merge11 f9, f5, f5
    ps_merge01 f10, f5, f8
    psq_st f9, Vec.x(axb), 1, 0
    ps_neg f10, f10
    psq_st f10, Vec.y(axb), 0, 0
}





