// thug2's GXBump.c is an older SDK revision (pre-Sep-2002) with only 6
// linked functions: the modern IndTex helpers (GXSetIndTexMtx/Order,
// GXSetTevIndWarp/BumpST/BumpXYZ/Repeat, __GXSetIndirectMask) are absent
// from the DOL entirely. This is also the ONLY known decomp with a real
// 204-byte __GXUpdateBPMask - every other repo (tww/bfbb/tp/mkdd/nfsmw/
// crashwoc/ratatouille) has it as an empty stub.
//
// Uses the public gx global (GXInit.h GXData layout): iref@0x120,
// bpMask@0x124, IndTexScale0/1@0x128/0x12C, genMode@0x204, dirtyState@0x4F4.
//
// NOTES:
// - GXSetTevIndirect packs fields in the MODERN low-bit layout (format<<2,
//   bias<<4, alpha<<7, mtx<<9, wrapS<<13, wrapT<<16, utcLod<<19, addPrev<<20)
//   but with the OLD arg order (utc_lod before alpha_sel, i.e. the last two
//   args are (utc_lod, alpha_sel) and the callee reads utc_lod as a u8 from
//   the top byte of its stack slot).
// - GXSetTevDirect must NOT inline GXSetTevIndirect (the DOL makes a real
//   call) - this file is built with -inline off (see configure.py).
// - __GXUpdateBPMask's register allocation only matches with the local
//   declaration order i, nIndStages, texMapId, mask (mask last).
#include <dolphin/gx.h>
#include <dolphin/os.h>

#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>

#if DEBUG
#define GX_WRITE_SOME_REG5(a, b) \
do { \
    GX_WRITE_U8(a); \
    GX_WRITE_U32(b); \
    __gxVerif->rasRegs[(b >> 24) & 0xFF] = b; \
} while (0)
#else
#define GX_WRITE_SOME_REG5(a, b) \
do { \
    GX_WRITE_U8(a); \
    GX_WRITE_U32(b); \
} while (0)
#endif

void GXSetTevIndirect(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexFormat format, GXIndTexBiasSel bias_sel, GXIndTexMtxID matrix_sel, GXIndTexWrap wrap_s, GXIndTexWrap wrap_t, GXBool add_prev, GXBool utc_lod, GXIndTexAlphaSel alpha_sel)
{
    u32 reg = 0;
    reg = (reg & ~0x3) | (u32)ind_stage;
    reg = (reg & ~(0x3 << 2)) | ((u32)format << 2);
    reg = (reg & ~(0x7 << 4)) | ((u32)bias_sel << 4);
    reg = (reg & ~(0x3 << 7)) | ((u32)alpha_sel << 7);
    reg = (reg & ~(0xF << 9)) | ((u32)matrix_sel << 9);
    reg = (reg & ~(0x7 << 13)) | ((u32)wrap_s << 13);
    reg = (reg & ~(0x7 << 16)) | ((u32)wrap_t << 16);
    reg = (reg & ~(0x1 << 19)) | ((u32)utc_lod << 19);
    reg = (reg & ~(0x1 << 20)) | ((u32)add_prev << 20);
    reg = (reg & 0x00FFFFFF) | ((u32)(tev_stage + 0x10) << 24);
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, reg);
    gx->bpSentNot = 0;
}

void GXSetIndTexCoordScale(GXIndTexStageID ind_state, GXIndTexScale scale_s, GXIndTexScale scale_t)
{
    switch (ind_state) {
    case GX_INDTEXSTAGE0:
        gx->IndTexScale0 = (gx->IndTexScale0 & ~0xF) | scale_s;
        gx->IndTexScale0 = (gx->IndTexScale0 & ~(0xF << 4)) | (scale_t << 4);
        gx->IndTexScale0 = (gx->IndTexScale0 & 0x00FFFFFF) | 0x25000000;
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, gx->IndTexScale0);
        break;
    case GX_INDTEXSTAGE1:
        gx->IndTexScale0 = (gx->IndTexScale0 & ~(0xF << 8)) | (scale_s << 8);
        gx->IndTexScale0 = (gx->IndTexScale0 & ~(0xF << 12)) | (scale_t << 12);
        gx->IndTexScale0 = (gx->IndTexScale0 & 0x00FFFFFF) | 0x25000000;
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, gx->IndTexScale0);
        break;
    case GX_INDTEXSTAGE2:
        gx->IndTexScale1 = (gx->IndTexScale1 & ~0xF) | scale_s;
        gx->IndTexScale1 = (gx->IndTexScale1 & ~(0xF << 4)) | (scale_t << 4);
        gx->IndTexScale1 = (gx->IndTexScale1 & 0x00FFFFFF) | 0x26000000;
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, gx->IndTexScale1);
        break;
    case GX_INDTEXSTAGE3:
        gx->IndTexScale1 = (gx->IndTexScale1 & ~(0xF << 8)) | (scale_s << 8);
        gx->IndTexScale1 = (gx->IndTexScale1 & ~(0xF << 12)) | (scale_t << 12);
        gx->IndTexScale1 = (gx->IndTexScale1 & 0x00FFFFFF) | 0x26000000;
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, gx->IndTexScale1);
        break;
    default:
        break;
    }
    gx->bpSentNot = 0;
}

void GXSetNumIndStages(u8 nIndStages)
{
    gx->genMode = (gx->genMode & ~0x70000) | ((u32)nIndStages << 16);
    gx->dirtyState |= 6;
}

void GXSetTevDirect(GXTevStageID tev_stage)
{
    GXSetTevIndirect(tev_stage, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
}

void __GXUpdateBPMask(void)
{
    u32 i;
    u32 nIndStages = (gx->genMode >> 16) & 7;
    u32 texMapId;
    u32 mask = 0;
    for (i = 0; i < nIndStages; i++) {
        switch (i) {
        case 0:
            texMapId = gx->iref & 7;
            break;
        case 1:
            texMapId = (gx->iref >> 6) & 7;
            break;
        case 2:
            texMapId = (gx->iref >> 12) & 7;
            break;
        case 3:
            texMapId = (gx->iref >> 18) & 7;
            break;
        }
        mask |= 1 << texMapId;
    }

    if ((u8)gx->bpMask != mask) {
        gx->bpMask = (gx->bpMask & ~0xFF) | mask;
        GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, gx->bpMask);
        gx->bpSentNot = 0;
    }
}

void __GXFlushTextureState(void)
{
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, gx->bpMask);
    gx->bpSentNot = 0;
}
