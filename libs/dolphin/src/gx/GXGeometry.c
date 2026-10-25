#include <dolphin/gx.h>
#include <dolphin/gx/GX.h>

void __GXSetDirtyState(void)
{
    if (gx->dirtyState & 1)
    {
        __GXSetSUTexRegs();
    }
    if (gx->dirtyState & 2)
    {
        __GXUpdateBPMask();
    }
    if (gx->dirtyState & 4)
    {
        __GXSetGenMode();
    }
    if (gx->dirtyState & 8)
    {
        __GXSetVCD();
    }
    if (gx->dirtyState & 0x10)
    {
        __GXSetVAT();
    }
    if (gx->dirtyState & 0x18)
    {
        __GXCalculateVLim();
    }

    gx->dirtyState = 0;
}

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts)
{
    if (gx->dirtyState != 0)
    {
        if (gx->dirtyState & 1)
        {
            __GXSetSUTexRegs();
        }
        if (gx->dirtyState & 2)
        {
            __GXUpdateBPMask();
        }
        if (gx->dirtyState & 4)
        {
            __GXSetGenMode();
        }
        if (gx->dirtyState & 8)
        {
            __GXSetVCD();
        }
        if (gx->dirtyState & 0x10)
        {
            __GXSetVAT();
        }
        if (gx->dirtyState & 0x18)
        {
            __GXCalculateVLim();
        }

        gx->dirtyState = 0;
    }

    if (*(u32*)&gx->vNumNot == 0)
    { // checks both vNum and bpSentNot
        __GXSendFlushPrim();
    }
    GX_WRITE_U8(vtxfmt | type);
    GX_WRITE_U16(nverts);
}

void __GXSendFlushPrim(void)
{
    u32 i;
    u32 sz = gx->vNum * gx->vLim;

    GX_WRITE_U8(0x98);
    GX_WRITE_U16(gx->vNum);
    for (i = 0; i < sz; i += 4)
    {
        GX_WRITE_U32(0);
    }
    gx->bpSentNot = 1;
}

void GXSetLineWidth(u8 width, GXTexOffset texOffsets)
{
    GXData* data = gx;

    GX_BITFIELD_SET(data->lpSize, 24, 8, width);
    GX_BITFIELD_SET(data->lpSize, 13, 3, texOffsets);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(data->lpSize);
    data->bpSentNot = 0;
}

void GXSetPointSize(u8 pointSize, GXTexOffset texOffsets)
{
    GXData* data = gx;

    GX_BITFIELD_SET(data->lpSize, 16, 8, pointSize);
    GX_BITFIELD_SET(data->lpSize, 10, 3, texOffsets);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(data->lpSize);
    data->bpSentNot = 0;
}

void GXEnableTexOffsets(GXTexCoordID coord, GXBool line, GXBool point)
{
    GX_BITFIELD_SET(gx->suTs0[coord], 13, 1, line);
    GX_BITFIELD_SET(gx->suTs0[coord], 12, 1, point);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(gx->suTs0[coord]);
    gx->bpSentNot = 0;
}

void GXSetCullMode(GXCullMode mode)
{
    GXCullMode hwMode;

    switch (mode)
    {
    case GX_CULL_FRONT:
        hwMode = GX_CULL_BACK;
        break;
    case GX_CULL_BACK:
        hwMode = GX_CULL_FRONT;
        break;
    default:
        hwMode = mode;
        break;
    }

    GX_BITFIELD_SET(gx->genMode, 16, 2, hwMode);
    gx->dirtyState |= GX_DIRTY_GEN_MODE;
}

void GXSetCoPlanar(GXBool enable)
{
    GXData* data = gx;

    GX_BITFIELD_SET(data->genMode, 12, 1, enable);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(0xFE080000);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(data->genMode);
}

void __GXSetGenMode(void)
{
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(gx->genMode);
    gx->bpSentNot = 0;
}
