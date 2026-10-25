// PARKED 2026-10-03 (a63): DIFF 18.7%  (m2c draft was DIFF 20.0%, but its
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 18.7097% -> 23.8710% per-object flags: - -> -fno-expensive-optimizations
// bytes only lined up by luck: it had the wrong call arity and 32-bit loads
// where the game does byte loads. This body is now instruction-for-
// instruction equivalent to the want except for register allocation and a
// 2-instruction shortfall, 612B vs 620B.)
// reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//              tools/test_wip_drafts.py --addr 0x80258254
// fixed vs m2c (all verified against the disasm):
//   1. fn_80257D7C takes (state, bitindex) - m2c passed 3 args.
//   2. arg1+0x4 is a 32-bit field (lwz/stw); structs.h types it s8, which
//      would give lbz/extsb+stb -> aliased through a local DecState struct.
//   3. arg0+0x1C is a BYTE table (lbz -1 / lbzx), +0x14/+0x20 are word tables.
//   4. bitrev is the classic 4-stage LO/HI pair; the >>8 term needs 0x00FF00FF
//      (masking both terms with BYTE_HI folds the pair and loses 3 insns).
//   5. unprototyped fn_80257D7C made ngccc emit `crclr cr1eq` before both bls
//      (WANT has none) -> added the prototype.
//   6. the "leaf vs internal node" test must be `if (temp_r8 < 0) {split} else
//      {leaf}` so GCC branches bge to the out-of-line leaf block.
// compiler notes (cost me 2 hours, useful for every rlwinm-mask case):
//   * PPC bit 31 is the LSB: rlwinm MB..ME is the LOW mask, so `x & 0x7FFF` is
//     rlwinm(0,17,31) and `(x>>8) & 0xFFFF` is rlwinm(24,16,31). Do NOT read
//     these as big-endian masks - m2c's `>>15`/`>>17` pairs here are correct.
//   * `lis rX, 0xff` materialises 0x00FF0000, so `lis rX,0xff; ori rX,rX,0xff`
//     is 0x00FF00FF (not 0xFFFF) - that is why the byte stage needs two masks.
//   * x*2 emits `add` where the want has `slwi`: use << 1, << 2, << 4.
//   * (and (lshr x C) <contiguous mask>) ALWAYS folds to one rlwinm in both
//     ProDG 3.7 and 3.9.3, so a want with `srwi`+`and 0x00FF00FF` can only be
//     reproduced from a non-contiguous mask.
// remaining diff (all regalloc / layout, no semantic bug left):
//   * 2 insns short overall; the leaf temp wants r8, GOT keeps it in a
//     call-saved reg, and the want hoists `lwz r7,0x1c(r27)` (syms) into the
//     binary-search preheader while GOT loads it in the loop-exit block.
//   * chan pinned to r30 (the only pin; it reproduces hi=r28, lo=r29, chan=r30
//     and buys +1.9%). Pinning r28/r29 explicitly is WORSE (17.4%): ngccc then
//     reuses the pinned reg as scratch for the leaf/`& 0x7FFF` temporaries.
//   * the want's bit-loop is rotated (decrement `addi r30,r30,-1` sits in the
//     LATCH at 0x8025830C, entered by `bgt`) and keeps a second, provably
//     redundant `cmpwi r3,0; bge` on the chan<=1 exit path. A
//     for(;;){call;if(bit>=0)break;if(chan>1){chan--;continue;}break;}
//     makes ngccc hoist that test into the loop (`ble` straight to `li r3,-1`).
//     Next idea: get the redundant test to survive by making the loop's second
//     exit a value GCC cannot range-propagate (e.g. the bit stored through a
//     second variable assigned from the call inside the exit branch).
// WIP DRAFT (non-matching) — fn_80258254: huffman symbol decode step.
// family=m2c range=0x80258254-0x802584C0 size=620B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// FINDINGS (a63):
//  * fn_80257D7C takes (state, bitindex) — the m2c draft's 3-arg call was wrong.
//  * arg1+0x4 (the 1/8 fraction) is read/written 32-bit (lwz/stw); the shared
//    header types it s8, which would emit lbz/extsb + stb.
//  * arg0+0x1C is a BYTE table (lbz -1 / lbzx), +0x14 / +0x20 are word tables.
//  * bitrev: each stage is (t>>k)&LO | (t<<k)&HI with the classic masks, and
//    the >>8 term must use 0x00FF00FF (BYTE_HI on both terms folds the pair).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// qb_constants.h has no BYTE_LO; the bitrev LO/HI pairs are
// 0x00FF00FF/0xFF00FF00, 0x0F0F0F0F/0xF0F0F0F0,
// 0x33333333/0xCCCCCCCC, 0x55555555/0xAAAAAAAA.
#define QB_BITREV_MASK_BYTE_LO     0x00FF00FF

// huffman decode state (arg1) / node table (arg0) as the code really uses them
typedef struct {
    s32 total;  /* 0x00 */
    s32 frac;   /* 0x04 */
    s32 f08;    /* 0x08 */
    s32 count;  /* 0x0C */
} DecState;

typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 *nodes; /* 0x14: word array of internal-node split values */
    s32 f18;
    s8 *syms;   /* 0x1C: byte array of symbol deltas */
    s32 *leaf;  /* 0x20: word array, entry >= 0 -> leaf, else hi/lo split */
    s32 bits;   /* 0x24 */
    s32 chan;   /* 0x28 */
} NodeTab;

// callee prototype: WANT has no `crclr cr1eq` before either call, and an
// unprototyped call makes 3.9.3 emit one (recipes §"spurious crclr cr1eq").
s32 fn_80257D7C(void *state, s32 bit);

// FLAG: -fno-expensive-optimizations
s32 fn_80258254(Unk_2B59CD86 *arg0, Unk_D42E3F3A *arg1) {
    DecState *st = (DecState *)arg1;
    NodeTab *nt = (NodeTab *)arg0;
    s32 temp_r3;
    s32 temp_r3_3;
    u32 temp_r3_4;
    u32 temp_r3_5;
    u32 temp_r3_6;
    u32 temp_r3_7;
    s32 temp_r11;
    s32 var_r28;
    s32 var_r29;
    register s32 var_r30 __asm__("r30") = arg0->unk0x28;

    temp_r3 = fn_80257D7C(arg1, arg0->unk0x24);
    if (temp_r3 >= 0) {
        s32 temp_r8 = nt->leaf[temp_r3];
        if (temp_r8 < 0) {
            var_r28 = arg0->unk0x8 - (temp_r8 & 0x7FFF);
            var_r29 = ((u32)temp_r8 >> 0xFU) & 0x7FFF;
        } else {
            s32 temp_r3_2 = nt->syms[temp_r8 - 1] + st->frac;
            s32 temp_r10 = temp_r3_2;
            if (temp_r3_2 < 0) {
                temp_r10 = temp_r3_2 + 7;
            }
            temp_r10 >>= 3;
            st->frac = temp_r3_2 & 7;
            st->count = st->count + temp_r10;
            st->total = st->total + temp_r10;
            return temp_r8 - 1;
        }
    } else {
        var_r28 = arg0->unk0x8;
        var_r29 = 0;
    }
    for (;;) {
        temp_r3_3 = fn_80257D7C(arg1, var_r30);
        if (temp_r3_3 >= 0) {
            break;
        }
        if (var_r30 > 1) {
            var_r30 -= 1;
            continue;
        }
        break;
    }
    if (temp_r3_3 < 0) {
        return -1;
    }
    temp_r3_4 = ((u32)temp_r3_3 << 0x10) | ((u32)temp_r3_3 >> 0x10U);
    temp_r3_5 = ((temp_r3_4 >> 8U) & QB_BITREV_MASK_BYTE_LO) | ((temp_r3_4 << 8) & QB_BITREV_MASK_BYTE_HI);
    temp_r3_6 = ((temp_r3_5 >> 4U) & QB_BITREV_MASK_NIBBLE_LO) | ((temp_r3_5 << 4) & QB_BITREV_MASK_NIBBLE_HI);
    temp_r3_7 = ((temp_r3_6 >> 2U) & QB_BITREV_MASK_2BIT_LO) | ((temp_r3_6 << 2) & QB_BITREV_MASK_2BIT_HI);
    temp_r3_7 = ((temp_r3_7 >> 1U) & QB_BITREV_MASK_BIT_LO) | ((temp_r3_7 << 1) & QB_BITREV_MASK_BIT_HI);
    {
        s32 var_r10_2 = var_r28 - var_r29;
        s32 temp_r4 = st->frac;
        s32 temp_r6 = st->count;
        s8 *syms = nt->syms;
        if (var_r10_2 > 1) {
            do {
                var_r10_2 >>= 1;
                temp_r11 = (u32)nt->nodes[var_r29 + var_r10_2] < temp_r3_7;
                var_r28 -= var_r10_2 & -temp_r11;
                var_r29 += var_r10_2 & (temp_r11 - 1);
                var_r10_2 = var_r28 - var_r29;
            } while (var_r10_2 > 1);
        }
        {
            s32 temp_r0 = syms[var_r29];
            if (temp_r0 <= var_r30) {
                s32 temp_r11_2 = temp_r0 + temp_r4;
                s32 var_r9 = temp_r11_2;
                if (temp_r11_2 < 0) {
                    var_r9 = temp_r11_2 + 7;
                }
                var_r9 >>= 3;
                st->count = temp_r6 + var_r9;
                st->frac = temp_r11_2 & 7;
                st->total = st->total + var_r9;
                return var_r29;
            }
            {
                s32 temp_r4_2 = var_r30 + temp_r4;
                s32 var_r9_2 = temp_r4_2;
                if (temp_r4_2 < 0) {
                    var_r9_2 = temp_r4_2 + 7;
                }
                var_r9_2 >>= 3;
                st->total = st->total + var_r9_2;
                st->frac = temp_r4_2 & 7;
                st->count = temp_r6 + var_r9_2;
                return -1;
            }
        }
    }
}
