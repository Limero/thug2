// WIP DRAFT (non-matching) — identification pass 2026-08-26 (group 8)
// family=vfprintf range=0x8026BD70-0x8026D1B4 size=5188B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ============================================================================
// IDENTIFICATION: vfprintf-family engine ("__svfprintf_r", FLOATING-POINT
// variant) — int fn(FILE *f /*arg1*/, const char *fmt /*arg2*/,
//                       va_list ap /*arg3*/).
// Evidence:
//  - rodata2 lbl_802B20E0 = "bug in vfprintf: bad base" (want F9xx path),
//    pad tables lbl_802B2090="                " (16 spaces),
//    lbl_802B20A0="0000000000000000", digit sets lbl_802B20B0
//    ="0123456789abcdef", lbl_802B20CC="0123456789ABCDEF",
//    "(null)"=lbl_802B20C4; %e/%g consts lbl_802B2100=0.0, 2108=1.0,
//    2110=-4.0 (rodata2).
//  - Conversion switch covers %c s p n o u x X d i %, flags +-#0*., width/
//    precision incl. '*', length h/l/ll/q/L, uppercase D/E/G/O/U aliases.
//  - Output path: if (f->flags@0xC & 0x200) memcpy straight into the string
//    buffer (sprintf case) else set error flag @0xE when len==0 and call
//    writer fn_8026BBC4(f->fd@0xE, buf, len, flushflag) (fwrite case).
//  - va_list advance: ap->gp_offset@0x0 vs 8, reg save area @0x8,
//    overflow area @0x4 (PPC SysV va_list).
// Family context (call graph):
//   vsnprintf-family wrappers (0x80269xxx, build va_list on stack)
//     -> fn_8026BC98 dispatcher: scans fmt for [eEfgG] or 'L' prefix
//        -> FLOAT seen   -> HERE (fn_8026BD70)
//        -> no float     -> fn_8026D288 (integer-only twin, separate TU:
//                           it owns DUPLICATE copies of the digit strings
//                           lbl_802B2140/lbl_802B215C and its own writer
//                           copy fn_8026D1B4)
// Callees (arity audited against want call sites):
//   fn_8026EEF0(ptrA=&lbl_803CA420[0], &out_char_slot, fmt, w=*(u32*)&lbl_803CA40C,
//               &count_slot) -> segment scan length (>0 means hit '%').
//   fn_8026BBC4(fd, buf, len, flag)  stream/string writer (13 sites, NO crclr).
//   memcpy                            6 sites ALL with want-side
//                                    `crclr cr1eq` -> MUST stay unprototyped.
//   fn_802745E0 / fn_802740FC         64-bit div/mod by 10 (%d loop) —
//                                     want keeps crclr -> stay unprototyped.
//   fn_8026EDA8(f64)                  log10-ish helper for %e precision.
//   fn_8026B6DC(prec, fmtchar, flag, &sign_slot, double) -> digit string ptr
//                                     (%e/%f/%g formatter, dtoa family).
//   strlen / memchr                   libc (symbols.txt scope:global).
//
// WHY PARKED (structural — see also fn_8026F55C.c park note):
//  1. SDA addressing: want loads its two scanner-table words via
//     `lwz disp(r13)` (.sdata 0x803CA420/0x803CA40C). Game-code objects
//     (-G0) emit lis+addi absolute refs — never r13-relative. Same
//     prebuilt-runtime-object situation as pow/fn_8026F55C (route probe:
//     extra_cflags ["-msdata=eabi","-G8"]).
//  2. 1297 instructions: byte-exactness additionally needs schedule
//     equality across the whole conversion-switch engine (compare tree +
//     ~19 output blocks + 64-bit division loops). Multi-session rebuild.
//  Body below is the m2c skeleton with data references repaired
//  (fake saved_reg_r13 statics -> real lbl_ externs; bare literals ->
//  lbl_ forms; callee protos added per want's crclr map). It documents
//  control flow but does NOT match.
// ============================================================================
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 4.7% ([3]desc->4.7%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 memcpy(s32, s32, s32);

/* ---- data symbols referenced by the engine ---- */
extern char lbl_802B2090[];  /* rodata2: 16 spaces (left-pad source)      */
extern char lbl_802B20A0[];  /* rodata2: 16 zeros  (zero-pad source)      */
extern char lbl_802B20B0[];  /* "0123456789abcdef"                        */
extern char lbl_802B20C4[];  /* "(null)"                                  */
extern char lbl_802B20CC[];  /* "0123456789ABCDEF"                        */
extern char lbl_802B20E0[];  /* "bug in vfprintf: bad base"               */
extern f64 lbl_802B2100;     /* 0.0   (%e/%g special compares)            */
extern f64 lbl_802B2108;     /* 1.0                                       */
extern f64 lbl_802B2110;     /* -4.0                                      */
extern s32 lbl_803CA420;  /* .sdata: scanner table A (first word used) */
extern s32 lbl_803CA40C;  /* .sdata: scanner table B (first word = 1)  */

/* ---- callees (prototypes per want's crclr map) ---- */
extern void fn_8026E5B8(void);                      /* init hook (no crclr) */
extern s32 fn_8026EEF0(Unk_C7387A53 *, s32 *, void *, s32, void *);
extern s32 fn_8026BBC4(s32, u8 *, u32, s32);      /* writer, 13 sites     */
extern f64 fn_8026EDA8(f64);                        /* log10-ish            */
extern u8 *fn_8026B6DC(s32, s8, s32, char *, f64);  /* dtoa                 */
extern u32 strlen(const char *);
extern void *memchr(const void *, s32, u32);
/* NOTE: memcpy / fn_802745E0 / fn_802740FC deliberately UNPROTOTYPED —
 * want emits `crclr cr1eq` before every one of those bl sites. */
extern char lbl_802B20B0[];
extern char lbl_802B20CC[];
static s32 sp184;
static s32 sp188;
static s32 M2C_CARRY = 0;

s32 fn_8026BD70(CStruct *arg1, u8 *arg2, Unk_9509C1A6 *arg3, s32 arg0) {
s32 fs_t;
    s32 *sp188;
    s32 *sp184;
    s32 sp180;
    s16 sp17C;
    s32 sp178;
    s32 sp174;
    u8 sp170;                                       
    u8 sp16C;
    s8 sp10;
    s32 var_r5;
    f32 var_f1_2;
    f64 temp_f0;
    f64 temp_f0_2;
    f64 temp_f31;
    f64 var_f1;
    s16 temp_r0_4;
    s16 var_r0_2;
    s32 *var_r10;
    s32 *var_r3;
    s32 *var_r3_3;
    s32 *var_r3_4;
    s32 *var_r3_5;
    s32 *var_r3_6;
    s32 *var_r3_7;
    s32 *var_r8;
    s32 *var_r9;
    s32 *var_r9_10;
    s32 *var_r9_12;
    s32 *var_r9_13;
    s32 *var_r9_15;
    s32 *var_r9_16;
    s32 *var_r9_18;
    s32 *var_r9_19;
    s32 *var_r9_20;
    s32 *var_r9_2;
    s32 *var_r9_5;
    s32 *var_r9_6;
    s32 *var_r9_9;
    s32 temp_cr0_eq;
    s32 temp_r0_3;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_cr0_eq;
    s32 var_r0_3;
    s32 var_r15;
    s32 var_r16;
    s32 var_r21;
    s32 var_r23;
    s32 var_r24;
    s32 var_r25;
    s32 var_r25_2;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 var_r30_5;
    s32 var_r30_6;
    s32 var_r30_7;
    s32 var_r9_3;
    s32 var_r9_7;
    s8 temp_r11_6;
    s8 var_r0;
    s8 var_r26;
    s8 var_r9_11;
    s8 var_r9_14;
    s8 var_r9_17;
    s8 var_r9_4;
    s8 var_r9_8;
    u32 temp_r10_2;
    u32 temp_r10_3;
    u32 temp_r4;
    u32 var_r31;
    u64 temp_ret;
    u8 *temp_r27;
    u8 *var_r22;
    u8 *var_r27;
    u8 *var_r3_2;
    u8 temp_r0;
    u8 temp_r0_2;
    u8 temp_r10;
    u8 temp_r11;
    u8 temp_r11_10;
    u8 temp_r11_11;
    u8 temp_r11_12;
    u8 temp_r11_13;
    u8 temp_r11_14;
    u8 temp_r11_15;
    u8 temp_r11_2;
    u8 temp_r11_3;
    u8 temp_r11_4;
    u8 temp_r11_5;
    u8 temp_r11_7;
    u8 temp_r11_9;
    u8 temp_r9;
    u8 temp_r9_2;
    u8 temp_r9_3;
    u8 temp_r9_4;
    u8 temp_r9_5;
    u8 temp_r9_6;
    u8 temp_r9_7;
    u8 temp_r9_8;
    CStruct *temp_r11_16;
    CStruct *temp_r11_17;
    CStruct *temp_r11_18;
    CStruct *temp_r11_19;
    CStruct *temp_r11_8;

    var_r22 = arg2;
    var_r15 = 0;
    fn_8026E5B8();
    sp184 = &sp174;
    sp178 = 0;
    sp188 = &sp178;
loop_1:
    temp_r27 = var_r22;
loop_2:
    temp_r3 = fn_8026EEF0(lbl_803CA420, sp184, var_r22, lbl_803CA40C, sp188);
    if (temp_r3 > 0) {
        var_r22 = &var_r22[temp_r3];
        if (sp174 == 0x25) {
            var_r22 -= 1;
        } else {
            goto loop_2;
        }
    }
    temp_r31 = (s32)var_r22 - (s32)var_r22;
    if (temp_r31 != 0) {
        if (arg1->unk0xC & 0x200) {
            memcpy(arg1->unk0x0, temp_r27, temp_r31);
            arg1->unk0x0 = (void *) (arg1->unk0x0 + temp_r31);
        } else {
            if ((s32) arg1->unk0xC == 0) {
                *(s32 *)((char *)arg1 + (s32)0xE) = 1;
            }
            fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), temp_r27, temp_r31, 0);
        }
        var_r15 += temp_r31;
    }
    if (temp_r3 > 0) {
        var_r16 = 0;
        var_r22 += 1;
        sp170 = 0;
        var_r24 = 0;
        var_r23 = 0;
loop_14:
        var_r25 = -1;
loop_15:
        temp_r0 = *((s32 *)var_r22);
        var_r22 += 1;
        var_r26 = (s8) temp_r0;
loop_16:
        if (var_r26 != 0x63) {
            if (var_r26 <= 0x63) {
                switch (var_r26) {                  
                case 0x20:                          
                    if ((s32) sp170 == 0) {
                    case 0x2B:                      
                        sp170 = var_r26;
                    }
                    goto loop_15;
                case 0x23:                          
                    var_r24 |= 1;
                    goto loop_15;
                case 0x2A:                          
                    temp_r11 = arg3->unk0x0;
                    if ((u32) ((s8) temp_r11 + 1) <= 8U) {
                        var_r9 = arg3->unk0x8 + ((s8) temp_r11 * 4);
                        arg3->unk0x0 = (u8) (temp_r11 + 1);
                    } else {
                        if ((s8) temp_r11 <= 7) {
                            var_r9 = arg3->unk0x4;
                            arg3->unk0x0 = 8U;
                        } else {
                            var_r9 = arg3->unk0x4;
                        }
                        arg3->unk0x4 = (s32 *) (var_r9 + 4);
                    }
                    var_r16 = *((s32 *)var_r9);
                    if (var_r16 < 0) {
                        var_r16 = -var_r16;
                    case 0x2D:                      
                        var_r24 |= 4;
                    }
                    goto loop_15;
                case 0x2E:                          
                    temp_r0_2 = *((s32 *)var_r22);
                    var_r22 += 1;
                    var_r26 = (s8) temp_r0_2;
                    if (var_r26 == 0x2A) {
                        temp_r11_2 = arg3->unk0x0;
                        if ((u32) ((s8) temp_r11_2 + 1) <= 8U) {
                            var_r3 = arg3->unk0x8 + ((s8) temp_r11_2 * 4);
                            arg3->unk0x0 = (u8) (temp_r11_2 + 1);
                        } else {
                            if ((s8) temp_r11_2 <= 7) {
                                var_r3 = arg3->unk0x4;
                                arg3->unk0x0 = 8U;
                            } else {
                                var_r3 = arg3->unk0x4;
                            }
                            arg3->unk0x4 = (s32 *) (var_r3 + 4);
                        }
                        var_r25 = *((s32 *)var_r3);
                        if (var_r25 < -1) {
                            goto loop_14;
                        }
                        goto loop_15;
                    }
                    var_r30 = 0;
                    if ((u32) (var_r26 - 0x30) <= 9U) {
                        do {
                            temp_r11_3 = *((s32 *)var_r22);
                            var_r22 += 1;
                            var_r30 = (var_r30 * 0xA) - 0x30 + var_r26;
                            var_r26 = (s8) temp_r11_3;
                        } while ((u32) (var_r26 - 0x30) <= 9U);
                    }
                    var_r25 = var_r30;
                    if (var_r25 < -1) {
                        var_r25 = -1;
                    }
                    goto loop_16;
                case 0x30:                          
                    var_r24 |= 0x80;
                    goto loop_15;
                default:                            
                    var_r30_2 = 0;
                    do {
                        temp_r11_4 = *((s32 *)var_r22);
                        var_r22 += 1;
                        var_r30_2 = (var_r30_2 * 0xA) - 0x30 + var_r26;
                        var_r26 = (s8) temp_r11_4;
                    } while ((u32) (var_r26 - 0x30) <= 9U);
                    var_r16 = var_r30_2;
                    goto loop_16;
                case 0x4C:                          
                    var_r24 |= 8;
                    goto loop_15;
                case 0x44:                          
                    var_r24 |= 0x10;
                    goto block_108;
                case 0x45:                          
                case 0x47:                          
                    var_r5 = 0;
                    if (var_r25 == -1) {
                        var_r25 = 6;
                    }
                    temp_r10 = *(s32 *)((char *)arg3 + (s32)0x1);
                    if ((s8) temp_r10 <= 7) {
                        var_r9_2 = arg3->unk0x8 + (((s8) temp_r10 * 8) + 0x20);
                        *(s32 *)((char *)arg3 + (s32)0x1) = (u8) (temp_r10 + 1);
                    } else {
                        var_r9_2 = arg3->unk0x4;
                        arg3->unk0x4 = (s32 *) (var_r9_2 + 8);
                    }
                    temp_f31 = *((s32 *)var_r9_2);
                    0;
                    if ((var_r26 == 0x67) || (var_r26 == 0x47)) {
                        temp_f0 = lbl_802B2100;
                        if ((f32) temp_f31 != (f32) temp_f0) {
                            var_f1 = temp_f31;
                            if ((f32) temp_f31 < (f32) temp_f0) {
                                var_f1 = -temp_f31;
                            }
                            var_f1_2 = fn_8026EDA8(var_f1);
                        } else {
                            var_f1_2 = (f32) lbl_802B2108;
                        }
                        temp_f0_2 = lbl_802B2110;
                        var_cr0_eq = var_f1_2 == (f32) temp_f0_2;
                        if ((var_f1_2 < (f32) temp_f0_2) || (var_cr0_eq = var_f1_2 == (f32) (f64) var_r25, 0, (0 != 0))) {
                            var_r0 = 0x45;
                            0;
                            if (var_cr0_eq != 0) {
                                var_r0 = 0x65;
                            }
                            var_r26 = var_r0;
                        } else {
                            var_r26 = 0x66;
                        }
                        var_r5 = 1;
                    }
                    if (var_r24 & 1) {
                        if (var_r25 == 0) {
                            var_r25 = 1;
                        }
                        var_r5 = 0;
                    }
                    var_r3_2 = fn_8026B6DC(var_r25, var_r26, var_r5, &sp170, temp_f31);
                    var_r27 = var_r3_2;
                    goto block_333;
                case 0x4F:                          
                    var_r24 |= 0x10;
                    goto block_193;
                case 0x55:                          
                    var_r24 |= 0x10;
                    goto block_246;
                case 0x58:                          
                    var_r9_3 = (s32)lbl_802B20CC;
                    goto block_279;
                }
            } else {
                switch (var_r26) {                  
                case 0x68:                          
                    var_r24 |= 0x40;
                    goto loop_15;
                case 0x6C:                          
                    if ((s32) *((s32 *)var_r22) == 0x6C) {
                        var_r22 += 1;
                    case 0x71:                      
                        var_r24 |= 0x20;
                    } else {
                        var_r24 |= 0x10;
                    }
                    goto loop_15;
                case 0x69:                          
block_108:
                    if (var_r24 & 0x20) {
                        temp_r9 = arg3->unk0x0;
                        if ((u32) ((s8) temp_r9 + 2) <= 8U) {
                            if (temp_r9 & 1) {
                                arg3->unk0x0 = (u8) (temp_r9 + 1);
                            }
                            temp_r9_2 = arg3->unk0x0;
                            arg3->unk0x0 = (u8) (temp_r9_2 + 2);
                            var_r3_3 = arg3->unk0x8 + ((s8) temp_r9_2 * 4);
                        } else {
                            if ((s8) temp_r9 <= 7) {
                                var_r3_3 = arg3->unk0x4;
                                arg3->unk0x0 = 8U;
                            } else {
                                var_r3_3 = arg3->unk0x4;
                            }
                            arg3->unk0x4 = (s32 *) (var_r3_3 + 8);
                        }
                        var_r30_3 = ((CStruct *)var_r3_3)->unk0x0;
                        var_r31 = ((CStruct *)var_r3_3)->unk0x4;
                    } else {
                        if (var_r24 & 0x10) {
                            var_r9_4 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_4 + 1) > 8U) {
                                if (var_r9_4 <= 7) {
                                    var_r9_5 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    goto block_134;
                                }
                                goto block_135;
                            }
                            goto block_131;
                            goto block_136;
                        }
                        if (var_r24 & 0x40) {
                            temp_r11_5 = arg3->unk0x0;
                            if ((u32) ((s8) temp_r11_5 + 1) <= 8U) {
                                var_r9_6 = arg3->unk0x8 + ((s8) temp_r11_5 * 4);
                                arg3->unk0x0 = (u8) (temp_r11_5 + 1);
                            } else {
                                if ((s8) temp_r11_5 <= 7) {
                                    var_r9_6 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    var_r9_6 = arg3->unk0x4;
                                }
                                arg3->unk0x4 = (s32 *) (var_r9_6 + 4);
                            }
                            var_r0_2 = *(s32 *)((char *)var_r9_6 + (s32)0x2);
                        } else {
                            var_r9_4 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_4 + 1) <= 8U) {
block_131:
                                var_r9_5 = arg3->unk0x8 + (var_r9_4 * 4);
                                arg3->unk0x0 = (u8) (arg3->unk0x0 + 1);
                            } else {
                                if (var_r9_4 <= 7) {
                                    var_r9_5 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
block_134:
                                    var_r9_5 = arg3->unk0x4;
                                }
block_135:
                                arg3->unk0x4 = (s32 *) (var_r9_5 + 4);
                            }
block_136:
                            var_r0_2 = (s16) *((s32 *)var_r9_5);
                        }
                        var_r30_3 = (s32) (var_r0_2 >> 0x1F);
                        var_r31 = (u32) var_r0_2;
                    }
                    if (var_r30_3 < 0) {
                        s64 n64 = -(((s64)var_r30_3 << 32) | var_r31);
                        var_r30_3 = (s32) (n64 >> 32);
                        var_r31 = (u32) n64;
                        sp170 = 0x2D;
                    }
                    var_r9_7 = 1;
block_313:
                    var_r23 = var_r25;
                    0;
                    if (var_r23 >= 0) {
                        var_r24 &= QB_UNKNOWN_0xFFFFFF7F;
                    }
                    var_r27 = &sp16C;
                    temp_cr0_eq = (var_r30_3 | var_r31) == 0;
                    if ((temp_cr0_eq == 0) || (temp_cr0_eq == 0)) {
                        if (var_r9_7 != 1) {
                            if ((u32) var_r9_7 >= 1U) {
                                if (var_r9_7 != 2) {
                                    var_r27 = (u8 *)lbl_802B20E0;
                                    var_r3_2 = (u8 *)lbl_802B20E0;
block_333:
                                    var_r21 = strlen(var_r3_2);
                                } else {
                                    do {
                                        temp_r10_2 = (var_r30_3 << 0x1C) | (var_r31 >> 4U);
                                        temp_r0_3 = var_r31 & 0xF;
                                        var_r30_3 = (s32) ((u32) var_r30_3 >> 4U);
                                        var_r31 = temp_r10_2;
                                        var_r27 -= 1;
                                        *(u8 *)((char *)var_r27 - 0x1) = (u8) *((s32 *)sp180 + (s32)temp_r0_3);
                                    } while ((var_r30_3 | var_r31) != 0);
                                    goto block_334;
                                }
                            } else {
                                do {
                                    temp_r10_3 = (var_r30_3 << 0x1D) | (var_r31 >> 3U);
                                    temp_r11_6 = (var_r31 & 7) + 0x30;
                                    var_r30_3 = (s32) ((u32) var_r30_3 >> 3U);
                                    var_r31 = temp_r10_3;
                                    var_r27 -= 1;
                                    *(u8 *)((char *)var_r27 - 0x1) = temp_r11_6;
                                } while ((var_r30_3 | var_r31) != 0);
                                if ((var_r24 & 1) && (temp_r11_6 != 0x30)) {
                                    var_r27 -= 1;
                                    *(u8 *)((char *)var_r27 - 0x1) = 0x30;
                                }
                                goto block_334;
                            }
                        } else {
loop_326:
                            if ((u32) var_r30_3 > 0U) {
block_325:
                                var_r27 -= 1;
                                *(u8 *)((char *)var_r27 - 0x1) = (s8) ((u32) fn_802745E0((u64) var_r30_3, var_r31, 0, 0xA) + 0x30);
                                fs_t = fn_802740FC((u64) var_r30_3, var_r31, 0, 0xA);
                                temp_r4 = (u32) temp_ret;
                                temp_ret = fs_t;
                                var_r30_3 = temp_ret;
                                var_r31 = temp_r4;
                                goto loop_326;
                            }
                            if ((var_r30_3 == 0) && (var_r31 > 9U)) {
                                goto block_325;
                            }
                            var_r27 -= 1;
                            *(u8 *)((char *)var_r27 - 0x1) = (s8) (var_r31 + 0x30);
                            goto block_334;
                        }
                    } else {
block_334:
                        var_r21 = ((s32)&sp16C - 0) - (s32)var_r27;
                    }
                    goto block_337;
                case 0x6E:                          
                    if (var_r24 & 0x20) {
                        temp_r11_7 = arg3->unk0x0;
                        if ((u32) ((s8) temp_r11_7 + 1) <= 8U) {
                            var_r8 = arg3->unk0x8 + ((s8) temp_r11_7 * 4);
                            arg3->unk0x0 = (u8) (temp_r11_7 + 1);
                        } else {
                            if ((s8) temp_r11_7 <= 7) {
                                var_r8 = arg3->unk0x4;
                                arg3->unk0x0 = 8U;
                            } else {
                                var_r8 = arg3->unk0x4;
                            }
                            arg3->unk0x4 = (s32 *) (var_r8 + 4);
                        }
                        temp_r11_8 = *((s32 *)var_r8);
                        temp_r11_8->unk0x0 = (s32) (var_r15 >> 0x1F);
                        temp_r11_8->unk0x4 = var_r15;
                    } else {
                        if (var_r24 & 0x10) {
                            var_r9_8 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_8 + 1) > 8U) {
                                if (var_r9_8 <= 7) {
                                    var_r9_9 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    goto block_189;
                                }
                                goto block_190;
                            }
                            goto block_186;
                            goto block_191;
                        }
                        if (var_r24 & 0x40) {
                            temp_r11_9 = arg3->unk0x0;
                            if ((u32) ((s8) temp_r11_9 + 1) <= 8U) {
                                var_r9_10 = arg3->unk0x8 + ((s8) temp_r11_9 * 4);
                                arg3->unk0x0 = (u8) (temp_r11_9 + 1);
                            } else {
                                if ((s8) temp_r11_9 <= 7) {
                                    var_r9_10 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    var_r9_10 = arg3->unk0x4;
                                }
                                arg3->unk0x4 = (s32 *) (var_r9_10 + 4);
                            }
                            **(s16 **)var_r9_10 = (s16) var_r15;
                        } else {
                            var_r9_8 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_8 + 1) <= 8U) {
block_186:
                                var_r9_9 = arg3->unk0x8 + (var_r9_8 * 4);
                                arg3->unk0x0 = (u8) (arg3->unk0x0 + 1);
                            } else {
                                if (var_r9_8 <= 7) {
                                    var_r9_9 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
block_189:
                                    var_r9_9 = arg3->unk0x4;
                                }
block_190:
                                arg3->unk0x4 = (s32 *) (var_r9_9 + 4);
                            }
block_191:
                            **(s16 **)var_r9_9 = var_r15;
                        }
                    }
                    goto loop_1;
                case 0x6F:                          
block_193:
                    if (var_r24 & 0x20) {
                        temp_r9_3 = arg3->unk0x0;
                        if ((u32) ((s8) temp_r9_3 + 2) <= 8U) {
                            if (temp_r9_3 & 1) {
                                arg3->unk0x0 = (u8) (temp_r9_3 + 1);
                            }
                            temp_r9_4 = arg3->unk0x0;
                            arg3->unk0x0 = (u8) (temp_r9_4 + 2);
                            var_r3_4 = arg3->unk0x8 + ((s8) temp_r9_4 * 4);
                        } else {
                            if ((s8) temp_r9_3 <= 7) {
                                var_r3_4 = arg3->unk0x4;
                                arg3->unk0x0 = 8U;
                            } else {
                                var_r3_4 = arg3->unk0x4;
                            }
                            arg3->unk0x4 = (s32 *) (var_r3_4 + 8);
                        }
                        var_r30_3 = ((CStruct *)var_r3_4)->unk0x0;
                        var_r31 = ((CStruct *)var_r3_4)->unk0x4;
                    } else {
                        if (var_r24 & 0x10) {
                            var_r9_11 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_11 + 1) > 8U) {
                                if (var_r9_11 <= 7) {
                                    var_r9_12 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    goto block_219;
                                }
                                goto block_220;
                            }
                            goto block_216;
                            goto block_221;
                        }
                        if (var_r24 & 0x40) {
                            temp_r11_10 = arg3->unk0x0;
                            if ((u32) ((s8) temp_r11_10 + 1) <= 8U) {
                                var_r9_13 = arg3->unk0x8 + ((s8) temp_r11_10 * 4);
                                arg3->unk0x0 = (u8) (temp_r11_10 + 1);
                            } else {
                                if ((s8) temp_r11_10 <= 7) {
                                    var_r9_13 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    var_r9_13 = arg3->unk0x4;
                                }
                                arg3->unk0x4 = (s32 *) (var_r9_13 + 4);
                            }
                            var_r31 = (u32) *(u32 *)((char *)var_r9_13 + (s32)0x2);
                        } else {
                            var_r9_11 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_11 + 1) <= 8U) {
block_216:
                                var_r9_12 = arg3->unk0x8 + (var_r9_11 * 4);
                                arg3->unk0x0 = (u8) (arg3->unk0x0 + 1);
                            } else {
                                if (var_r9_11 <= 7) {
                                    var_r9_12 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
block_219:
                                    var_r9_12 = arg3->unk0x4;
                                }
block_220:
                                arg3->unk0x4 = (s32 *) (var_r9_12 + 4);
                            }
block_221:
                            var_r31 = *((s32 *)var_r9_12);
                        }
                        var_r30_3 = 0;
                    }
                    var_r9_7 = 0;
block_312:
                    sp170 = 0;
                    goto block_313;
                case 0x70:                          
                    temp_r11_11 = arg3->unk0x0;
                    if ((u32) ((s8) temp_r11_11 + 1) <= 8U) {
                        var_r10 = arg3->unk0x8 + ((s8) temp_r11_11 * 4);
                        arg3->unk0x0 = (u8) (temp_r11_11 + 1);
                    } else {
                        if ((s8) temp_r11_11 <= 7) {
                            var_r10 = arg3->unk0x4;
                            arg3->unk0x0 = 8U;
                        } else {
                            var_r10 = arg3->unk0x4;
                        }
                        arg3->unk0x4 = (s32 *) (var_r10 + 4);
                    }
                    var_r31 = *((s32 *)var_r10);
                    var_r24 |= 2;
                    sp180 = (s32)lbl_802B20B0;
                    var_r30_3 = 0;
                    var_r9_7 = 2;
                    var_r26 = 0x78;
                    goto block_312;
                case 0x73:                          
                    temp_r11_12 = arg3->unk0x0;
                    if ((u32) ((s8) temp_r11_12 + 1) <= 8U) {
                        var_r3_5 = arg3->unk0x8 + ((s8) temp_r11_12 * 4);
                        arg3->unk0x0 = (u8) (temp_r11_12 + 1);
                    } else {
                        if ((s8) temp_r11_12 <= 7) {
                            var_r3_5 = arg3->unk0x4;
                            arg3->unk0x0 = 8U;
                        } else {
                            var_r3_5 = arg3->unk0x4;
                        }
                        arg3->unk0x4 = (s32 *) (var_r3_5 + 4);
                    }
                    var_r27 = *((s32 *)var_r3_5);
                    if (var_r27 == NULL) {
                        var_r27 = (u8 *)lbl_802B20C4;
                    }
                    if (var_r25 >= 0) {
                        temp_r3_2 = memchr(var_r27, 0, var_r25);
                        if ((temp_r3_2 == 0) || (var_r21 = (s32)temp_r3_2 - (s32)var_r27, ((var_r21 > var_r25) != 0))) {
                            var_r21 = var_r25;
                        }
                    } else {
                        var_r21 = strlen(var_r27);
                    }
                    sp170 = 0;
                    goto block_337;
                case 0x75:                          
block_246:
                    if (var_r24 & 0x20) {
                        temp_r9_5 = arg3->unk0x0;
                        if ((u32) ((s8) temp_r9_5 + 2) <= 8U) {
                            if (temp_r9_5 & 1) {
                                arg3->unk0x0 = (u8) (temp_r9_5 + 1);
                            }
                            temp_r9_6 = arg3->unk0x0;
                            arg3->unk0x0 = (u8) (temp_r9_6 + 2);
                            var_r3_6 = arg3->unk0x8 + ((s8) temp_r9_6 * 4);
                        } else {
                            if ((s8) temp_r9_5 <= 7) {
                                var_r3_6 = arg3->unk0x4;
                                arg3->unk0x0 = 8U;
                            } else {
                                var_r3_6 = arg3->unk0x4;
                            }
                            arg3->unk0x4 = (s32 *) (var_r3_6 + 8);
                        }
                        var_r30_3 = ((CStruct *)var_r3_6)->unk0x0;
                        var_r31 = ((CStruct *)var_r3_6)->unk0x4;
                    } else {
                        if (var_r24 & 0x10) {
                            var_r9_14 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_14 + 1) > 8U) {
                                if (var_r9_14 <= 7) {
                                    var_r9_15 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    goto block_272;
                                }
                                goto block_273;
                            }
                            goto block_269;
                            goto block_274;
                        }
                        if (var_r24 & 0x40) {
                            temp_r11_13 = arg3->unk0x0;
                            if ((u32) ((s8) temp_r11_13 + 1) <= 8U) {
                                var_r9_16 = arg3->unk0x8 + ((s8) temp_r11_13 * 4);
                                arg3->unk0x0 = (u8) (temp_r11_13 + 1);
                            } else {
                                if ((s8) temp_r11_13 <= 7) {
                                    var_r9_16 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    var_r9_16 = arg3->unk0x4;
                                }
                                arg3->unk0x4 = (s32 *) (var_r9_16 + 4);
                            }
                            var_r31 = (u32) *(u32 *)((char *)var_r9_16 + (s32)0x2);
                        } else {
                            var_r9_14 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_14 + 1) <= 8U) {
block_269:
                                var_r9_15 = arg3->unk0x8 + (var_r9_14 * 4);
                                arg3->unk0x0 = (u8) (arg3->unk0x0 + 1);
                            } else {
                                if (var_r9_14 <= 7) {
                                    var_r9_15 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
block_272:
                                    var_r9_15 = arg3->unk0x4;
                                }
block_273:
                                arg3->unk0x4 = (s32 *) (var_r9_15 + 4);
                            }
block_274:
                            var_r31 = *((s32 *)var_r9_15);
                        }
                        var_r30_3 = 0;
                    }
                    var_r9_7 = 1;
                    goto block_312;
                case 0x78:                          
                    var_r9_3 = (s32)lbl_802B20B0;
block_279:
                    sp180 = var_r9_3;
                    if (var_r24 & 0x20) {
                        temp_r9_7 = arg3->unk0x0;
                        if ((u32) ((s8) temp_r9_7 + 2) <= 8U) {
                            if (temp_r9_7 & 1) {
                                arg3->unk0x0 = (u8) (temp_r9_7 + 1);
                            }
                            temp_r9_8 = arg3->unk0x0;
                            arg3->unk0x0 = (u8) (temp_r9_8 + 2);
                            var_r3_7 = arg3->unk0x8 + ((s8) temp_r9_8 * 4);
                        } else {
                            if ((s8) temp_r9_7 <= 7) {
                                var_r3_7 = arg3->unk0x4;
                                arg3->unk0x0 = 8U;
                            } else {
                                var_r3_7 = arg3->unk0x4;
                            }
                            arg3->unk0x4 = (s32 *) (var_r3_7 + 8);
                        }
                        var_r30_3 = ((CStruct *)var_r3_7)->unk0x0;
                        var_r31 = ((CStruct *)var_r3_7)->unk0x4;
                    } else {
                        if (var_r24 & 0x10) {
                            var_r9_17 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_17 + 1) > 8U) {
                                if (var_r9_17 <= 7) {
                                    var_r9_18 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    goto block_305;
                                }
                                goto block_306;
                            }
                            goto block_302;
                            goto block_307;
                        }
                        if (var_r24 & 0x40) {
                            temp_r11_14 = arg3->unk0x0;
                            if ((u32) ((s8) temp_r11_14 + 1) <= 8U) {
                                var_r9_19 = arg3->unk0x8 + ((s8) temp_r11_14 * 4);
                                arg3->unk0x0 = (u8) (temp_r11_14 + 1);
                            } else {
                                if ((s8) temp_r11_14 <= 7) {
                                    var_r9_19 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    var_r9_19 = arg3->unk0x4;
                                }
                                arg3->unk0x4 = (s32 *) (var_r9_19 + 4);
                            }
                            var_r31 = (u32) *(u32 *)((char *)var_r9_19 + (s32)0x2);
                        } else {
                            var_r9_17 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_17 + 1) <= 8U) {
block_302:
                                var_r9_18 = arg3->unk0x8 + (var_r9_17 * 4);
                                arg3->unk0x0 = (u8) (arg3->unk0x0 + 1);
                            } else {
                                if (var_r9_17 <= 7) {
                                    var_r9_18 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
block_305:
                                    var_r9_18 = arg3->unk0x4;
                                }
block_306:
                                arg3->unk0x4 = (s32 *) (var_r9_18 + 4);
                            }
block_307:
                            var_r31 = *((s32 *)var_r9_18);
                        }
                        var_r30_3 = 0;
                    }
                    var_r9_7 = 2;
                    if ((var_r24 & 1) && ((var_r30_3 | var_r31) != 0)) {
                        var_r24 |= 2;
                    }
                    goto block_312;
                }
            }
        } else {
            temp_r11_15 = arg3->unk0x0;
            var_r27 = (u8 *) &sp10;
            if ((u32) ((s8) temp_r11_15 + 1) <= 8U) {
                var_r9_20 = arg3->unk0x8 + ((s8) temp_r11_15 * 4);
                arg3->unk0x0 = (u8) (temp_r11_15 + 1);
            } else {
                if ((s8) temp_r11_15 <= 7) {
                    var_r9_20 = arg3->unk0x4;
                    arg3->unk0x0 = 8U;
                } else {
                    var_r9_20 = arg3->unk0x4;
                }
                arg3->unk0x4 = (s32 *) (var_r9_20 + 4);
            }
            var_r21 = 1;
            *((s32 *)var_r27) = *(s32 *)((char *)var_r9_20 + (s32)0x3);
            sp170 = 0;
block_337:
            var_r25_2 = var_r21;
            if (var_r25_2 < var_r23) {
                var_r25_2 = var_r23;
            }
            if ((s32) sp170 != 0) {
                var_r25_2 += 1;
            } else if (var_r24 & 2) {
                var_r25_2 += 2;
            }
            if (!(var_r24 & 0x84)) {
                var_r30_4 = var_r16 - var_r25_2;
                if (var_r30_4 > 0) {
                    if (var_r30_4 > 0x10) {
                        do {
                            if (arg1->unk0xC & 0x200) {
                                temp_r11_16 = arg1->unk0x0;
                                temp_r11_16->unk0x0 = (s32) ((CStruct *)lbl_802B2090)->unk0x0;
                                temp_r11_16->unk0xC = (s32) ((CStruct *)lbl_802B2090)->unk0xC;
                                temp_r11_16->unk0x4 = (s32) ((CStruct *)lbl_802B2090)->unk0x4;
                                temp_r11_16->unk0x8 = (s32) ((CStruct *)lbl_802B2090)->unk0x8;
                                arg1->unk0x0 = (void *) (*((char *)&arg1->unk0x0) + 0x10);
                            } else {
                                if ((s32) arg1->unk0xC == 0) {
                                    *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                                }
                                fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2090, 0x10, 0);
                            }
                            var_r30_4 -= 0x10;
                        } while (var_r30_4 > 0x10);
                    }
                    if (arg1->unk0xC & 0x200) {
                        memcpy(arg1->unk0x0, (u8 *)lbl_802B2090, var_r30_4);
                        arg1->unk0x0 = (void *) (arg1->unk0x0 + var_r30_4);
                    } else {
                        if ((s32) arg1->unk0xC == 0) {
                            *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                        }
                        fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2090, var_r30_4, 0);
                    }
                }
            }
            if ((s32) sp170 != 0) {
                if (arg1->unk0xC & 0x200) {
                    *(s32 *)(*(s32 *)((char *)((char *)arg1) + 0x0) + 0x0) = sp170;
                    arg1->unk0x0 = (void *) (arg1->unk0x0 + 1);
                } else {
                    if ((s32) arg1->unk0xC == 0) {
                        *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                    }
                    fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), &sp170, 1, 0);
                }
            } else if (var_r24 & 2) {
                temp_r0_4 = (u8) var_r26 | 0x3000;
                sp17C = temp_r0_4;
                if (arg1->unk0xC & 0x200) {
                    *(s32 *)(*(s32 *)((char *)((char *)arg1) + 0x0) + 0x0) = temp_r0_4;
                    arg1->unk0x0 = (void *) (arg1->unk0x0 + 2);
                } else {
                    if ((s32) arg1->unk0xC == 0) {
                        *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                    }
                    fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *) &sp17C, 2, 0);
                }
            }
            if ((s32) (var_r24 & 0x84) == 0x80) {
                var_r30_5 = var_r16 - var_r25_2;
                if (var_r30_5 > 0) {
                    if (var_r30_5 > 0x10) {
                        do {
                            if (arg1->unk0xC & 0x200) {
                                temp_r11_17 = arg1->unk0x0;
                                temp_r11_17->unk0x0 = (s32) ((CStruct *)lbl_802B20A0)->unk0x0;
                                temp_r11_17->unk0xC = (s32) ((CStruct *)lbl_802B20A0)->unk0xC;
                                temp_r11_17->unk0x4 = (s32) ((CStruct *)lbl_802B20A0)->unk0x4;
                                temp_r11_17->unk0x8 = (s32) ((CStruct *)lbl_802B20A0)->unk0x8;
                                arg1->unk0x0 = (void *) (*((char *)&arg1->unk0x0) + 0x10);
                            } else {
                                if ((s32) arg1->unk0xC == 0) {
                                    *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                                }
                                fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B20A0, 0x10, 0);
                            }
                            var_r30_5 -= 0x10;
                        } while (var_r30_5 > 0x10);
                    }
                    if (arg1->unk0xC & 0x200) {
                        memcpy(arg1->unk0x0, (u8 *)lbl_802B20A0, var_r30_5);
                        arg1->unk0x0 = (void *) (arg1->unk0x0 + var_r30_5);
                    } else {
                        if ((s32) arg1->unk0xC == 0) {
                            *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                        }
                        fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B20A0, var_r30_5, 0);
                    }
                }
            }
            var_r30_6 = var_r23 - var_r21;
            if (var_r30_6 > 0) {
                if (var_r30_6 > 0x10) {
                    do {
                        if (arg1->unk0xC & 0x200) {
                            temp_r11_18 = arg1->unk0x0;
                            temp_r11_18->unk0x0 = (s32) ((CStruct *)lbl_802B20A0)->unk0x0;
                            temp_r11_18->unk0xC = (s32) ((CStruct *)lbl_802B20A0)->unk0xC;
                            temp_r11_18->unk0x4 = (s32) ((CStruct *)lbl_802B20A0)->unk0x4;
                            temp_r11_18->unk0x8 = (s32) ((CStruct *)lbl_802B20A0)->unk0x8;
                            arg1->unk0x0 = (void *) (*((char *)&arg1->unk0x0) + 0x10);
                        } else {
                            if ((s32) arg1->unk0xC == 0) {
                                *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                            }
                            fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B20A0, 0x10, 0);
                        }
                        var_r30_6 -= 0x10;
                    } while (var_r30_6 > 0x10);
                }
                if (arg1->unk0xC & 0x200) {
                    memcpy(arg1->unk0x0, (u8 *)lbl_802B20A0, var_r30_6);
                    arg1->unk0x0 = (void *) (arg1->unk0x0 + var_r30_6);
                } else {
                    if ((s32) arg1->unk0xC == 0) {
                        *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                    }
                    fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B20A0, var_r30_6, 0);
                }
            }
            if (arg1->unk0xC & 0x200) {
                memcpy(arg1->unk0x0, var_r27, var_r21);
                arg1->unk0x0 = (void *) (arg1->unk0x0 + var_r21);
            } else {
                if ((s32) arg1->unk0xC == 0) {
                    *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                }
                fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), var_r27, var_r21, 0);
            }
            if (var_r24 & 4) {
                var_r30_7 = var_r16 - var_r25_2;
                if (var_r30_7 > 0) {
                    if (var_r30_7 > 0x10) {
                        do {
                            if (arg1->unk0xC & 0x200) {
                                temp_r11_19 = arg1->unk0x0;
                                temp_r11_19->unk0xC = (s32) ((CStruct *)lbl_802B2090)->unk0xC;
                                temp_r11_19->unk0x8 = (s32) ((CStruct *)lbl_802B2090)->unk0x8;
                                temp_r11_19->unk0x4 = (s32) ((CStruct *)lbl_802B2090)->unk0x4;
                                temp_r11_19->unk0x0 = (s32) ((CStruct *)lbl_802B2090)->unk0x0;
                                arg1->unk0x0 = (void *) (*((char *)&arg1->unk0x0) + 0x10);
                            } else {
                                if ((s32) arg1->unk0xC == 0) {
                                    *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                                }
                                fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2090, 0x10, 0);
                            }
                            var_r30_7 -= 0x10;
                        } while (var_r30_7 > 0x10);
                    }
                    if (arg1->unk0xC & 0x200) {
                        memcpy(arg1->unk0x0, (u8 *)lbl_802B2090, var_r30_7);
                        arg1->unk0x0 = (void *) (arg1->unk0x0 + var_r30_7);
                    } else {
                        if ((s32) arg1->unk0xC == 0) {
                            *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                        }
                        fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2090, var_r30_7, 0);
                    }
                }
            }
            var_r0_3 = var_r25_2;
            if (var_r0_3 < var_r16) {
                var_r0_3 = var_r16;
            }
            var_r15 += var_r0_3;
            goto loop_1;
        }
    }
    if (!(arg1->unk0xC & 0x200)) {
        fn_8026BBC4(*(s32 *)((char *)arg1 + (s32)0xE), NULL, 0, 1);
    }
    return var_r15;
    
    
    sp10 = var_r26;
    sp170 = 0;
    var_r27 = (u8 *) &sp10;
    var_r21 = 1;
}
// PARK-NOTE 2026-08-30: the `var_r30_3 = -var_r30_3 - !M2C_CARRY` is m2c's
// mangled render of a 64-bit NEGATE (want: srawi r30,r0,31; subfic r31,r31,0;
// subfze r30,r30), not a subfc/subfe subtract. Only fixable via full s64
// rebuild of this 5188B function — out of batch scope. The `subf r21,r27,r3`
// at +0xa8c is a plain 32-bit subtract (no borrow). Stays parked.
// RE-TRIAGE 2026-08-30: isolated recipe VERIFIED byte-exact — `s64 x =
// (s64)v; if (x < 0) { x = -x; }` emits exactly mr/srawi/cmpwi/bge/li
// 0x2d/subfic/subfze/stb (negate stays IN-PLACE in the live pair regs).
// All split-var emulations (0-l / -h-(l!=0)) emit neg/subf instead — only
// a true s64 variable reproduces subfic/subfze. Grafted as an s64 round-trip
// at this site: masked score 29->60/1297 (2.2%->4.6%, downstream regalloc
// cascade aligns +31 insns) but the negate site ITSELF still mismatches
// (round-trip forces temps r9-r12 + 8 shuffle insns vs want's in-place
// r30:r31) and the object grew 24B. KEPT as best-match. The real fix
// requires converting the ENTIRE format state machine to one s64 var so the
// pair stays live through the negate (full rebuild, same wall as before).
// fn_8026D288: same recipe, graft REGRESSED (42->27) — reverted there.