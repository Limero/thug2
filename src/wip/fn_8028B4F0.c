// WIP DRAFT (non-matching) — hand-written from retail disassembly + mwcc iteration.
// family=gxtev range=0x8028B4F0-0x8028B564 size=116B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Identity: GXSetTevKColor(GXTevKColorID id, GXColor color) — GXTev.o color trio #3.
// VERDICT: PARKED 13.8% (mwcc_verify: DIFF 25/29 words, size 116B exact).
// K variant: sets the 4-bit constant field 8 at bit 20 of BOTH data words
// (retail emits rlwinm rX,rX,0,12,7 clear + oris rX,rX,0x80 — reproduced by
// the explicit `(data & ~0x00F00000) | 0x800000`; the SET_REG_FIELD(4,20,8)
// intrinsic form emits a shifted rlwimi instead and does NOT match), then
// 24-bit merges. Only TWO FIFO writes (no BG triplicate).
// Same scheduler coin-flip as siblings (docs/parkings/gx-tev-color-family.md
// + 19); register assignment differs from retail throughout (r5/r9 vs r0/r5
// for the first loads). Tried: intrinsic form, mask+or form, reorderings.
// Promotion needs mwcc + dolphin gx/os includes; no .data/.sdata2 sections.
#include "types.h"
#include "qb_constants.h"
#include <dolphin/gx.h>
#include <dolphin/os.h>

#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>

#ifdef SET_REG_FIELD
#undef SET_REG_FIELD
#endif
#define SET_REG_FIELD(line, reg, size, shift, val) \
do { \
    ASSERTMSGLINE(line, ((u32)(val) & ~((1 << (size)) - 1)) == 0, "GX Internal: Register field out of range"); \
    (reg) = ((u32)__rlwimi((u32)(reg), (val), (shift), 32 - (shift) - (size), 31 - (shift))); \
} while (0)

#ifndef CHECK_GXBEGIN
#define CHECK_GXBEGIN(line, name) ASSERTMSGLINE(line, !__GXinBegin, "'" name "' is not allowed between GXBegin/GXEnd")
#endif

#ifndef __GXinBegin
extern u8 __GXinBegin;
#endif

#ifndef GX_WRITE_RAS_REG
#define GX_WRITE_RAS_REG(value) \
do { \
    GX_WRITE_U8(0x61); \
    GX_WRITE_U32(value); \
} while (0)
#endif

void GXSetTevKColor(GXTevKColorID id, GXColor color) {
    u32 data;
    u32 regRA;
    u32 regBG;

    CHECK_GXBEGIN(780, "GXSetTevKColor");

    data = color.a << 12;
    SET_REG_FIELD(785, data, 8, 0, color.r);
    data = (data & ~QB_UNKNOWN_0x00F00000) | 0x800000;
    regRA = (0xE0 + id * 2) << 24;
    SET_REG_FIELD(787, regRA, 24, 0, data);

    data = color.g << 12;
    SET_REG_FIELD(790, data, 8, 0, color.b);
    data = (data & ~QB_UNKNOWN_0x00F00000) | 0x800000;
    regBG = (0xE1 + id * 2) << 24;
    SET_REG_FIELD(792, regBG, 24, 0, data);

    GX_WRITE_RAS_REG(regRA);
    GX_WRITE_RAS_REG(regBG);

    gx->bpSentNot = 0;
}
