// UPDATED 2026-08-29: WA-split applied (f78c call-spec pattern).
// WIP DRAFT (non-matching) — identification pass 2026-08-26 (group 8)
// family=vfiprintf range=0x8026D288-0x8026E57C size=4852B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ============================================================================
// IDENTIFICATION: vfprintf-family engine, INTEGER-ONLY twin
// ("__svfiprintf_r") — int fn(FILE *f /*arg1*/, const char *fmt /*arg2*/,
//                              va_list ap /*arg3*/).
// Same engine as fn_8026BD70 (see that header for the full anatomy) minus
// the floating-point conversions: no %e/E/f/g/G arm, no dtoa/log10 calls,
// no float consts. Compiled from a SEPARATE translation unit — proof: it
// owns DUPLICATED rodata literals (lbl_802B2120 spaces / 2130 zeros /
// 2140 "0123456789abcdef" / 2154 "(null)" / 215C "0123456789ABCDEF" /
// 2170 "bug in vfprintf: bad base") and its own copy of the writer helper
// (fn_8026D1B4 vs BD70's fn_8026BBC4; both 0xD4).
// Dispatch: fn_8026BC98 scans fmt for [eEfgG]/L and routes float-free
// formats HERE. Callers of the dispatcher: the vsnprintf-family wrappers
// at 0x8026A000/0x8026A044.
// Callees:
//   fn_8026EEF0(ptrA=&lbl_803CA420[0], &out_slot, fmt, *(u32*)&lbl_803CA40C,
//               &count_slot) -> segment scan length (>0 = '%' found)
//   fn_8026D1B4(fd, buf, len, flag)  writer (13 sites, NO crclr -> proto)
//   memcpy                           6 sites ALL with want-side crclr cr1eq
//                                    -> MUST stay unprototyped
//   fn_802745E0/fn_802740FC          u64 div/mod by 10 — want keeps crclr
//                                    -> stay unprototyped
//   strlen/memchr                    libc, no crclr -> prototyped
//
// WHY PARKED (structural):
//  1. SDA addressing: scanner-table words loaded via `lwz disp(r13)`
//     (.sdata 0x803CA420/0x803CA40C); game-code -G0 objects can never emit
//     that form (see fn_8026F55C.c park note for the msdata-flag probe).
//  2. 1213 instructions of compare-tree switch engine + ~19 output blocks;
//     byte-exactness is a multi-session hand rebuild even with flags solved.
//  Body below = m2c skeleton with data references repaired (fake
//  saved_reg_r13 statics -> real lbl_ externs; bare literals -> lbl_
//  forms; protos added per want's crclr map). Documents control flow,
//  does NOT match.
// ============================================================================
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 6.0% ([30]rev->5.4% [24]rev->5.9% [3]desc->6.0%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 memcpy(s32, s32, s32);
s32 fn_802745E0(void *, void *, void *, void *);

/* ---- data symbols referenced by the engine ---- */
extern char lbl_802B2120[];  /* rodata2: 16 spaces (this TU's copy)       */
extern char lbl_802B2130[];  /* rodata2: 16 zeros                         */
extern char lbl_802B2140[];  /* "0123456789abcdef"                        */
extern char lbl_802B2154[];  /* "(null)"                                  */
extern char lbl_802B215C[];  /* "0123456789ABCDEF"                        */
extern char lbl_802B2170[];  /* "bug in vfprintf: bad base"               */
extern s32 lbl_803CA420;  /* .sdata: scanner table A (first word used) */
extern s32 lbl_803CA40C;  /* .sdata: scanner table B (first word = 1)  */

/* ---- callees (prototypes per want's crclr map) ---- */
extern s32 fn_8026EEF0(Unk_C7387A53 *, s32 *, void *, s32, void *);
extern s32 fn_8026D1B4(s32, u8 *, u32, s32);      /* writer, 13 sites     */
extern u32 strlen(const char *);
extern void *memchr(const void *, s32, u32);
/* NOTE: memcpy / fn_802745E0 / fn_802740FC deliberately UNPROTOTYPED —
 * want emits `crclr cr1eq` before every one of those bl sites. */
extern char lbl_802B2140[];
extern char lbl_802B215C[];
static s32 sp44;
static s32 sp48;
static s32 M2C_CARRY = 0;

s32 fn_8026D288(CStruct *arg1, u8 *arg2, Unk_8B4EE1D5 *arg3) {
s32 fs_t;
    s32 *sp48;
    s32 *sp44;
    s32 sp40;
    s16 sp3C;
    s32 sp38;
    s32 sp34;
    u8 sp30;                                        
    s8 sp8;                                         
    s16 temp_r0_4;
    s16 var_r0;
    s32 *var_r10;
    s32 *var_r3;
    s32 *var_r3_2;
    s32 *var_r3_3;
    s32 *var_r3_4;
    s32 *var_r3_5;
    s32 *var_r3_6;
    s32 *var_r8;
    s32 *var_r9;
    s32 *var_r9_11;
    s32 *var_r9_12;
    s32 *var_r9_14;
    s32 *var_r9_15;
    s32 *var_r9_17;
    s32 *var_r9_18;
    s32 *var_r9_19;
    s32 *var_r9_4;
    s32 *var_r9_5;
    s32 *var_r9_8;
    s32 *var_r9_9;
    s32 temp_cr0_eq;
    s32 temp_r0_3;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r0_2;
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
    s32 var_r9_2;
    s32 var_r9_6;
    s8 temp_r11_6;
    s8 var_r27;
    s8 var_r9_10;
    s8 var_r9_13;
    s8 var_r9_16;
    s8 var_r9_3;
    s8 var_r9_7;
    u32 temp_r10;
    u32 temp_r10_2;
    u32 temp_r4;
    u32 var_r31;
    u64 temp_ret;
    u8 *temp_r26;
    u8 *var_r22;
    u8 *var_r26;
    u8 temp_r0;
    u8 temp_r0_2;
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

    sp38 = 0;
    sp48 = &sp38;
    sp44 = &sp34;
    var_r22 = arg2;
    var_r15 = 0;
loop_1:
    temp_r26 = var_r22;
loop_2:
    temp_r3 = fn_8026EEF0(lbl_803CA420, sp44, var_r22, lbl_803CA40C, sp48);
    if (temp_r3 > 0) {
        var_r22 = &var_r22[temp_r3];
        if (sp34 == 0x25) {
            var_r22 -= 1;
        } else {
            goto loop_2;
        }
    }
    temp_r31 = (s32)var_r22 - (s32)var_r22;
    if (temp_r31 != 0) {
        if (arg1->unk0xC & 0x200) {
            memcpy(arg1->unk0x0, temp_r26, temp_r31);
            arg1->unk0x0 = (void *) (arg1->unk0x0 + temp_r31);
        } else {
            if ((s32) arg1->unk0xC == 0) {
                *(s32 *)((char *)arg1 + (s32)0xE) = 1;
            }
            fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), temp_r26, temp_r31, 0);
        }
        var_r15 += temp_r31;
    }
    if (temp_r3 > 0) {
        var_r16 = 0;
        var_r22 += 1;
        sp30 = 0;
        var_r24 = 0;
        var_r23 = 0;
loop_14:
        var_r25 = -1;
loop_15:
        temp_r0 = *((s32 *)var_r22);
        var_r22 += 1;
        var_r27 = (s8) temp_r0;
loop_16:
        if (var_r27 != 0x63) {
            if (var_r27 <= 0x63) {
                switch (var_r27) {                  
                case 0x20:                          
                    if ((s32) sp30 == 0) {
                    case 0x2B:                      
                        sp30 = var_r27;
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
                    var_r27 = (s8) temp_r0_2;
                    if (var_r27 == 0x2A) {
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
                    if ((u32) (var_r27 - 0x30) <= 9U) {
                        do {
                            temp_r11_3 = *((s32 *)var_r22);
                            var_r22 += 1;
                            var_r30 = (var_r30 * 0xA) - 0x30 + var_r27;
                            var_r27 = (s8) temp_r11_3;
                        } while ((u32) (var_r27 - 0x30) <= 9U);
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
                        var_r30_2 = (var_r30_2 * 0xA) - 0x30 + var_r27;
                        var_r27 = (s8) temp_r11_4;
                    } while ((u32) (var_r27 - 0x30) <= 9U);
                    var_r16 = var_r30_2;
                    goto loop_16;
                case 0x44:                          
                    var_r24 |= 0x10;
                    goto block_101;
                case 0x4F:                          
                    var_r24 |= 0x10;
                    goto block_162;
                case 0x55:                          
                    var_r24 |= 0x10;
                    goto block_215;
                case 0x58:                          
                    var_r9_2 = (s32)lbl_802B215C;
                    goto block_248;
                }
            } else {
                switch (var_r27) {                  
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
                case 0x64:                          
block_101:
                    if (var_r24 & 0x20) {
                        temp_r9 = arg3->unk0x0;
                        if ((u32) ((s8) temp_r9 + 2) <= 8U) {
                            if (temp_r9 & 1) {
                                arg3->unk0x0 = (u8) (temp_r9 + 1);
                            }
                            temp_r9_2 = arg3->unk0x0;
                            arg3->unk0x0 = (u8) (temp_r9_2 + 2);
                            var_r3_2 = arg3->unk0x8 + ((s8) temp_r9_2 * 4);
                        } else {
                            if ((s8) temp_r9 <= 7) {
                                var_r3_2 = arg3->unk0x4;
                                arg3->unk0x0 = 8U;
                            } else {
                                var_r3_2 = arg3->unk0x4;
                            }
                            arg3->unk0x4 = (s32 *) (var_r3_2 + 8);
                        }
                        var_r30_3 = ((CStruct *)var_r3_2)->unk0x0;
                        var_r31 = ((CStruct *)var_r3_2)->unk0x4;
                    } else {
                        if (var_r24 & 0x10) {
                            var_r9_3 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_3 + 1) > 8U) {
                                if (var_r9_3 <= 7) {
                                    var_r9_4 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    goto block_127;
                                }
                                goto block_128;
                            }
                            goto block_124;
                            goto block_129;
                        }
                        if (var_r24 & 0x40) {
                            temp_r11_5 = arg3->unk0x0;
                            if ((u32) ((s8) temp_r11_5 + 1) <= 8U) {
                                var_r9_5 = arg3->unk0x8 + ((s8) temp_r11_5 * 4);
                                arg3->unk0x0 = (u8) (temp_r11_5 + 1);
                            } else {
                                if ((s8) temp_r11_5 <= 7) {
                                    var_r9_5 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    var_r9_5 = arg3->unk0x4;
                                }
                                arg3->unk0x4 = (s32 *) (var_r9_5 + 4);
                            }
                            var_r0 = *(s32 *)((char *)var_r9_5 + (s32)0x2);
                        } else {
                            var_r9_3 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_3 + 1) <= 8U) {
block_124:
                                var_r9_4 = arg3->unk0x8 + (var_r9_3 * 4);
                                arg3->unk0x0 = (u8) (arg3->unk0x0 + 1);
                            } else {
                                if (var_r9_3 <= 7) {
                                    var_r9_4 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
block_127:
                                    var_r9_4 = arg3->unk0x4;
                                }
block_128:
                                arg3->unk0x4 = (s32 *) (var_r9_4 + 4);
                            }
block_129:
                            var_r0 = (s16) *((s32 *)var_r9_4);
                        }
                        var_r31 = (u32) var_r0;
                        var_r30_3 = var_r0 >> 0x1F;
                    }
                    if (var_r30_3 < 0) {
                        var_r31 = 0 - var_r31;
                        var_r30_3 = -var_r30_3 - !M2C_CARRY;
                        sp30 = 0x2D;
                    }
                    var_r9_6 = 1;
block_282:
                    var_r23 = var_r25;
                    0;
                    if (var_r23 >= 0) {
                        var_r24 &= QB_UNKNOWN_0xFFFFFF7F;
                    }
                    var_r26 = &sp30;
                    temp_cr0_eq = (var_r30_3 | var_r31) == 0;
                    if ((temp_cr0_eq == 0) || (temp_cr0_eq == 0)) {
                        if (var_r9_6 != 1) {
                            if ((u32) var_r9_6 >= 1U) {
                                if (var_r9_6 != 2) {
                                    var_r21 = strlen((u8 *)lbl_802B2170);
                                    var_r26 = (u8 *)lbl_802B2170;
                                } else {
                                    do {
                                        temp_r10 = (var_r30_3 << 0x1C) | (var_r31 >> 4U);
                                        temp_r0_3 = var_r31 & 0xF;
                                        var_r30_3 = (s32) ((u32) var_r30_3 >> 4U);
                                        var_r31 = temp_r10;
                                        var_r26 -= 1;
                                        *(u8 *)((char *)var_r26 - 0x1) = (u8) *((s32 *)sp40 + (s32)temp_r0_3);
                                    } while ((var_r30_3 | var_r31) != 0);
                                    goto block_302;
                                }
                            } else {
                                do {
                                    temp_r10_2 = (var_r30_3 << 0x1D) | (var_r31 >> 3U);
                                    temp_r11_6 = (var_r31 & 7) + 0x30;
                                    var_r30_3 = (s32) ((u32) var_r30_3 >> 3U);
                                    var_r31 = temp_r10_2;
                                    var_r26 -= 1;
                                    *(u8 *)((char *)var_r26 - 0x1) = temp_r11_6;
                                } while ((var_r30_3 | var_r31) != 0);
                                if ((var_r24 & 1) && (temp_r11_6 != 0x30)) {
                                    var_r26 -= 1;
                                    *(u8 *)((char *)var_r26 - 0x1) = 0x30;
                                }
                                goto block_302;
                            }
                        } else {
loop_295:
                            if ((u32) var_r30_3 > 0U) {
block_294:
                                var_r26 -= 1;
                                *(u8 *)((char *)var_r26 - 0x1) = (s8) ((u32) fn_802745E0((u64) var_r30_3, var_r31, 0, 0xA) + 0x30);
                                fs_t = fn_802740FC((u64) var_r30_3, var_r31, 0, 0xA);
                                temp_r4 = (u32) temp_ret;
                                temp_ret = fs_t;
                                var_r30_3 = temp_ret;
                                var_r31 = temp_r4;
                                goto loop_295;
                            }
                            if ((var_r30_3 == 0) && (var_r31 > 9U)) {
                                goto block_294;
                            }
                            var_r26 -= 1;
                            *(u8 *)((char *)var_r26 - 0x1) = (s8) (var_r31 + 0x30);
                            goto block_302;
                        }
                    } else {
block_302:
                        var_r21 = ((s32)&sp30 - 0) - (s32)var_r26;
                    }
                    goto block_305;
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
                        temp_r11_8->unk0x4 = var_r15;
                        temp_r11_8->unk0x0 = (s32) (var_r15 >> 0x1F);
                        temp_r11_8 = *((s32 *)var_r8);
                    } else {
                        if (var_r24 & 0x10) {
                            var_r9_7 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_7 + 1) > 8U) {
                                if (var_r9_7 <= 7) {
                                    var_r9_8 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    goto block_158;
                                }
                                goto block_159;
                            }
                            goto block_155;
                            goto block_160;
                        }
                        if (var_r24 & 0x40) {
                            temp_r11_9 = arg3->unk0x0;
                            if ((u32) ((s8) temp_r11_9 + 1) <= 8U) {
                                var_r9_9 = arg3->unk0x8 + ((s8) temp_r11_9 * 4);
                                arg3->unk0x0 = (u8) (temp_r11_9 + 1);
                            } else {
                                if ((s8) temp_r11_9 <= 7) {
                                    var_r9_9 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    var_r9_9 = arg3->unk0x4;
                                }
                                arg3->unk0x4 = (s32 *) (var_r9_9 + 4);
                            }
                            **(s16 **)var_r9_9 = (s16) var_r15;
                        } else {
                            var_r9_7 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_7 + 1) <= 8U) {
block_155:
                                var_r9_8 = arg3->unk0x8 + (var_r9_7 * 4);
                                arg3->unk0x0 = (u8) (arg3->unk0x0 + 1);
                            } else {
                                if (var_r9_7 <= 7) {
                                    var_r9_8 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
block_158:
                                    var_r9_8 = arg3->unk0x4;
                                }
block_159:
                                arg3->unk0x4 = (s32 *) (var_r9_8 + 4);
                            }
block_160:
                            **(s16 **)var_r9_8 = var_r15;
                        }
                    }
                    goto loop_1;
                case 0x6F:                          
block_162:
                    if (var_r24 & 0x20) {
                        temp_r9_3 = arg3->unk0x0;
                        if ((u32) ((s8) temp_r9_3 + 2) <= 8U) {
                            if (temp_r9_3 & 1) {
                                arg3->unk0x0 = (u8) (temp_r9_3 + 1);
                            }
                            temp_r9_4 = arg3->unk0x0;
                            arg3->unk0x0 = (u8) (temp_r9_4 + 2);
                            var_r3_3 = arg3->unk0x8 + ((s8) temp_r9_4 * 4);
                        } else {
                            if ((s8) temp_r9_3 <= 7) {
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
                            var_r9_10 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_10 + 1) > 8U) {
                                if (var_r9_10 <= 7) {
                                    var_r9_11 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    goto block_188;
                                }
                                goto block_189;
                            }
                            goto block_185;
                            goto block_190;
                        }
                        if (var_r24 & 0x40) {
                            temp_r11_10 = arg3->unk0x0;
                            if ((u32) ((s8) temp_r11_10 + 1) <= 8U) {
                                var_r9_12 = arg3->unk0x8 + ((s8) temp_r11_10 * 4);
                                arg3->unk0x0 = (u8) (temp_r11_10 + 1);
                            } else {
                                if ((s8) temp_r11_10 <= 7) {
                                    var_r9_12 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    var_r9_12 = arg3->unk0x4;
                                }
                                arg3->unk0x4 = (s32 *) (var_r9_12 + 4);
                            }
                            var_r31 = (u32) *(u32 *)((char *)var_r9_12 + (s32)0x2);
                        } else {
                            var_r9_10 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_10 + 1) <= 8U) {
block_185:
                                var_r9_11 = arg3->unk0x8 + (var_r9_10 * 4);
                                arg3->unk0x0 = (u8) (arg3->unk0x0 + 1);
                            } else {
                                if (var_r9_10 <= 7) {
                                    var_r9_11 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
block_188:
                                    var_r9_11 = arg3->unk0x4;
                                }
block_189:
                                arg3->unk0x4 = (s32 *) (var_r9_11 + 4);
                            }
block_190:
                            var_r31 = *((s32 *)var_r9_11);
                        }
                        var_r30_3 = 0;
                    }
                    var_r9_6 = 0;
block_281:
                    sp30 = 0;
                    goto block_282;
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
                    sp40 = (s32)lbl_802B2140;
                    var_r30_3 = 0;
                    var_r9_6 = 2;
                    var_r27 = 0x78;
                    goto block_281;
                case 0x73:                          
                    temp_r11_12 = arg3->unk0x0;
                    if ((u32) ((s8) temp_r11_12 + 1) <= 8U) {
                        var_r3_4 = arg3->unk0x8 + ((s8) temp_r11_12 * 4);
                        arg3->unk0x0 = (u8) (temp_r11_12 + 1);
                    } else {
                        if ((s8) temp_r11_12 <= 7) {
                            var_r3_4 = arg3->unk0x4;
                            arg3->unk0x0 = 8U;
                        } else {
                            var_r3_4 = arg3->unk0x4;
                        }
                        arg3->unk0x4 = (s32 *) (var_r3_4 + 4);
                    }
                    var_r26 = *((s32 *)var_r3_4);
                    if (var_r26 == NULL) {
                        var_r26 = (u8 *)lbl_802B2154;
                    }
                    if (var_r25 >= 0) {
                        temp_r3_2 = memchr(var_r26, 0, var_r25);
                        if ((temp_r3_2 == 0) || (var_r21 = (s32)temp_r3_2 - (s32)var_r26, ((var_r21 > var_r25) != 0))) {
                            var_r21 = var_r25;
                        }
                    } else {
                        var_r21 = strlen(var_r26);
                    }
                    sp30 = 0;
                    goto block_305;
                case 0x75:                          
block_215:
                    if (var_r24 & 0x20) {
                        temp_r9_5 = arg3->unk0x0;
                        if ((u32) ((s8) temp_r9_5 + 2) <= 8U) {
                            if (temp_r9_5 & 1) {
                                arg3->unk0x0 = (u8) (temp_r9_5 + 1);
                            }
                            temp_r9_6 = arg3->unk0x0;
                            arg3->unk0x0 = (u8) (temp_r9_6 + 2);
                            var_r3_5 = arg3->unk0x8 + ((s8) temp_r9_6 * 4);
                        } else {
                            if ((s8) temp_r9_5 <= 7) {
                                var_r3_5 = arg3->unk0x4;
                                arg3->unk0x0 = 8U;
                            } else {
                                var_r3_5 = arg3->unk0x4;
                            }
                            arg3->unk0x4 = (s32 *) (var_r3_5 + 8);
                        }
                        var_r30_3 = ((CStruct *)var_r3_5)->unk0x0;
                        var_r31 = ((CStruct *)var_r3_5)->unk0x4;
                    } else {
                        if (var_r24 & 0x10) {
                            var_r9_13 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_13 + 1) > 8U) {
                                if (var_r9_13 <= 7) {
                                    var_r9_14 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    goto block_241;
                                }
                                goto block_242;
                            }
                            goto block_238;
                            goto block_243;
                        }
                        if (var_r24 & 0x40) {
                            temp_r11_13 = arg3->unk0x0;
                            if ((u32) ((s8) temp_r11_13 + 1) <= 8U) {
                                var_r9_15 = arg3->unk0x8 + ((s8) temp_r11_13 * 4);
                                arg3->unk0x0 = (u8) (temp_r11_13 + 1);
                            } else {
                                if ((s8) temp_r11_13 <= 7) {
                                    var_r9_15 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    var_r9_15 = arg3->unk0x4;
                                }
                                arg3->unk0x4 = (s32 *) (var_r9_15 + 4);
                            }
                            var_r31 = (u32) *(u32 *)((char *)var_r9_15 + (s32)0x2);
                        } else {
                            var_r9_13 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_13 + 1) <= 8U) {
block_238:
                                var_r9_14 = arg3->unk0x8 + (var_r9_13 * 4);
                                arg3->unk0x0 = (u8) (arg3->unk0x0 + 1);
                            } else {
                                if (var_r9_13 <= 7) {
                                    var_r9_14 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
block_241:
                                    var_r9_14 = arg3->unk0x4;
                                }
block_242:
                                arg3->unk0x4 = (s32 *) (var_r9_14 + 4);
                            }
block_243:
                            var_r31 = *((s32 *)var_r9_14);
                        }
                        var_r30_3 = 0;
                    }
                    var_r9_6 = 1;
                    goto block_281;
                case 0x78:                          
                    var_r9_2 = (s32)lbl_802B2140;
block_248:
                    sp40 = var_r9_2;
                    if (var_r24 & 0x20) {
                        temp_r9_7 = arg3->unk0x0;
                        if ((u32) ((s8) temp_r9_7 + 2) <= 8U) {
                            if (temp_r9_7 & 1) {
                                arg3->unk0x0 = (u8) (temp_r9_7 + 1);
                            }
                            temp_r9_8 = arg3->unk0x0;
                            arg3->unk0x0 = (u8) (temp_r9_8 + 2);
                            var_r3_6 = arg3->unk0x8 + ((s8) temp_r9_8 * 4);
                        } else {
                            if ((s8) temp_r9_7 <= 7) {
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
                            var_r9_16 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_16 + 1) > 8U) {
                                if (var_r9_16 <= 7) {
                                    var_r9_17 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    goto block_274;
                                }
                                goto block_275;
                            }
                            goto block_271;
                            goto block_276;
                        }
                        if (var_r24 & 0x40) {
                            temp_r11_14 = arg3->unk0x0;
                            if ((u32) ((s8) temp_r11_14 + 1) <= 8U) {
                                var_r9_18 = arg3->unk0x8 + ((s8) temp_r11_14 * 4);
                                arg3->unk0x0 = (u8) (temp_r11_14 + 1);
                            } else {
                                if ((s8) temp_r11_14 <= 7) {
                                    var_r9_18 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
                                    var_r9_18 = arg3->unk0x4;
                                }
                                arg3->unk0x4 = (s32 *) (var_r9_18 + 4);
                            }
                            var_r31 = (u32) *(u32 *)((char *)var_r9_18 + (s32)0x2);
                        } else {
                            var_r9_16 = (s8) arg3->unk0x0;
                            if ((u32) (var_r9_16 + 1) <= 8U) {
block_271:
                                var_r9_17 = arg3->unk0x8 + (var_r9_16 * 4);
                                arg3->unk0x0 = (u8) (arg3->unk0x0 + 1);
                            } else {
                                if (var_r9_16 <= 7) {
                                    var_r9_17 = arg3->unk0x4;
                                    arg3->unk0x0 = 8U;
                                } else {
block_274:
                                    var_r9_17 = arg3->unk0x4;
                                }
block_275:
                                arg3->unk0x4 = (s32 *) (var_r9_17 + 4);
                            }
block_276:
                            var_r31 = *((s32 *)var_r9_17);
                        }
                        var_r30_3 = 0;
                    }
                    var_r9_6 = 2;
                    if ((var_r24 & 1) && ((var_r30_3 | var_r31) != 0)) {
                        var_r24 |= 2;
                    }
                    goto block_281;
                }
            }
        } else {
            temp_r11_15 = arg3->unk0x0;
            var_r26 = (u8 *) &sp8;
            if ((u32) ((s8) temp_r11_15 + 1) <= 8U) {
                var_r9_19 = arg3->unk0x8 + ((s8) temp_r11_15 * 4);
                arg3->unk0x0 = (u8) (temp_r11_15 + 1);
            } else {
                if ((s8) temp_r11_15 <= 7) {
                    var_r9_19 = arg3->unk0x4;
                    arg3->unk0x0 = 8U;
                } else {
                    var_r9_19 = arg3->unk0x4;
                }
                arg3->unk0x4 = (s32 *) (var_r9_19 + 4);
            }
            sp30 = 0;
            var_r21 = 1;
            sp8 = *(s32 *)((char *)var_r9_19 + (s32)0x3);
block_305:
            var_r25_2 = var_r21;
            if (var_r25_2 < var_r23) {
                var_r25_2 = var_r23;
            }
            if ((s32) sp30 != 0) {
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
                                temp_r11_16->unk0x0 = (s32) ((CStruct *)lbl_802B2120)->unk0x0;
                                temp_r11_16->unk0xC = (s32) ((CStruct *)lbl_802B2120)->unk0xC;
                                temp_r11_16->unk0x4 = (s32) ((CStruct *)lbl_802B2120)->unk0x4;
                                temp_r11_16->unk0x8 = (s32) ((CStruct *)lbl_802B2120)->unk0x8;
                                arg1->unk0x0 = (void *) (*((char *)&arg1->unk0x0) + 0x10);
                            } else {
                                if ((s32) arg1->unk0xC == 0) {
                                    *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                                }
                                fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2120, 0x10, 0);
                            }
                            var_r30_4 -= 0x10;
                        } while (var_r30_4 > 0x10);
                    }
                    if (arg1->unk0xC & 0x200) {
                        memcpy(arg1->unk0x0, (u8 *)lbl_802B2120, var_r30_4);
                        arg1->unk0x0 = (void *) (arg1->unk0x0 + var_r30_4);
                    } else {
                        if ((s32) arg1->unk0xC == 0) {
                            *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                        }
                        fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2120, var_r30_4, 0);
                    }
                }
            }
            if ((s32) sp30 != 0) {
                if (arg1->unk0xC & 0x200) {
                    *(s32 *)(*(s32 *)((char *)((char *)arg1) + 0x0) + 0x0) = sp30;
                    arg1->unk0x0 = (void *) (arg1->unk0x0 + 1);
                } else {
                    if ((s32) arg1->unk0xC == 0) {
                        *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                    }
                    fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), &sp30, 1, 0);
                }
            } else if (var_r24 & 2) {
                temp_r0_4 = (u8) var_r27 | 0x3000;
                sp3C = temp_r0_4;
                if (arg1->unk0xC & 0x200) {
                    *(s32 *)(*(s32 *)((char *)((char *)arg1) + 0x0) + 0x0) = temp_r0_4;
                    arg1->unk0x0 = (void *) (arg1->unk0x0 + 2);
                } else {
                    if ((s32) arg1->unk0xC == 0) {
                        *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                    }
                    fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *) &sp3C, 2, 0);
                }
            }
            if ((s32) (var_r24 & 0x84) == 0x80) {
                var_r30_5 = var_r16 - var_r25_2;
                if (var_r30_5 > 0) {
                    if (var_r30_5 > 0x10) {
                        do {
                            if (arg1->unk0xC & 0x200) {
                                temp_r11_17 = arg1->unk0x0;
                                temp_r11_17->unk0x0 = (s32) ((CStruct *)lbl_802B2130)->unk0x0;
                                temp_r11_17->unk0xC = (s32) ((CStruct *)lbl_802B2130)->unk0xC;
                                temp_r11_17->unk0x4 = (s32) ((CStruct *)lbl_802B2130)->unk0x4;
                                temp_r11_17->unk0x8 = (s32) ((CStruct *)lbl_802B2130)->unk0x8;
                                arg1->unk0x0 = (void *) (*((char *)&arg1->unk0x0) + 0x10);
                            } else {
                                if ((s32) arg1->unk0xC == 0) {
                                    *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                                }
                                fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2130, 0x10, 0);
                            }
                            var_r30_5 -= 0x10;
                        } while (var_r30_5 > 0x10);
                    }
                    if (arg1->unk0xC & 0x200) {
                        memcpy(arg1->unk0x0, (u8 *)lbl_802B2130, var_r30_5);
                        arg1->unk0x0 = (void *) (arg1->unk0x0 + var_r30_5);
                    } else {
                        if ((s32) arg1->unk0xC == 0) {
                            *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                        }
                        fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2130, var_r30_5, 0);
                    }
                }
            }
            var_r30_6 = var_r23 - var_r21;
            if (var_r30_6 > 0) {
                if (var_r30_6 > 0x10) {
                    do {
                        if (arg1->unk0xC & 0x200) {
                            temp_r11_18 = arg1->unk0x0;
                            temp_r11_18->unk0x0 = (s32) ((CStruct *)lbl_802B2130)->unk0x0;
                            temp_r11_18->unk0xC = (s32) ((CStruct *)lbl_802B2130)->unk0xC;
                            temp_r11_18->unk0x4 = (s32) ((CStruct *)lbl_802B2130)->unk0x4;
                            temp_r11_18->unk0x8 = (s32) ((CStruct *)lbl_802B2130)->unk0x8;
                            arg1->unk0x0 = (void *) (*((char *)&arg1->unk0x0) + 0x10);
                        } else {
                            if ((s32) arg1->unk0xC == 0) {
                                *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                            }
                            fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2130, 0x10, 0);
                        }
                        var_r30_6 -= 0x10;
                    } while (var_r30_6 > 0x10);
                }
                if (arg1->unk0xC & 0x200) {
                    memcpy(arg1->unk0x0, (u8 *)lbl_802B2130, var_r30_6);
                    arg1->unk0x0 = (void *) (arg1->unk0x0 + var_r30_6);
                } else {
                    if ((s32) arg1->unk0xC == 0) {
                        *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                    }
                    fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2130, var_r30_6, 0);
                }
            }
            if (arg1->unk0xC & 0x200) {
                memcpy(arg1->unk0x0, var_r26, var_r21);
                arg1->unk0x0 = (void *) (arg1->unk0x0 + var_r21);
            } else {
                if ((s32) arg1->unk0xC == 0) {
                    *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                }
                fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), var_r26, var_r21, 0);
            }
            if (var_r24 & 4) {
                var_r30_7 = var_r16 - var_r25_2;
                if (var_r30_7 > 0) {
                    if (var_r30_7 > 0x10) {
                        do {
                            if (arg1->unk0xC & 0x200) {
                                temp_r11_19 = arg1->unk0x0;
                                temp_r11_19->unk0xC = (s32) ((CStruct *)lbl_802B2120)->unk0xC;
                                temp_r11_19->unk0x8 = (s32) ((CStruct *)lbl_802B2120)->unk0x8;
                                temp_r11_19->unk0x4 = (s32) ((CStruct *)lbl_802B2120)->unk0x4;
                                temp_r11_19->unk0x0 = (s32) ((CStruct *)lbl_802B2120)->unk0x0;
                                arg1->unk0x0 = (void *) (*((char *)&arg1->unk0x0) + 0x10);
                            } else {
                                if ((s32) arg1->unk0xC == 0) {
                                    *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                                }
                                fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2120, 0x10, 0);
                            }
                            var_r30_7 -= 0x10;
                        } while (var_r30_7 > 0x10);
                    }
                    if (arg1->unk0xC & 0x200) {
                        memcpy(arg1->unk0x0, (u8 *)lbl_802B2120, var_r30_7);
                        arg1->unk0x0 = (void *) (arg1->unk0x0 + var_r30_7);
                    } else {
                        if ((s32) arg1->unk0xC == 0) {
                            *(s32 *)((char *)arg1 + (s32)0xE) = 1;
                        }
                        fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), (u8 *)lbl_802B2120, var_r30_7, 0);
                    }
                }
            }
            var_r0_2 = var_r25_2;
            if (var_r0_2 < var_r16) {
                var_r0_2 = var_r16;
            }
            var_r15 += var_r0_2;
            goto loop_1;
        }
    }
    if (!(arg1->unk0xC & 0x200)) {
        fn_8026D1B4(*(s32 *)((char *)arg1 + (s32)0xE), NULL, 0, 1);
    }
    return var_r15;
    
    
    sp8 = var_r27;
    sp30 = 0;
    var_r26 = (u8 *) &sp8;
    var_r21 = 1;
}
// PARK-NOTE 2026-08-30: `var_r30_3 = -var_r30_3 - !M2C_CARRY` = 64-bit NEGATE
// (srawi/subfic/subfze), NOT a u64 subtract. Needs full s64 rebuild of this
// 4852B function; out of batch scope. The `subf` at +0x940 is 32-bit. Parked.
// RE-TRIAGE 2026-08-30: same isolated recipe as fn_8026BD70 (`s64 x =
// (s64)v; if (x<0) x = -x;` is byte-exact in isolation). Grafted the s64
// round-trip here: REGRESSED 42->27/1213 (3.5%->2.2%) — the temp-reg
// shuffling hurt this draft's layout. REVERTED to best-match m2c form.
// Both drafts need the full-s64 conversion of the whole format state
// machine (pair stays live through the negate) to fix the site properly.
// RE-TRIAGE 2026-10-12: vfprintf-engine out of scope (SDA + 1213-insn switch); no body change.
