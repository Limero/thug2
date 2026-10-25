// WIP DRAFT (non-matching) — GX TEV colour register upload (S10 form).
// family=hand range=0x8028B47C-0x8028B4F0 size=116B
// FLAG: -G256
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Packs the two TEN (11-bit signed) register payloads from the colour
// argument, builds the 0xE0/0xE1 RAS command words and pushes them down the
// write-gather pipe as four 0x61-tagged writes, then clears gx->bpSentNot.
//
// The object is 32 bytes longer than want because two emissions are missing:
//
//  1. The `(payload & ~0x7FF) | (field & 0x7FF)` insert comes out as a
//     clear-mask plus a separate `or` instead of the single fused
//     rlwimi retail uses.  Retail's code for the same expression is exactly
//     one rotate-mask and one rotate-insert, so the source must be the SDK's
//     SET_REG_FIELD spelling; writing the mask pair by hand (both the
//     `(x & m) | (y & n)` and the union-bitfield spellings) is measured to
//     produce the two-instruction form under this compiler.
//  2. The pipe base is materialised as `lis 0xCC00 / ori 0x8000` here, while
//     retail keeps the HIGH half in the register and folds the low half into
//     a -0x8000 displacement.  Retail therefore reaches the pipe through a
//     symbol-like address expression, not a bare integer constant; the two
//     GX_WRITE_* macros below are the deref form and give the ori form.
//
// The small-data flag is load-bearing: retail reads the gx pointer through
// r13 (`-0x6218(r13)`), which only happens with small data enabled.  With the
// project's default -G0 the whole access shape is wrong, so every function in
// this SDK region needs -G256 (or -msdata=eabi -G256) before it is scored.
#include "types.h"

typedef struct {
    s16 r, g, b, a;
} GXColorS10;

typedef struct {
    u16 pad0;
    u16 bpSentNot;
} GXData;

extern GXData *const gx;

void fn_8028B47C(u32 id, GXColorS10 *color) {
    u32 data;
    u32 regRA;
    u32 regBG;

    data = (color->a & 0x7FF) << 12;
    data = (data & ~0x7FF) | (color->r & 0x7FF);
    regRA = ((0xE0 + id * 2) << 24) | data;
    data = (color->g & 0x7FF) << 12;
    data = (data & ~0x7FF) | (color->b & 0x7FF);
    regBG = ((0xE1 + id * 2) << 24) | data;

    *(volatile u8 *)0xCC008000 = 0x61;
    *(volatile u32 *)0xCC008000 = regRA;
    *(volatile u8 *)0xCC008000 = 0x61;
    *(volatile u32 *)0xCC008000 = regBG;
    *(volatile u8 *)0xCC008000 = 0x61;
    *(volatile u32 *)0xCC008000 = regBG;
    *(volatile u8 *)0xCC008000 = 0x61;
    *(volatile u32 *)0xCC008000 = regBG;

    gx->bpSentNot = 0;
}
