#include "types.h"
#include "qb_constants.h"
// WIP DRAFT (non-matching) — best-known hand reconstruction (2026-08-26 re-audit)
// family=gx-chan range=0x80289BD8-0x80289CCC size=244B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED (55.7% word / EXACT 244B size, 61/61 insns): docs/parkings/18-gxlight-chan-regalloc.md.
// Byte-twin of GXSetChanAmbColor (see fn_80289AE4.c for the full parking note):
// same __rlwimi-intrinsic swapped-operand form, matColor 0xB0/0xB4 + XF base
// 0x100C instead of ambColor 0xA8/0xAC + 0x100A. Verified to the identical
// residual (exact 61-insn size; register-name renames + one [mr]/[rlwimi]
// transposition per COLOR case) via
// python3 <scratch> 0x80289BD8 <this file>.
//
// Same global.h/__rlwimi intrinsic shadowing caveat as fn_80289AE4.c: the
// minimal prelude stands in for the SDK headers until that is resolved.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { u8 r, g, b, a; } GXColor;

typedef enum {
    GX_COLOR0 = 0,
    GX_COLOR1 = 1,
    GX_ALPHA0 = 2,
    GX_ALPHA1 = 3,
    GX_COLOR0A0 = 4,
    GX_COLOR1A1 = 5
} GXChannelID;

/* GXData layout stub: only the fields GXSetChanMatColor touches.
   Real offsets: bpSentNot 0x002 (u16), matColor 0x0B0 (see symbols.txt/GXInit.h). */
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;      /* 0x002 */
    u8 pad1[0xA4];
    u32 ambColor[2];    /* 0x0A8 */
    u32 matColor[2];    /* 0x0B0 */
} GXData;

extern GXData* const gx;

void GXSetChanMatColor(GXChannelID channel, GXColor* color)
{
    u32 colorID;
    u32 rgb;
    u32 reg;

    switch (channel) {
    case GX_COLOR0:
        rgb = gx->matColor[GX_COLOR0];
        reg = __rlwimi((*(u32*)color) & ~0xff, rgb, 0, 24, 31);
        colorID = GX_COLOR0;
        break;
    case GX_COLOR1:
        rgb = gx->matColor[GX_COLOR1];
        reg = __rlwimi((*(u32*)color) & ~0xff, rgb, 0, 24, 31);
        colorID = GX_COLOR1;
        break;
    case GX_ALPHA0:
        reg = color->a;
        __rlwimi(reg, gx->matColor[GX_COLOR0], 0, 0, 23);
        colorID = GX_COLOR0;
        break;
    case GX_ALPHA1:
        reg = color->a;
        __rlwimi(reg, gx->matColor[GX_COLOR1], 0, 0, 23);
        colorID = GX_COLOR1;
        break;
    case GX_COLOR0A0:
        reg = *(u32*)color;
        colorID = GX_COLOR0;
        break;
    case GX_COLOR1A1:
        reg = *(u32*)color;
        colorID = GX_COLOR1;
        break;
    default:
        return;
    }

    *(volatile u8*)QB_UNKNOWN_0xCC008000 = 0x10;
    *(volatile u32*)QB_UNKNOWN_0xCC008000 = 0x1000 + (colorID + 12);
    *(volatile u32*)QB_UNKNOWN_0xCC008000 = reg;
    gx->bpSentNot = 1;
    gx->matColor[colorID] = reg;
}
