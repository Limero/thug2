// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001EA14-0x8001EC60 (588B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* Single register-write function pointer, dereferenced afresh at every call. */
extern char lbl_80300280[];
/* Rotating 0..7 slot counter. */
extern s32 lbl_80300254;
/* 8 pairs of s32, indexed by the counter. */
typedef struct { s32 f0; s32 f1; } reg_pair_t;
extern reg_pair_t lbl_80300214[];
/* 8-byte table: sub-field selector, shifted left by 5. */
extern u8 lbl_803002D8[];
/* 0x40-byte register-lane table; arg13 is a byte OFFSET added to its address. */
extern u8 lbl_803002A0[];
extern u8 lbl_803002A8[];
extern u8 lbl_803002B0[];
extern u8 lbl_803002B8[];
extern u8 lbl_803002C0[];
extern u8 lbl_803002C8[];
/* .rodata2 float pool: 32.0f and 16.0f. */
extern f32 lbl_802911D8;
extern f32 lbl_802911DC;

void fn_8001EA14(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                 s32 arg6, s32 arg7, s32 arg_sp8, u8 arg_spC, u8 arg_sp10,
                 s32 arg_sp14, s32 arg_sp18,
                 f32 farg0, f32 farg1, f32 farg2) {
    volatile double _dummy;
    volatile double _dummy2;
    s32 var_r0;
    s32 var_r0_2;

    /* 1st word: field/block selectors + the low 9 bits of farg2 * 32.0f. */
    ((s32 (*)(s32)) *(s32 *) lbl_80300280)(
        (arg4 | (arg5 << 2)) |
        (arg_sp8 == 1 ? 0x10 : 0) |
        (lbl_803002D8[arg7] << 5) |
        (arg_sp10 == 0 ? 0x100 : 0) |
        ((((s32) (farg2 * lbl_802911D8)) << 9) & 0x1FE00) |
        (arg_sp14 << 19) |
        (arg_spC << 21) |
        ((s32) *(u8 *) ((s32) arg_sp18 + (s32) lbl_803002A0) << 24));

    /* 2nd word: two 8-bit fields of farg0/farg1 * 16.0f. */
    ((s32 (*)(s32)) *(s32 *) lbl_80300280)(
        ((s32) (farg0 * lbl_802911DC) & 0xFF) |
        (((s32) (farg1 * lbl_802911DC) << 8) & 0xFF00) |
        ((s32) *(u8 *) ((s32) arg_sp18 + (s32) lbl_803002A8) << 24));

    /* 3rd word: three range fields. */
    ((void (*)(s32)) *(s32 *) lbl_80300280)(
        (arg1 - 1) | ((arg2 - 1) << 10) | (arg3 << 20) |
        ((s32) *(u8 *) ((s32) arg_sp18 + (s32) lbl_803002B0) << 24));

    /* 4th word: half of the current slot, plus the 0xD8000 register tag. */
    ((s32 (*)(s32)) *(s32 *) lbl_80300280)(
        0xD0000 | 0x8000 |
        ((u32) (lbl_80300214[lbl_80300254].f0) >> 5) |
        ((s32) *(u8 *) ((s32) arg_sp18 + (s32) lbl_803002B8) << 24));

    /* 5th word: the other half, only if the value is below the 0xFFFFF cap. */
    var_r0_2 = lbl_80300214[lbl_80300254].f1;
    if ((u32) var_r0_2 <= 0xFFFFFU) {
        ((s32 (*)(s32)) *(s32 *) lbl_80300280)(
            0xD0000 | 0x8000 | ((u32) var_r0_2 >> 5) |
            ((s32) *(u8 *) ((s32) arg_sp18 + (s32) lbl_803002C0) << 24));
    }

    lbl_80300254 = (lbl_80300254 + 1) & 7;

    /* 6th word: the address, pre-tagged with the 0x80000000 bit. */
    var_r0 = ((arg0 + 0x80000000) >> 5) |
        ((s32) *(u8 *) ((s32) arg_sp18 + (s32) lbl_803002C8) << 24);
    ((s32 (*)(s32)) *(s32 *) lbl_80300280)(var_r0);
}
