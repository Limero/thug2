#include "types.h"
#include "qb_constants.h"
// WIP DRAFT (non-matching) — best-known hand reconstruction (2026-08-26 re-audit)
// family=gx-chan range=0x80289AE4-0x80289BD8 size=244B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED (55.7% word / EXACT 244B size, 61/61 insns): docs/parkings/18-gxlight-chan-regalloc.md.
// Regalloc coin-flip wall, re-confirmed 2026-08-26 with a NEW lever beyond the
// doc's attempt list: mwcc's __rlwimi INTRINSIC with bfbb-form swapped operand
// roles — GX_SET_TRUNC(new_color_masked, old_stored, field) instead of the
// tww/tp form that masks the stored reg in place. Winning mix: COLOR cases =
// EXPRESSION form via an rgb temp loaded first (`rgb = gx->..Color[..];
// reg = __rlwimi((*(u32*)color) & ~0xff, rgb, 0, 24, 31);`), ALPHA cases =
// STATEMENT form (`reg = color->a; __rlwimi(reg, .., 0, 0, 23);`), locals
// declared {colorID, rgb, reg}. This reaches EXACT SIZE and reproduces the
// DOL's per-case instruction CLASSES ([rlwinm scratch][merge][mr home] for
// COLOR cases, [lbz home][rlwimi home] for ALPHA, dead default blr before the
// shared tail); residual diffs are register-name assignment (colorID r5/reg r7
// vs got r6/r5-class renames) plus one [mr]/[rlwimi] transposition in the two
// COLOR cases — pure doc-15-class allocator coin flips. All mwcc versions
// 1.0-3.0a5.2 swept on this form (1.3+ fuse harder, 220B/212B); -schedule off
// and -inline noauto do not help. Harness: python3
// <scratch> 0x80289AE4 <this file>.
//
// NOTE on includes: global.h (pulled by every SDK gx header) declares
// "extern int __rlwimi(...)", which SHADOWS mwcc's __rlwimi intrinsic and
// turns each merge into a real call (+frame). Skipping global.h breaks
// GXLight.h, so this draft carries a minimal local prelude instead of the SDK
// headers (same pattern as /tmp smoke-test files). At promotion time the
// _global_h_-guard trick or an intrinsic-safe header edit is needed.
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

/* GXData layout stub: only the fields GXSetChanAmbColor touches.
   Real offsets: bpSentNot 0x002 (u16), ambColor 0x0A8 (see symbols.txt/GXInit.h). */
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;      /* 0x002 */
    u8 pad1[0xA4];
    u32 ambColor[2];    /* 0x0A8 */
    u32 matColor[2];    /* 0x0B0 */
} GXData;

extern GXData* const gx;

void GXSetChanAmbColor(GXChannelID channel, GXColor* color)
{
    u32 colorID;
    u32 rgb;
    u32 reg;

    switch (channel) {
    case GX_COLOR0:
        rgb = gx->ambColor[GX_COLOR0];
        reg = __rlwimi((*(u32*)color) & ~0xff, rgb, 0, 24, 31);
        colorID = GX_COLOR0;
        break;
    case GX_COLOR1:
        rgb = gx->ambColor[GX_COLOR1];
        reg = __rlwimi((*(u32*)color) & ~0xff, rgb, 0, 24, 31);
        colorID = GX_COLOR1;
        break;
    case GX_ALPHA0:
        reg = color->a;
        __rlwimi(reg, gx->ambColor[GX_COLOR0], 0, 0, 23);
        colorID = GX_COLOR0;
        break;
    case GX_ALPHA1:
        reg = color->a;
        __rlwimi(reg, gx->ambColor[GX_COLOR1], 0, 0, 23);
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
    *(volatile u32*)QB_UNKNOWN_0xCC008000 = 0x1000 + (colorID + 10);
    *(volatile u32*)QB_UNKNOWN_0xCC008000 = reg;
    gx->bpSentNot = 1;
    gx->ambColor[colorID] = reg;
}
