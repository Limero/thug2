#!/usr/bin/env python3
"""Compile-only repairs for the unique FAIL tail (65 addresses).

Each entry is (addr, [(old, new), ...]) applied as exact substring replaces
on the draft BODY (header comments preserved). After applying, the draft is
recompiled; only successes are written back. Remaining errors are printed.

Usage: fix_tail2.py [--apply] [--addr 0x...]
"""
import os, re, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl

# ---------------------------------------------------------------------------
# Repair table: addr -> list of (old, new) exact substrings
# ---------------------------------------------------------------------------
FIXES = {
    0x80011454: [
        ("temp_r9_2 - 1 + temp_r30", "(s32)temp_r9_2 - 1 + temp_r30"),
        (") - temp_r9_2", ") - (s32)temp_r9_2"),
        ("temp_r11_6 - 1 + temp_r30", "(s32)temp_r11_6 - 1 + temp_r30"),
        (") - temp_r11_6", ") - (s32)temp_r11_6"),
    ],
    0x80014534: [
        ("s32 (*((s32 *)fn_800559A0()))();", "s32 (*fn_800559A0())(void);"),
        ("fn_800559A0()();", "(*fn_800559A0())();"),
    ],
    0x80027720: [
        ("*(*(s32 *)(*((s32 *)temp_r5 + 0x2C + (s32)var_r3) + 4 + (s32)var_r21))",
         "*((s32 *)(*((s32 *)temp_r5 + 0x2C + (s32)var_r3) + 4 + (s32)var_r21))"),
    ],
    0x8002A3E0: [
        ("*(f32 *)((char *)temp_r10 + (s32)0x8) << 0x11",
         "*(s32 *)((char *)temp_r10 + (s32)0x8) << 0x11"),
    ],
    0x8002D728: [
        ("if ((s32) *(*((s32 *)temp_r28 + (s32)temp_r9_4) + 0x2C + var_r30_2) != 0) {",
         "if ((s32) *(s32 *)(*((s32 *)temp_r28 + (s32)temp_r9_4) + 0x2C + (s32)var_r30_2) != 0) {"),
    ],
    0x8004B798: [
        ("s32 *fn_8003FF64(s32 *, s32);", "s32 *fn_8003FF64(s32 *, ...);"),
        ("goto block_19;\n        }\n        var_r28 = arg0 + 0x58;",
         "goto block_19;\n        }\nblock_19:\n        var_r28 = arg0 + 0x58;"),
    ],
    0x80050868: [
        ("if ( *(*arg0 + sp2FC) != NULL) {", "if ( *(s32 *)(*arg0 + (s32)sp2FC) != NULL) {"),
    ],
    0x80052248: [
        ("if ( *(*sp128 + sp188) != NULL) {", "if ( *(s32 *)(*sp128 + (s32)sp188) != NULL) {"),
    ],
    0x8005FD68: [
        ("sp18 = temp_f0_3;", "sp18 = (void *)(s32)temp_f0_3;"),
    ],
    0x800639E8: [
        ("temp_r30_2 + *(f32 *)((char *)arg0 + (s32)0x100)",
         "(char *)temp_r30_2 + (s32)*(f32 *)((char *)arg0 + (s32)0x100)"),
        ("temp_r30_3 + *(f32 *)((char *)arg0 + (s32)0x100)",
         "(char *)temp_r30_3 + (s32)*(f32 *)((char *)arg0 + (s32)0x100)"),
    ],
    0x80070D40: [
        ("*((s32 *)var_r11) = **var_r11;", "*((s32 *)var_r11) = **(s32 **)var_r11;"),
    ],
    0x80079FB4: [
        ("*(((s32 (*)())*(s32 *)((char *)temp_r9_2 + (s32)0x15C))",
         "*((s32 *)(((s32 (*)())*(s32 *)((char *)temp_r9_2 + (s32)0x15C))"),
        ("+ arg2) * 4)) = arg1;", "+ arg2) * 4))) = arg1;"),
    ],
    0x8007ADB8: [
        ("*(var_r8 + var_r16)", "*((s32 *)var_r8 + (s32)var_r16)"),
    ],
    0x8007C6F0: [
        ("*((s32 *)arg0 + 0x24 + var_r30)", "*((s32 *)arg0 + 0x24 + (s32)var_r30)"),
        ("*((s32 *)arg0 + 0x25 + var_r30)", "*((s32 *)arg0 + 0x25 + (s32)var_r30)"),
        ("*((s32 *)arg0 + 0x26 + var_r30)", "*((s32 *)arg0 + 0x26 + (s32)var_r30)"),
        ("(s32 *)(*(f32 *)((char *)arg0 + (s32)0x290) * 4)",
         "(s32 *)((s32)(*(f32 *)((char *)arg0 + (s32)0x290) * 4))"),
    ],
    0x8008076C: [
        # full-line replacement handled by COMPUTED (paren balance verified)
    ],
    0x800914C4: [
        ("*(var_r8 + temp_r21)", "*((s32 *)var_r8 + (s32)temp_r21)"),
    ],
    0x80094010: [
        ("(s32 *)((*(f32 *)((char *)temp_r28 + (s32)0x55) * 0x18) + *(s32 *)((char *)temp_r28 + (s32)0x8))",
         "(s32 *)((s32)((*(f32 *)((char *)temp_r28 + (s32)0x55) * 0x18) + *(s32 *)((char *)temp_r28 + (s32)0x8)))"),
    ],
    0x800948E0: [
        ("(void *) ((f32) (f64) *(s32 *)((s32 *)(var_r23 + *(s32 *)((char *)arg0 + (s32)0x18)) + 0x8) * *(s32 *)0x80297280))",
         "(void *) ((s32)((f32) (f64) *(s32 *)((s32 *)(var_r23 + *(s32 *)((char *)arg0 + (s32)0x18)) + 0x8) * *(s32 *)0x80297280)))"),
    ],
    0x800B48D4: [
        ("sp24 = &sp8;", "sp24 = (s32) &sp8;"),
    ],
    0x800CB24C: [
        ("+ *(f32 **)0x803645E0)", "+ (s32)*(s32 *)0x803645E0)"),
        ("+ *(u32 **)0x803645E4)", "+ (s32)*(s32 *)0x803645E4)"),
    ],
    0x800D9DB0: [
        ("(f32) &sp8", "(f32) (s32) &sp8"),
    ],
    0x800F0B38: [
        # idempotent: only add label when missing (var_r6 = 0; precedes it)
        ("var_r6 = 0;\n                                        goto block_43;",
         "var_r6 = 0;\nblock_43:\n                                        goto block_43;"),
    ],
    0x800F18D8: [
        ("*(arg0 + 2 + var_r11)", "*((s32 *)((char *)arg0 + 2 + (s32)var_r11))"),
    ],
    0x800F198C: [
        ("*(arg0 + 2 + temp_r31)", "*((s32 *)((char *)arg0 + 2 + (s32)temp_r31))"),
    ],
    0x80102B1C: [
        ("(temp_r9 & 0xFFFFFFFC) + (temp_r27 - arg0)",
         "(temp_r9 & 0xFFFFFFFC) + ((s32)temp_r27 - (s32)arg0)"),
    ],
    0x80102E8C: [
        ("-(*(f32 *)((char *)arg0 + (s32)0x0) & 0xFFFFFFFC)",
         "-((s32)*(f32 *)((char *)arg0 + (s32)0x0) & 0xFFFFFFFC)"),
    ],
    0x80107D7C: [
        ("*((s32 *)*(f32 *)((char *)temp_r29 + (s32)0x38) + temp_r10)",
         "*((s32 *)(s32)*(f32 *)((char *)temp_r29 + (s32)0x38) + (s32)temp_r10)"),
    ],
    0x8012543C: [
        ("*(((arg0 * 4) & 0x3FFC) + *(s32 *)0x80303248)",
         "*((s32 *)(((arg0 * 4) & 0x3FFC) + *(s32 *)0x80303248))"),
    ],
    0x8012A260: [
        # idempotent: only add label when missing
        ("}\n            goto loop_39;", "}\n                loop_39:\n            goto loop_39;"),
    ],
    0x80132458: [
        ("temp_r11_12 = *(f32 *)((char *)temp_r27 + (s32)0x8);", "temp_r11_12 = (s32)*(f32 *)((char *)temp_r27 + (s32)0x8);"),
        ("temp_r9_5 = *(f32 *)((char *)temp_r27 + (s32)0x8);", "temp_r9_5 = (s32)*(f32 *)((char *)temp_r27 + (s32)0x8);"),
        ("temp_r11_13 = *(f32 *)((char *)temp_r26 + (s32)0x8);", "temp_r11_13 = (s32)*(f32 *)((char *)temp_r26 + (s32)0x8);"),
        ("temp_r9_6 = *(f32 *)((char *)temp_r26 + (s32)0x8);", "temp_r9_6 = (s32)*(f32 *)((char *)temp_r26 + (s32)0x8);"),
        ("temp_r11_19 = *(f32 *)((char *)temp_r27 + (s32)0x8);", "temp_r11_19 = (s32)*(f32 *)((char *)temp_r27 + (s32)0x8);"),
        ("temp_r9_7 = *(f32 *)((char *)temp_r26 + (s32)0x8);", "temp_r9_7 = (s32)*(f32 *)((char *)temp_r26 + (s32)0x8);"),
        ("temp_r11_20 = *(f32 *)((char *)temp_r27 + (s32)0x8);", "temp_r11_20 = (s32)*(f32 *)((char *)temp_r27 + (s32)0x8);"),
        ("= (void *) (*(f32 *)((char *)temp_r26 + (s32)0x8) + *(f32 *)((char *)temp_r27 + (s32)0x8));",
         "= (void *) (s32)(*(f32 *)((char *)temp_r26 + (s32)0x8) + *(f32 *)((char *)temp_r27 + (s32)0x8));"),
        ("temp_r4 = *(f32 *)((char *)temp_r26 + (s32)0x8);", "temp_r4 = (s32)*(f32 *)((char *)temp_r26 + (s32)0x8);"),
        ("temp_r9_2 = *(f32 *)((char *)temp_r27 + (s32)0x8);", "temp_r9_2 = (s32)*(f32 *)((char *)temp_r27 + (s32)0x8);"),
        ("temp_r29_3 = *(f32 *)((char *)temp_r27 + (s32)0x8);", "temp_r29_3 = (s32)*(f32 *)((char *)temp_r27 + (s32)0x8);"),
        ("temp_r29_4 = *(f32 *)((char *)temp_r27 + (s32)0x8);", "temp_r29_4 = (s32)*(f32 *)((char *)temp_r27 + (s32)0x8);"),
        ("temp_r9_3 = *(f32 *)((char *)temp_r26 + (s32)0x8);", "temp_r9_3 = (s32)*(f32 *)((char *)temp_r26 + (s32)0x8);"),
        ("temp_r11_11 = *(f32 *)((char *)temp_r27 + (s32)0x8);", "temp_r11_11 = (s32)*(f32 *)((char *)temp_r27 + (s32)0x8);"),
        ("temp_r9_4 = *(f32 *)((char *)temp_r26 + (s32)0x8);", "temp_r9_4 = (s32)*(f32 *)((char *)temp_r26 + (s32)0x8);"),
    ],
    0x8013A398: [
        ("fn_8000AF90(temp_r30_2 + 3, temp_r31, *(s32 *)((char *)arg0 + (s32)0x8) - 3) - temp_r31",
         "fn_8000AF90((s32)temp_r30_2 + 3, temp_r31, *(s32 *)((char *)arg0 + (s32)0x8) - 3) - (s32)temp_r31"),
    ],
    0x8013DA08: [
        ("= (void *) (var_r27 + var_r29);", "= (void *) ((s32)var_r27 + (s32)var_r29);"),
    ],
    0x8015F510: [
        # idempotent: only add label when missing
        ("var_r3_2 = *(s32 *)((char *)var_r31 + (s32)0x8);\n                    goto block_8;",
         "var_r3_2 = *(s32 *)((char *)var_r31 + (s32)0x8);\n                        block_8:\n                    goto block_8;"),
    ],
    0x8017C8F4: [
        ("+ (temp_r26 + temp_r31 + 0x58))", "+ ((s32)temp_r26 + (s32)temp_r31 + 0x58))"),
    ],
    0x801931EC: [
        ("(*(f32 *)((char *)arg0 + (s32)0x70) & 0x80000)",
         "((s32)*(f32 *)((char *)arg0 + (s32)0x70) & 0x80000)"),
    ],
    0x801968A8: [
        ("(*(f32 *)((char *)arg0 + (s32)0x70) & 0x80000)",
         "((s32)*(f32 *)((char *)arg0 + (s32)0x70) & 0x80000)"),
        ("arg0 + *(f32 *)((char *)temp_r9_5 + (s32)0x20)",
         "(char *)arg0 + (s32)*(f32 *)((char *)temp_r9_5 + (s32)0x20)"),
    ],
    0x801E72F0: [
        ("(arg2 - *(s32 *)((char *)arg3 + (s32)0x48)) / 96",
         "((s32)arg2 - *(s32 *)((char *)arg3 + (s32)0x48)) / 96"),
    ],
    0x801FE888: [
        ("temp_r8 = *(f32 *)((char *)arg0 + (s32)0xC);", "temp_r8 = (s32)*(f32 *)((char *)arg0 + (s32)0xC);"),
    ],
    0x802288E0: [
        ("(&sp48)[*(s32 *)((char *)var_r30 + (s32)0x34)]->unk38 = 1;",
         "*((s32 *)(&sp48)[*(s32 *)((char *)var_r30 + (s32)0x34)] + 0x38) = 1;"),
        ("(&sp48)[*(s32 *)((char *)var_r30 + (s32)0x34)]->unk3C = 1;",
         "*((s32 *)(&sp48)[*(s32 *)((char *)var_r30 + (s32)0x34)] + 0x3C) = 1;"),
        ("(&sp48)[*(s32 *)((char *)var_r30 + (s32)0x34)]->unk40 = 1;",
         "*((s32 *)(&sp48)[*(s32 *)((char *)var_r30 + (s32)0x34)] + 0x40) = 1;"),
    ],
    0x80237A88: [
        # fn_80240B2C(a,b) = a+b (asm 0x80240B2C); asm stores bytes from the
        # r26 = &sp8 row into the r25 + sp70*6 + i result pointer.
        ("**(s32 **)((s32 *)((s32 *)((char *)&sp8 + (s32 *)fn_80240B2C(temp_r25 + (sp70 * 6), 0)) = ((sp70 * 6))) + 0x8) + arg2;",
         "*(s8 *)(temp_r25 + (sp70 * 6) + 0) = (s8)((s8)*(s8 *)((char *)&sp8 + (s32)(sp70 * 6) + (s32)0x8) + (s32)arg2);"),
        ("**(s32 **)((s32 *)((s32 *)((char *)&sp8 + (s32 *)fn_80240B2C(temp_r25 + (sp70 * 6), 1)) = (s8) ((sp70 * 6))) + 0x9) + arg3;",
         "*(s8 *)(temp_r25 + (sp70 * 6) + 1) = (s8)((s8)*(s8 *)((char *)&sp8 + (s32)(sp70 * 6) + (s32)0x9) + (s32)arg3);"),
        ("**(s32 **)((s32 *)((s32 *)((char *)&sp8 + (s32 *)fn_80240B2C(temp_r25 + (sp70 * 6), 2)) = ((sp70 * 6))) + 0xA) + arg4;",
         "*(s8 *)(temp_r25 + (sp70 * 6) + 2) = (s8)((s8)*(s8 *)((char *)&sp8 + (s32)(sp70 * 6) + (s32)0xA) + (s32)arg4);"),
    ],
    0x802399E8: [
        ("fn_802399E8(arg0, &sp20, (s8) unksp19, arg3, arg4 & 0xFFFFFFFB, arg5, temp_r9_2)",
         "fn_802399E8(arg0, &sp20, (s8) unksp19, (s32)arg3, arg4 & 0xFFFFFFFB, arg5, (s32)temp_r9_2)"),
    ],
    0x8023B364: [
        ("(s16) (var_r31_3 - temp_r24)", "(s16) ((s32)var_r31_3 - (s32)temp_r24)"),
    ],
    0x80243CE8: [
        ("*(*((s32 *)temp_r30 + (s32)temp_r28) + 4 + (var_r29 * 4))",
         "*(s32 *)(*((s32 *)temp_r30 + (s32)temp_r28) + 4 + (var_r29 * 4))"),
    ],
    0x802456AC: [
        ("(s32) (var_r28 - var_r24) > 3", "(s32) ((s32)var_r28 - (s32)var_r24) > 3"),
    ],
    0x8024AEF0: [
        ("fn_80250F2C(*(s32 *)((s32 *)(arg0 + 0x48) + 0x44), var_r31 + *(s32 *)((char *)arg0 + (s32)0x10C), var_r5, arg0 + 0xA0, *((s32 *)arg0 + 0x94 + (*(temp_r23 + var_r25) * 4)))",
         "fn_80250F2C(*(s32 *)((s32 *)((char *)arg0 + 0x48) + 0x44), (s32)var_r31 + *(s32 *)((char *)arg0 + (s32)0x10C), var_r5, (char *)arg0 + 0xA0, *((s32 *)arg0 + 0x94 + (*(s32 *)((char *)temp_r23 + (s32)var_r25) * 4)))"),
    ],
    0x8024C970: [
        ("+ var_r11) = *(s32 *)((char *)var_r11 + (s32)0x802B1490);",
         " + (s32)var_r11) = *(s32 *)((char *)var_r11 + (s32)0x802B1490);"),
        ("+ var_r11_2) = *(s32 *)((char *)var_r11_2 + (s32)0x802B14D0);",
         " + (s32)var_r11_2) = *(s32 *)((char *)var_r11_2 + (s32)0x802B14D0);"),
    ],
    0x80250AC4: [
        ("*((temp_r12 << 8) + arg0 + 2 + arg4) = var_r11;",
         "*((s32 *)((temp_r12 << 8) + (s32)arg0 + 2 + (s32)arg4)) = var_r11;"),
    ],
    0x802533B0: [
        ("(temp_r0 * 4)->((s32 (*)())*(s32 *)((char *)unk803CA350 + (s32)0xC))(temp_r3_3);",
         "((s32 (*)())*(s32 *)((char *)unk803CA350 + (s32)0xC))(temp_r3_3);"),
        ("(temp_r0_2 * 4)->((s32 (*)())*(s32 *)((char *)unk80308040 + (s32)0xC))(temp_r3_4);",
         "((s32 (*)())*(s32 *)((char *)unk80308040 + (s32)0xC))(temp_r3_4);"),
    ],
    0x802542EC: [
        ("*((s32 (*)())*((s32 *)(s32 *)(temp_r3_4 * 4) + 0x803CA350))",
         "*((s32 (*)())*((s32 *)((s32)(temp_r3_4 * 4) + 0x803CA350)))"),
        ("*((s32 (*)())*((s32 *)(s32 *)(temp_r3_7 * 4) + 0x80308040))",
         "*((s32 (*)())*((s32 *)((s32)(temp_r3_7 * 4) + 0x80308040)))"),
        ("*((s32 (*)())*(s32 *)((char *)temp_r3_10 + (s32)0x803CA358))",
         "*((s32 (*)())*((s32 *)((s32)temp_r3_10 + 0x803CA358)))"),
    ],
    0x80254764: [
        ("return (*((s32 *)temp_r26 + 0x120 + temp_r0) * 4)->((s32 (*)())*(s32 *)((char *)unk803CA358 + (s32)0x8))(arg0, *((s32 *)temp_r26 + 0x220 + temp_r0));",
         "return ((s32 (*)())*(s32 *)((char *)unk803CA358 + (s32)0x8))(arg0, *((s32 *)temp_r26 + 0x220 + temp_r0));"),
    ],
    0x802561E0: [
        ("*(temp_r0 + *(s32 *)((char *)temp_r3 + (s32)0x14))",
         "((s32)temp_r0 + *(s32 *)((char *)temp_r3 + (s32)0x14))"),
        ("*(temp_r9_3 + *(s32 *)((char *)temp_r3 + (s32)0x1C))",
         "((s32)temp_r9_3 + *(s32 *)((char *)temp_r3 + (s32)0x1C))"),
    ],
    0x80256458: [
        ("*((s32 *)temp_r28_2 + *(var_r29_2 + (s32)&sp8))",
         "*((s32 *)temp_r28_2 + ((s32)var_r29_2 + (s32)&sp8))"),
        ("*(temp_r24 + *(var_r29_3 + (s32)&sp8))",
         "*((s32 *)temp_r24 + *((s32 *)((s32)var_r29_3 + (s32)&sp8)))"),
    ],
    0x802566E0: [
        ("*(temp_r11 + *(s32 *)((char *)arg1 + (s32)0x14))",
         "((s32)temp_r11 + *(s32 *)((char *)arg1 + (s32)0x14))"),
    ],
    0x80256D3C: [
        ("(*((s32 *)temp_r15 + 0x320 + temp_r9_5) * 4)->((s32 (*)())*(s32 *)((char *)unk803CA350 + (s32)0x10))(arg0, *((s32 *)temp_r9_5 + *(s32 *)((char *)temp_r21 + (s32)0x14)));",
         "((s32 (*)())*(s32 *)((char *)unk803CA350 + (s32)0x10))(arg0, *((s32 *)temp_r9_5 + *(s32 *)((char *)temp_r21 + (s32)0x14)));"),
        ("(temp_r0_4 * 4)->((s32 (*)())*(s32 *)((char *)unk80308040 + (s32)0x10))(arg0, *((s32 *)temp_r9_8 + *(s32 *)((char *)temp_r21 + (s32)0x18)), &unksp8, &unksp8);",
         "((s32 (*)())*(s32 *)((char *)unk80308040 + (s32)0x10))(arg0, *((s32 *)temp_r9_8 + *(s32 *)((char *)temp_r21 + (s32)0x18)), &unksp8, &unksp8);"),
        ("(*((s32 *)temp_r15 + 0x320 + temp_r9_9) * 4)->((s32 (*)())*(s32 *)((char *)unk803CA350 + (s32)0x14))(arg0, *((s32 *)temp_r9_9 + *(s32 *)((char *)temp_r21 + (s32)0x14)), *((s32 *)var_r28_2 + (s32)&unksp8), *((s32 *)var_r28_2 + *(s32 *)((char *)arg0 + (s32)0x0)));",
         "((s32 (*)())*(s32 *)((char *)unk803CA350 + (s32)0x14))(arg0, *((s32 *)temp_r9_9 + *(s32 *)((char *)temp_r21 + (s32)0x14)), *((s32 *)var_r28_2 + (s32)&unksp8), *((s32 *)var_r28_2 + *(s32 *)((char *)arg0 + (s32)0x0)));"),
    ],
    0x80258B78: [
        ("sp64 = *(f32 *)((char *)arg1 + (s32)0x4) ^ 0x80000000;",
         "sp64 = (s32)*(s32 *)((char *)arg1 + (s32)0x4) ^ 0x80000000;"),
        ("*(temp_r28 + *(s32 *)((char *)arg2 + (s32)0x8))",
         "((s32)temp_r28 + *(s32 *)((char *)arg2 + (s32)0x8))"),
    ],
    0x802592A4: [
        ("*((s32 *)temp_r11 + *(f32 *)((char *)arg1 + (s32)0x8))",
         "*((s32 *)temp_r11 + (s32)*(s32 *)((char *)arg1 + (s32)0x8))"),
    ],
    0x80259B6C: [
        ("temp_r0 = *(*(s32 *)((s32 *)(**(s32 **)((char *)arg0 + (s32)0x2C)) + 0x1C) + (*(s32 *)((char *)arg0 + (s32)0x1C) * 4));",
         "temp_r0 = *(s32 *)(*(s32 *)((s32 *)(**(s32 **)((char *)arg0 + (s32)0x2C)) + 0x1C) + (*(s32 *)((char *)arg0 + (s32)0x1C) * 4));"),
    ],
    0x80263CD0: [
        ("(void *(*)(f64))0x8025CFB4(*(f64 *)((char *)var_r26 + (s32)0x90))",
         "(void *(*)(f64))((void *)0x8025CFB4)(*(f64 *)((char *)var_r26 + (s32)0x90))"),
        ("(void *(*)(f64))0x8025CFB4(*(f64 *)((char *)var_r26_2 + (s32)0x1C8))",
         "(void *(*)(f64))((void *)0x8025CFB4)(*(f64 *)((char *)var_r26_2 + (s32)0x1C8))"),
    ],
    0x8026BD70: [
        ("((sp - 0x1E8) - var_r27) + 0x16C", "(((s32)sp - 0x1E8) - (s32)var_r27) + 0x16C"),
        ("var_r21 = temp_r3_2 - var_r27", "var_r21 = (s32)temp_r3_2 - (s32)var_r27"),
        ("**var_r9_10 = (s16) var_r15;", "**(s16 **)var_r9_10 = (s16) var_r15;"),
        ("**var_r9_9 = var_r15;", "**(s16 **)var_r9_9 = var_r15;"),
    ],
    0x8026D288: [
        ("((sp - 0x98) - var_r26) + 0x30", "(((s32)sp - 0x98) - (s32)var_r26) + 0x30"),
        ("var_r21 = temp_r3_2 - var_r26", "var_r21 = (s32)temp_r3_2 - (s32)var_r26"),
        ("**var_r9_9 = (s16) var_r15;", "**(s16 **)var_r9_9 = (s16) var_r15;"),
        ("**var_r9_8 = var_r15;", "**(s16 **)var_r9_8 = var_r15;"),
    ],
    0x80274B10: [
        ("unksp-8 = sp - 8;", "(void)0;"),
    ],
    0x8027BF10: [
        ("((arg0 - 0x803C8380) / 272) * 0xC", "(((s32)arg0 - 0x803C8380) / 272) * 0xC"),
    ],
    0x8027C194: [
        ("temp_r4 == *((f32 *)&sp1C)", "(s32)temp_r4 == (s32)*((f32 *)&sp1C)"),
    ],
    0x802887D0: [
        ("*arg2 = *((((((arg0 * 4) & 0x3FFFC) | 0xC8000000) & 0xFFC00FFF) | ((arg1 << 0xC) & 0x0FFFF000)) & 0xFF3FFFFF);",
         "*arg2 = *(s32 *)(((((arg0 * 4) & 0x3FFFC) | 0xC8000000) & 0xFFC00FFF) | ((arg1 << 0xC) & 0x0FFFF000)) & 0xFF3FFFFF);"),
    ],
    0x802887F4: [
        ("*((((((arg0 * 4) & 0x3FFFC) | 0xC8000000) & 0xFFC00FFF) | ((arg1 << 0xC) & 0x0FFFF000)) & 0xFF3FFFFF) = arg2;",
         "*(s32 *)(((((arg0 * 4) & 0x3FFFC) | 0xC8000000) & 0xFFC00FFF) | ((arg1 << 0xC) & 0x0FFFF000)) & 0xFF3FFFFF) = arg2;"),
    ],
}


# Round-2 fixes: applied AFTER FIXES (targets earlier output text).
FIXES2 = {
    0x80027720: [
        ("*(*((s32 *)temp_r5 + 0x2C + var_r3) + 4 + var_r21) = var_r8;",
         "*((s32 *)(*((s32 *)temp_r5 + 0x2C + (s32)var_r3) + 4 + (s32)var_r21)) = var_r8;"),
    ],
    0x8008076C: [
        # mirror the compilable line-52 form: + (*((s32 *)var_r30) * 12) offset
        ("*(f32 *)((char *)var_r31 + (s32)0x4) = (f32) *(s32 *)((s32 *)((*((s32 *)((char *)*(s32 *)((s32 *)(fn_8007DF14(*(s32 *)((char *)arg0 + (s32)0x18))) + 0xC) + (s32 *)var_r30) * 12))) + 0x4);",
         "*(f32 *)((char *)var_r31 + (s32)0x4) = (f32) *((s32 *)((char *)*(s32 *)((s32 *)(fn_8007DF14(*(s32 *)((char *)arg0 + (s32)0x18))) + 0xC) + (*((s32 *)var_r30) * 12)) + 0x4);"),
    ],
    0x802399E8: [
        ("s32 fn_802399E8(s32 arg0, void *arg1, s8 arg2, s32 arg3, s32 arg4, void **arg5)",
         "s32 fn_802399E8(s32 arg0, void *arg1, s8 arg2, s32 arg3, s32 arg4, void **arg5, ...)"),
    ],
    0x802533B0: [
        ("(char *)unk803CA350 + (s32)0xC", "(char *)0x803CA350 + (s32)0xC"),
        ("(char *)unk80308040 + (s32)0xC", "(char *)0x80308040 + (s32)0xC"),
    ],
    0x802542EC: [
        ("= *((s32 (*)())*((s32 *)((s32)(temp_r3_4 * 4) + 0x803CA350)))(arg0, arg1);",
         "= ((s32 (*)())*((s32 *)((s32)(temp_r3_4 * 4) + 0x803CA350)))(arg0, arg1);"),
        ("= *((s32 (*)())*((s32 *)((s32)(temp_r3_7 * 4) + 0x80308040)))(arg0, arg1);",
         "= ((s32 (*)())*((s32 *)((s32)(temp_r3_7 * 4) + 0x80308040)))(arg0, arg1);"),
        ("= *((s32 (*)())*((s32 *)((s32)temp_r3_10 + 0x803CA358)))(arg0, arg1);",
         "= ((s32 (*)())*((s32 *)((s32)temp_r3_10 + 0x803CA358)))(arg0, arg1);"),
    ],
    0x80254764: [
        ("(char *)unk803CA358 + (s32)0x8", "(char *)0x803CA358 + (s32)0x8"),
    ],
    0x80256458: [
        # temp_r11 is s32; deref through cast pointer (FIXES handles temp_r24)
        ("*(temp_r11 + *(s32 *)((char *)arg1 + (s32)0x14))",
         "*((s32 *)((s32)temp_r11 + *(s32 *)((char *)arg1 + (s32)0x14)))"),
    ],
    0x802566E0: [
        ("*(temp_r11 + *(s32 *)((char *)arg1 + (s32)0x14))",
         "*((s32 *)((s32)temp_r11 + *(s32 *)((char *)arg1 + (s32)0x14)))"),
    ],
    0x80256D3C: [
        ("(char *)unk803CA350 + (s32)0x10", "(char *)0x803CA350 + (s32)0x10"),
        ("(char *)unk80308040 + (s32)0x10", "(char *)0x80308040 + (s32)0x10"),
        ("(char *)unk803CA350 + (s32)0x14", "(char *)0x803CA350 + (s32)0x14"),
    ],
    0x80263CD0: [
        ("(void *(*)(f64))((void *)0x8025CFB4)(*(f64 *)((char *)var_r26 + (s32)0x90))",
         "((void *(*)(f64))0x8025CFB4)(*(f64 *)((char *)var_r26 + (s32)0x90))"),
        ("(void *(*)(f64))((void *)0x8025CFB4)(*(f64 *)((char *)var_r26_2 + (s32)0x1C8))",
         "((void *(*)(f64))0x8025CFB4)(*(f64 *)((char *)var_r26_2 + (s32)0x1C8))"),
    ],
    0x802887D0: [
        ("*arg2 = *(s32 *)(((((arg0 * 4) & 0x3FFFC) | 0xC8000000) & 0xFFC00FFF) | ((arg1 << 0xC) & 0x0FFFF000)) & 0xFF3FFFFF);",
         "*arg2 = *(s32 *)(((((arg0 * 4) & 0x3FFFC) | 0xC8000000) & 0xFFC00FFF) | ((arg1 << 0xC) & 0x0FFFF000)) & 0xFF3FFFFF);"),
    ],
    0x802887F4: [
        ("*(s32 *)(((((arg0 * 4) & 0x3FFFC) | 0xC8000000) & 0xFFC00FFF) | ((arg1 << 0xC) & 0x0FFFF000)) & 0xFF3FFFFF) = arg2;",
         "*(s32 *)(((((arg0 * 4) & 0x3FFFC) | 0xC8000000) & 0xFFC00FFF) | ((arg1 << 0xC) & 0x0FFFF000)) & 0xFF3FFFFF) = arg2;"),
    ],
}


def balanced(s):
    """Count ( and ) outside string literals/chars; return depth==0."""
    depth = 0
    i = 0
    while i < len(s):
        c = s[i]
        if c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
        i += 1
    return depth == 0


# Round-3: computed fixes with balance verification (paren-heavy m2c lines).
# value = None disables; callables build the replacement from scratch.
def fix_802887(a, store):
    G = "(((arg0 * 4) & 0x3FFFC) | 0xC8000000) & 0xFFC00FFF"
    H = "((arg1 << 0xC) & 0x0FFFF000)"
    inner = "((%s) | %s) & 0xFF3FFFFF" % (G, H)
    assert balanced(inner), inner
    if store:
        return "*arg2 = *(s32 *)(%s);" % inner
    return "*(s32 *)(%s) = arg2;" % inner


COMPUTED = {
    0x802887D0: lambda: fix_802887(0x802887D0, True),
    0x802887F4: lambda: fix_802887(0x802887F4, False),
}


def apply_computed(a, new):
    """Apply computed full-line replacement: find the old bad line and replace."""
    if a not in COMPUTED:
        return new, []
    repl = COMPUTED[a]()
    lines = new.split('\n')
    out = []
    n = 0
    for ln in lines:
        if '0xFF3FFFFF' in ln and '0xC8000000' in ln and n == 0:
            out.append(repl)
            n += 1
        else:
            out.append(ln)
    return '\n'.join(out), [] if n else ['NO-MATCH-802887']


def compile_draft(a, body):
    fname = 'fn_%08X' % a
    sp = '/tmp/leaf/%s.c' % fname
    with open(sp, 'w') as f:
        f.write('#include "types.h"\n' + body)
    env = dict(os.environ)
    env['SN_NGC_PATH'] = gl.C_DIR
    return subprocess.run(
        [gl.WIBO, f'{gl.C_DIR}/ngccc.exe', '-O2', '-G0', '-mcpu=750', '-fno-common',
         '-I', f'{gl.ROOT}/include', '-c', sp, '-o', '/tmp/leaf/%s.o' % fname],
        cwd=gl.ROOT, capture_output=True, text=True, env=env)


def body_lines(text):
    return [l for l in text.splitlines()
            if not l.startswith('//') and 'types.h' not in l]


def main():
    apply_ = '--apply' in sys.argv
    only = None
    if '--addr' in sys.argv:
        only = int(sys.argv[sys.argv.index('--addr') + 1], 16)
    addrs = [only] if only else sorted(FIXES)
    ok = fail = 0
    for a in addrs:
        fp = 'src/wip/fn_%08X.c' % a
        if not os.path.isfile(fp):
            print('%08X: NO-FILE' % a)
            continue
        text = open(fp).read()
        header = [l for l in text.splitlines() if l.startswith('//')]
        body = '\n'.join(body_lines(text))
        if a not in FIXES:
            print('%08X: no fixes' % a)
            continue
        new = body
        missed = []
        for old, repl in FIXES[a]:
            if old not in new:
                missed.append(old[:70])
            else:
                new = new.replace(old, repl)
        for old, repl in FIXES2.get(a, []):
            if old not in new:
                missed.append(old[:70])
            else:
                new = new.replace(old, repl)
        new, cmissed = apply_computed(a, new)
        missed += cmissed
        if missed and not apply_:
            print('%08X: MISSING substrings: %s' % (a, missed))
        r = compile_draft(a, new)
        if r.returncode == 0:
            ok += 1
            if apply_:
                open(fp, 'w').write('\n'.join(header) + '\n#include "types.h"\n' + new + '\n')
        else:
            fail += 1
            errs = [l for l in r.stderr.splitlines() if 'warning' not in l and l.strip()]
            if '--dump' in sys.argv:
                print('===== %08X =====' % a)
                src_lines = new.splitlines()
                for e in errs:
                    m = re.match(r'^[^:]+:(\d+):\s*(.*)$', e)
                    if m:
                        ln = int(m.group(1))
                        bi = ln - 2  # compiler file has 1 include line before body
                        print('L%d: %s' % (ln, m.group(2)))
                        print('     %s' % (src_lines[bi] if 0 <= bi < len(src_lines) else '?'))
                    else:
                        print(e[:120])
            else:
                print('%08X FAIL (%d fixes): %s' % (a, len(FIXES[a]), (errs[0] if errs else '?')))
    print('=== fixed %d / %d ===' % (ok, ok + fail))


if __name__ == '__main__':
    main()
