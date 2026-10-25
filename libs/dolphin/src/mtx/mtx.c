#include <dolphin/dolphin.h>
#include <dolphin/mtx.h>
#include <sdk_math.h>

// mtx constants are externed to auto-asm (extern route, docs/dolphin-sdk.md
// s8.9 + s9.17): retail's .sdata2 pool carries dead-function constants a
// fresh compile cannot reproduce, so the C objects emit no .sdata2 of their
// own and reference the auto pool at its retail addresses.
extern f32 lbl_803CA360[2];     // Unit01 = {0.0f, 1.0f}
extern const f32 lbl_803CAFB0;  // 1.0f
extern const f32 lbl_803CAFB4;  // 0.0f
extern const f32 lbl_803CAFC0;  // 2.0f




void PSMTXIdentity(__REGISTER Mtx m) {
    __REGISTER f32 c_zero = lbl_803CAFB4;
    __REGISTER f32 c_one = lbl_803CAFB0;
    __REGISTER f32 c_01;
    __REGISTER f32 c_10;

    asm {
        psq_st c_zero, 8(m), 0, 0
        ps_merge01 c_01, c_zero, c_one
        psq_st c_zero, 24(m), 0, 0
        ps_merge10 c_10, c_one, c_zero
        psq_st c_zero, 32(m), 0, 0
        psq_st c_01, 16(m), 0, 0
        psq_st c_10, 0(m), 0, 0
        psq_st c_10, 40(m), 0, 0
    }
}


asm void PSMTXCopy(const __REGISTER Mtx src, __REGISTER Mtx dst) {
    psq_l f0, 0(src), 0, 0
    psq_st f0, 0(dst), 0, 0
    psq_l f1, 8(src), 0, 0
    psq_st f1, 8(dst), 0, 0
    psq_l f2, 16(src), 0, 0
    psq_st f2, 16(dst), 0, 0
    psq_l f3, 24(src), 0, 0
    psq_st f3, 24(dst), 0, 0
    psq_l f4, 32(src), 0, 0
    psq_st f4, 32(dst), 0, 0
    psq_l f5, 40(src), 0, 0
    psq_st f5, 40(dst), 0, 0
}


asm void PSMTXConcat(const __REGISTER Mtx a, const __REGISTER Mtx b, __REGISTER Mtx ab) {
    nofralloc
    stwu r1, -64(r1)
    psq_l f0, 0(a), 0, 0
    stfd f14, 8(r1)
    psq_l f6, 0(b), 0, 0
    lis r6, lbl_803CA360@ha
    psq_l f7, 8(b), 0, 0
    stfd f15, 16(r1)
    addi r6, r6, lbl_803CA360@l
    stfd f31, 40(r1)
    psq_l f8, 16(b), 0, 0
    ps_muls0 f12, f6, f0
    psq_l f2, 16(a), 0, 0
    ps_muls0 f13, f7, f0
    psq_l f31, 0(r6), 0, 0
    ps_muls0 f14, f6, f2
    psq_l f9, 24(b), 0, 0
    ps_muls0 f15, f7, f2
    psq_l f1, 8(a), 0, 0
    ps_madds1 f12, f8, f0, f12
    psq_l f3, 24(a), 0, 0
    ps_madds1 f14, f8, f2, f14
    psq_l f10, 32(b), 0, 0
    ps_madds1 f13, f9, f0, f13
    psq_l f11, 40(b), 0, 0
    ps_madds1 f15, f9, f2, f15
    psq_l f4, 32(a), 0, 0
    psq_l f5, 40(a), 0, 0
    ps_madds0 f12, f10, f1, f12
    ps_madds0 f13, f11, f1, f13
    ps_madds0 f14, f10, f3, f14
    ps_madds0 f15, f11, f3, f15
    psq_st f12, 0(ab), 0, 0
    ps_muls0 f2, f6, f4
    ps_madds1 f13, f31, f1, f13
    ps_muls0 f0, f7, f4
    psq_st f14, 16(ab), 0, 0
    ps_madds1 f15, f31, f3, f15
    psq_st f13, 8(ab), 0, 0
    ps_madds1 f2, f8, f4, f2
    ps_madds1 f0, f9, f4, f0
    ps_madds0 f2, f10, f5, f2
    lfd f14, 8(r1)
    psq_st f15, 24(ab), 0, 0
    ps_madds0 f0, f11, f5, f0
    psq_st f2, 32(ab), 0, 0
    ps_madds1 f0, f31, f5, f0
    lfd f15, 16(r1)
    psq_st f0, 40(ab), 0, 0
    lfd f31, 40(r1)
    addi r1, r1, 64
    blr
}


asm u32 PSMTXInverse(const __REGISTER Mtx src, __REGISTER Mtx inv) {
    psq_l f0, 0(src), 1, 0
    psq_l f1, 4(src), 0, 0
    psq_l f2, 16(src), 1, 0
    ps_merge10 f6, f1, f0
    psq_l f3, 20(src), 0, 0
    psq_l f4, 32(src), 1, 0
    ps_merge10 f7, f3, f2
    psq_l f5, 36(src), 0, 0
    ps_mul f11, f3, f6
    ps_mul f13, f5, f7
    ps_merge10 f8, f5, f4
    ps_msub f11, f1, f7, f11
    ps_mul f12, f1, f8
    ps_msub f13, f3, f8, f13
    ps_mul f10, f3, f4
    ps_msub f12, f5, f6, f12
    ps_mul f9, f0, f5
    ps_mul f8, f1, f2
    ps_sub f6, f6, f6
    ps_msub f10, f2, f5, f10
    ps_mul f7, f0, f13
    ps_msub f9, f1, f4, f9
    ps_madd f7, f2, f12, f7
    ps_msub f8, f0, f3, f8
    ps_madd f7, f4, f11, f7
    ps_cmpo0 cr0, f7, f6
    bne skip_return
    li r3, 0
    blr
skip_return:
    fres f0, f7
    ps_add f6, f0, f0
    ps_mul f5, f0, f0
    ps_nmsub f0, f7, f5, f6
    lfs f1, 12(src)
    ps_muls0 f13, f13, f0
    lfs f2, 28(src)
    ps_muls0 f12, f12, f0
    lfs f3, 44(src)
    ps_muls0 f11, f11, f0
    ps_merge00 f5, f13, f12
    ps_muls0 f10, f10, f0
    ps_merge11 f4, f13, f12
    ps_muls0 f9, f9, f0
    psq_st f5, 0(inv), 0, 0
    ps_mul f6, f13, f1
    psq_st f4, 16(inv), 0, 0
    ps_muls0 f8, f8, f0
    ps_madd f6, f12, f2, f6
    psq_st f10, 32(inv), 1, 0
    ps_nmadd f6, f11, f3, f6
    psq_st f9, 36(inv), 1, 0
    ps_mul f7, f10, f1
    ps_merge00 f5, f11, f6
    psq_st f8, 40(inv), 1, 0
    ps_merge11 f4, f11, f6
    psq_st f5, 8(inv), 0, 0
    ps_madd f7, f9, f2, f7
    psq_st f4, 24(inv), 0, 0
    ps_nmadd f7, f8, f3, f7
    li r3, 1
    psq_st f7, 44(inv), 1, 0
}


asm u32 PSMTXInvXpose(const __REGISTER Mtx src, __REGISTER Mtx invX) {
	psq_l f0, 0(src), 1, 0
	psq_l f1, 4(src), 0, 0
	psq_l f2, 16(src), 1, 0
	ps_merge10 f6, f1, f0
	psq_l f3, 20(src), 0, 0
	psq_l f4, 32(src), 1, 0
	ps_merge10 f7, f3, f2
	psq_l f5, 36(src), 0, 0
	ps_mul f11, f3, f6
	ps_merge10 f8, f5, f4
	ps_mul f13, f5, f7
	ps_msub f11, f1, f7, f11
	ps_mul f12, f1, f8
	ps_msub f13, f3, f8, f13
	ps_msub f12, f5, f6, f12
	ps_mul f10, f3, f4
	ps_mul f9, f0, f5
	ps_mul f8, f1, f2
	ps_msub f10, f2, f5, f10
	ps_msub f9, f1, f4, f9
	ps_msub f8, f0, f3, f8
	ps_mul f7, f0, f13
	ps_sub f1, f1, f1
	ps_madd f7, f2, f12, f7
	ps_madd f7, f4, f11, f7
	ps_cmpo0 cr0, f7, f1
	bne skip_return
	li r3, 0
	blr
skip_return:
	fres f0, f7
	psq_st f1, 12(invX), 1, 0
	ps_add f6, f0, f0
	ps_mul f5, f0, f0
	psq_st f1, 28(invX), 1, 0
	ps_nmsub f0, f7, f5, f6
	psq_st f1, 44(invX), 1, 0
	ps_muls0 f13, f13, f0
	ps_muls0 f12, f12, f0
	ps_muls0 f11, f11, f0
    psq_st f13, 0(invX), 0, 0
	psq_st f12, 16(invX), 0, 0
	ps_muls0 f10, f10, f0
    ps_muls0 f9, f9, f0
	psq_st f11, 32(invX), 0, 0
	psq_st f10, 8(invX), 1, 0
	ps_muls0 f8, f8, f0
	li r3, 1
    psq_st f9, 24(invX), 1, 0
	psq_st f8, 40(invX), 1, 0
}


void PSMTXRotRad(Mtx m, char axis, f32 rad) {
    f32 sinA, cosA;
    sinA = sinf(rad);
    cosA = cosf(rad);
    PSMTXRotTrig(m, axis, sinA, cosA);
}


void PSMTXRotTrig(__REGISTER Mtx m, __REGISTER char axis, __REGISTER f32 sinA, __REGISTER f32 cosA) {
    __REGISTER f32 fc0, fc1, nsinA;
    __REGISTER f32 fw0, fw1, fw2, fw3;

	asm {
		frsp        sinA, sinA
		frsp        cosA, cosA
	}

    fc0 = lbl_803CAFB4;
    fc1 = lbl_803CAFB0;

	asm {
		ori         axis, axis, 0x20
		ps_neg      nsinA, sinA
		cmplwi      axis, 'x'
		beq         _case_x
		cmplwi      axis, 'y'
		beq         _case_y
		cmplwi      axis, 'z'
		beq         _case_z
		b           _end

	_case_x:
		psq_st      fc1,  0(m), 1, 0
		psq_st      fc0,  4(m), 0, 0
		ps_merge00  fw0, sinA, cosA
		psq_st      fc0, 12(m), 0, 0
		ps_merge00  fw1, cosA, nsinA
		psq_st      fc0, 28(m), 0, 0
		psq_st      fc0, 44(m), 1, 0
		psq_st      fw0, 36(m), 0, 0
		psq_st      fw1, 20(m), 0, 0
		b           _end;

	_case_y:
		ps_merge00  fw0, cosA, fc0
		ps_merge00  fw1, fc0, fc1
		psq_st      fc0, 24(m), 0, 0
		psq_st      fw0,  0(m), 0, 0
		ps_merge00  fw2, nsinA, fc0
		ps_merge00  fw3, sinA, fc0
		psq_st      fw0, 40(m), 0, 0;
		psq_st      fw1, 16(m), 0, 0;
		psq_st      fw3,  8(m), 0, 0;
		psq_st      fw2, 32(m), 0, 0;
		b           _end;

	_case_z:
		psq_st      fc0,  8(m), 0, 0
		ps_merge00  fw0, sinA, cosA
		ps_merge00  fw2, cosA, nsinA
		psq_st      fc0, 24(m), 0, 0
		psq_st      fc0, 32(m), 0, 0
		ps_merge00  fw1, fc1, fc0
		psq_st      fw0, 16(m), 0, 0
		psq_st      fw2,  0(m), 0, 0
		psq_st      fw1, 40(m), 0, 0

	_end:
	}
}


void PSMTXTrans(__REGISTER Mtx m, __REGISTER f32 xT, __REGISTER f32 yT, __REGISTER f32 zT) {
    __REGISTER f32 c0 = lbl_803CAFB4;
    __REGISTER f32 c1 = lbl_803CAFB0;

	asm {
		stfs xT, 12(m)
		stfs yT, 28(m)
		psq_st c0, 4(m), 0, 0
		psq_st c0, 32(m), 0, 0
		stfs c0, 16(m)
		stfs c1, 20(m)
		stfs c0, 24(m)
		stfs c1, 40(m)
		stfs zT, 44(m)
		stfs c1, 0(m)
	}
}


void PSMTXScale(__REGISTER Mtx m, __REGISTER f32 xS, __REGISTER f32 yS, __REGISTER f32 zS) {
    __REGISTER f32 c0 = lbl_803CAFB4;

	asm {
		stfs xS, 0(m)
		psq_st c0, 4(m), 0, 0
		psq_st c0, 12(m), 0, 0
		stfs yS, 20(m)
		psq_st c0, 24(m), 0, 0
		psq_st c0, 32(m), 0, 0
		stfs zS, 40(m)
		stfs c0, 44(m)
	}
}


void PSMTXQuat(__REGISTER Mtx m, const __REGISTER Quaternion* q) {
    __REGISTER f32 c_zero, c_one, c_two, scale;
    __REGISTER f32 tmp0, tmp1, tmp2, tmp3, tmp4;
    __REGISTER f32 tmp5, tmp6, tmp7, tmp8, tmp9;
    c_one = lbl_803CAFB0;

	asm {
        psq_l tmp0, 0(q), 0, 0
        psq_l tmp1, 8(q), 0, 0
        fsubs c_zero, c_one, c_one
        fadds c_two, c_one, c_one
        ps_mul tmp2, tmp0, tmp0
        ps_merge10 tmp5, tmp0, tmp0
        ps_madd tmp4, tmp1, tmp1, tmp2
        ps_mul tmp3, tmp1, tmp1
        ps_sum0 scale, tmp4, tmp4, tmp4
        ps_muls1 tmp7, tmp5, tmp1
        fres tmp9, scale
        ps_sum1 tmp4, tmp3, tmp4, tmp2
        ps_nmsub scale, scale, tmp9, c_two
        ps_muls1 tmp6, tmp1, tmp1
        ps_mul scale, tmp9, scale
        ps_sum0 tmp2, tmp2, tmp2, tmp2
        fmuls scale, scale, c_two
        ps_madd tmp8, tmp0, tmp5, tmp6
        ps_msub tmp6, tmp0, tmp5, tmp6
        psq_st c_zero, 12(m), 1, 0
        ps_nmsub tmp2, tmp2, scale, c_one
        ps_nmsub tmp4, tmp4, scale, c_one
        psq_st c_zero, 44(m), 1, 0
        ps_mul tmp8, tmp8, scale
        ps_mul tmp6, tmp6, scale
        psq_st tmp2, 40(m), 1, 0
        ps_madds0 tmp5, tmp0, tmp1, tmp7
        ps_merge00 tmp1, tmp8, tmp4
        ps_nmsub tmp7, tmp7, c_two, tmp5
        ps_merge10 tmp0, tmp4, tmp6
        psq_st tmp1, 16(m), 0, 0
        ps_mul tmp5, tmp5, scale
        ps_mul tmp7, tmp7, scale
        psq_st tmp0, 0(m), 0, 0
        psq_st tmp5, 8(m), 1, 0
        ps_merge10 tmp3, tmp7, c_zero
        ps_merge01 tmp9, tmp7, tmp5
        psq_st tmp3, 24(m), 0, 0
        psq_st tmp9, 32(m), 0, 0
	}
}


void C_MTXLookAt(Mtx m, const Point3d* camPos, const Vec* camUp, const Point3d* target) {
    Vec vLook;
    Vec vRight;
    Vec vUp;

    ASSERTMSGLINE(2438, m, "MTXLookAt():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(2439, camPos, "MTXLookAt():  NULL VecPtr 'camPos' ");
    ASSERTMSGLINE(2440, camUp, "MTXLookAt():  NULL VecPtr 'camUp' ");
    ASSERTMSGLINE(2441, target, "MTXLookAt():  NULL Point3dPtr 'target' ");

    vLook.x = camPos->x - target->x;
    vLook.y = camPos->y - target->y;
    vLook.z = camPos->z - target->z;
    VECNormalize(&vLook, &vLook);
    VECCrossProduct(camUp, &vLook, &vRight);
    VECNormalize(&vRight, &vRight);
    VECCrossProduct(&vLook, &vRight, &vUp);
    m[0][0] = vRight.x;
    m[0][1] = vRight.y;
    m[0][2] = vRight.z;
    m[0][3] = -((camPos->z * vRight.z) + ((camPos->x * vRight.x) + (camPos->y * vRight.y)));
    m[1][0] = vUp.x;
    m[1][1] = vUp.y;
    m[1][2] = vUp.z;
    m[1][3] = -((camPos->z * vUp.z) + ((camPos->x * vUp.x) + (camPos->y * vUp.y)));
    m[2][0] = vLook.x;
    m[2][1] = vLook.y;
    m[2][2] = vLook.z;
    m[2][3] = -((camPos->z * vLook.z) + ((camPos->x * vLook.x) + (camPos->y * vLook.y)));
}


// The SDK original is an inline-asm body (proven by SFA-Decomp
// src/dolphin/mtx/mtx.c:480-517, instruction-identical); no C form reproduces
// retail. Labels swapped to thug2's extern pool: lbl_803CAFB0 = 1.0f,
// lbl_803CAFC0 = 2.0f, lbl_803CAFB4 = 0.0f.
asm void C_MTXLightOrtho(__REGISTER Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS, f32 transT) {
    nofralloc
    fsubs f10, f4, f3
    lfs f11, lbl_803CAFB0(r2)
    fsubs f0, f1, f2
    lfs f9, lbl_803CAFC0(r2)
    fadds f3, f4, f3
    fdivs f12, f11, f10
    fdivs f10, f11, f0
    fmuls f4, f9, f12
    fneg f3, f3
    fadds f0, f1, f2
    fmuls f1, f4, f5
    fmuls f2, f12, f3
    fneg f0, f0
    stfs f1, 0(m)
    fmuls f1, f9, f10
    fmuls f2, f5, f2
    lfs f3, lbl_803CAFB4(r2)
    fmuls f0, f10, f0
    stfs f3, 4(m)
    fadds f2, f7, f2
    fmuls f1, f1, f6
    stfs f3, 8(m)
    fmuls f0, f6, f0
    stfs f2, 0xc(m)
    stfs f3, 0x10(m)
    fadds f0, f8, f0
    stfs f1, 0x14(m)
    stfs f3, 0x18(m)
    stfs f0, 0x1c(m)
    stfs f3, 0x20(m)
    stfs f3, 0x24(m)
    stfs f3, 0x28(m)
    stfs f11, 0x2c(m)
    blr
}
