// GXLight.c's channel-function tail split into its own file: the middle pair
// GXSetChanAmbColor (0x80289AE4) + GXSetChanMatColor (0x80289BD8) is a
// regalloc coin-flip and stays auto-asm (docs/parkings/18-gxlight-chan-regalloc.md),
// which makes a single contiguous GXLight.c split impossible. GXSetNumChans +
// GXSetChanCtrl (0x80289CCC..0x80289DDC) are wired byte-exact here.
#include <dolphin/gx.h>
#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>

void GXSetNumChans(u8 nChans)
{
    SET_REG_FIELD(gx->genMode, 3, 4, nChans);
    GX_WRITE_XF_REG(9, nChans);
    gx->dirtyState |= 4;
}

void GXSetChanCtrl(GXChannelID channel, GXBool enable, GXColorSrc amb_src,
                   GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn,
                   GXAttnFn attn_fn)
{
    u32 reg;
    u32 idx;

    idx = (u32)channel & 3;

    reg = 0;
    SET_REG_FIELD(reg, 1, 1, enable);
    SET_REG_FIELD(reg, 1, 0, mat_src);
    SET_REG_FIELD(reg, 1, 6, amb_src);
    SET_REG_FIELD(reg, 2, 7, (attn_fn == GX_AF_SPEC) ? GX_DF_NONE : diff_fn);
    SET_REG_FIELD(reg, 1, 9, (attn_fn != GX_AF_NONE));
    SET_REG_FIELD(reg, 1, 10, (attn_fn != GX_AF_SPEC));
    reg = (reg & ~(0xf << 2)) | ((light_mask & 0xf) << 2);
    reg = (reg & ~(0xf << 11)) | (((light_mask >> 4) & 0xf) << 11);

    GX_WRITE_XF_REG(idx + 14, reg);
    if (channel == GX_COLOR0A0)
    {
        GX_WRITE_XF_REG(16, reg);
    }
    else if (channel == GX_COLOR1A1)
    {
        GX_WRITE_XF_REG(17, reg);
    }
    gx->bpSentNot = GX_TRUE;
}
