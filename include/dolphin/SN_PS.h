// Paired-single support for the ProDG (GCC fork) GameCube toolchain.

#ifndef __SN_PS_H
#define __SN_PS_H

// 64-bit paired-single vector type (two f32 lanes).
typedef float sn_ps __attribute__((mode(PS)));

// A paired-single value viewed as lanes. Declares the union tag only,
// mirroring the compiler's own built-in shape (no typedef name).
typedef union SN_PS_type {
    sn_ps ps;
    struct tflt {
        float hi, lo;
#ifndef __cplusplus
    } flt;
#else
    };
    tflt flt;
#endif
};

// Graphics quantization registers (SPRs) and their scale/type codes.
#define GQR0 912
#define GQR1 913
#define GQR2 914
#define GQR3 915
#define GQR4 916
#define GQR5 917
#define GQR6 918
#define GQR7 919

#define GQR_SCALE_F32 0x0
#define GQR_SCALE_U8  0x4
#define GQR_SCALE_U16 0x5
#define GQR_SCALE_S8  0x6
#define GQR_SCALE_S16 0x7

// Pack two scalars into a paired-single value.
#define PS_BUILD(hi, lo) *(sn_ps *)(float[]){(lo), (hi)}

// Unary paired-single ops.
#define ps_neg(x)    __builtin_ps_neg(x)
#define ps_abs(x)    __builtin_ps_abs(x)
#define ps_nabs(x)   __builtin_ps_nabs(x)
#define ps_res(x)    __builtin_ps_res(x)
#define ps_rsqrte(x) __builtin_ps_rsqrte(x)

// Binary paired-single ops.
#define ps_add(x, y)     __builtin_ps_add(x, y)
#define ps_sub(x, y)     __builtin_ps_sub(x, y)
#define ps_div(x, y)     __builtin_ps_div(x, y)
#define ps_mul(x, y)     __builtin_ps_mul(x, y)
#define ps_merge00(x, y) __builtin_ps_merge00(x, y)
#define ps_merge01(x, y) __builtin_ps_merge01(x, y)
#define ps_merge10(x, y) __builtin_ps_merge10(x, y)
#define ps_merge11(x, y) __builtin_ps_merge11(x, y)
#define ps_muls0(x, y)   __builtin_ps_muls0(x, y)
#define ps_muls1(x, y)   __builtin_ps_muls1(x, y)

// Ternary paired-single ops (multiply-add family, sum, select).
#define ps_madd(x, y, z)   __builtin_ps_madd(x, y, z)
#define ps_msub(x, y, z)   __builtin_ps_msub(x, y, z)
#define ps_nmadd(x, y, z)  __builtin_ps_nmadd(x, y, z)
#define ps_nmsub(x, y, z)  __builtin_ps_nmsub(x, y, z)
#define ps_sum0(x, y, z)   __builtin_ps_sum0(x, y, z)
#define ps_sum1(x, y, z)   __builtin_ps_sum1(x, y, z)
#define ps_madds0(x, y, z) __builtin_ps_madds0(x, y, z)
#define ps_madds1(x, y, z) __builtin_ps_madds1(x, y, z)
#define ps_sel(x, y, z)    __builtin_ps_sel(x, y, z)

// Quantized load/store forms. Plain loads/stores are emitted by the compiler
// on its own; these spellings cover the indexed/updated/quantized variants.
#define ps_l(v, w, i)      __builtin_psq_l(v, w, i)
#define ps_lu(v, w, i)     __builtin_psq_lu(v, w, i)
#define ps_lx(v, o, w, i)  __builtin_psq_lx(v, o, w, i)
#define ps_lux(v, o, w, i) __builtin_psq_lux(v, o, w, i)

#define ps_st(d, v, w, i)     __builtin_psq_st(d, v, w, i)
#define ps_stu(d, v, w, i)    __builtin_psq_stu(d, v, w, i)
#define ps_stx(d, v, o, w, i) __builtin_psq_stx(d, v, o, w, i)
#define ps_stux(d, v, o, w, i) __builtin_psq_stux(d, v, o, w, i)

#endif
