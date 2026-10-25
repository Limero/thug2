#include <dolphin/base/PPCArch.h>
#include <dolphin/hw_regs.h>
#include <dolphin/gx.h>
#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>
#include <dolphin/os.h>

// __GXReadMEMCounterU32 lives in the EA-lineage __gx.h, which conflicts with
// our tww-lineage GX headers; copy the small inline here (matches retail).
static inline u32 __GXReadMEMCounterU32(u32 regAddrL, u32 regAddrH)
{
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

    ctrH0 = GX_GET_MEM_REG(regAddrH);

    do {
        ctrH1 = ctrH0;
        ctrL = GX_GET_MEM_REG(regAddrL);
        ctrH0 = GX_GET_MEM_REG(regAddrH);
    } while (ctrH0 != ctrH1);

    return (ctrH0 << 0x10) | ctrL;
}

static GXDrawSyncCallback TokenCB;
static GXDrawDoneCallback DrawDoneCB;
static u8 DrawDone;
static OSThreadQueue FinishQueue;

void GXSetMisc(GXMiscToken token, u32 val)
{
    switch (token)
    {
    case GX_MT_XF_FLUSH:
        gx->vNum = val;
        gx->vNumNot = !gx->vNum;
        gx->bpSentNot = 1;

        if (gx->vNum != 0)
        {
            gx->dirtyState |= 8;
        }
        break;
    case GX_MT_DL_SAVE_CONTEXT:
        ASSERTMSGLINE(223, !gx->inDispList, "GXSetMisc: Cannot change DL context setting while making a display list");
        gx->dlSaveContext = (val != 0);
        break;
    case GX_MT_ABORT_WAIT_COPYOUT:
        gx->abtWaitPECopy = (val != 0);
        break;
    case GX_MT_NULL:
        break;
    default:
#if DEBUG
        OSReport("GXSetMisc: bad token %d (val %d)\n", token, val);
#endif
        break;
    }
}

void GXFlush(void)
{
    if (gx->dirtyState)
    {
        __GXSetDirtyState();
    }

    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);

    PPCSync();
}

inline void __GXAbortWait(u32 clocks)
{
    OSTime time0;
    OSTime time1;

    time0 = OSGetTime();
    do
    {
        time1 = OSGetTime();
    } while (time1 - time0 <= (clocks / 4));
}

inline void __GXAbortWaitPECopyDone(void)
{
    u32 peCnt0;
    u32 peCnt1;

    peCnt0 = __GXReadMEMCounterU32(0x28, 0x27);
    do
    {
        peCnt1 = peCnt0;
        __GXAbortWait(32);

        peCnt0 = __GXReadMEMCounterU32(0x28, 0x27);
    } while (peCnt0 != peCnt1);
}

void __GXAbort(void)
{
    if (gx->abtWaitPECopy && GXGetGPFifo() != (GXFifoObj*)NULL)
    {
        __GXAbortWaitPECopyDone();
    }

    __PIRegs[0x18 / 4] = 1;
    __GXAbortWait(200);
    __PIRegs[0x18 / 4] = 0;
    __GXAbortWait(20);
}

void GXSetDrawSync(u16 token)
{
    BOOL enabled;
    u32 reg;

    enabled = OSDisableInterrupts();
    reg = token | 0x48000000;
    GX_WRITE_RAS_REG(reg);
    SET_REG_FIELD(reg, 16, 0, token);
    SET_REG_FIELD(reg, 8, 24, 0x47);
    GX_WRITE_RAS_REG(reg);
    GXFlush();
    OSRestoreInterrupts(enabled);
    gx->bpSentNot = 0;
}

u16 GXReadDrawSync(void)
{
    u16 token = GX_GET_PE_REG(7);
    return token;
}

inline void GXSetDrawDone(void)
{
    u32 reg;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    reg = 0x45000002;
    GX_WRITE_RAS_REG(reg);
    GXFlush();
    DrawDone = 0;
    OSRestoreInterrupts(enabled);
}

inline void GXWaitDrawDone(void)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    while (!DrawDone)
    {
        OSSleepThread(&FinishQueue);
    }
    OSRestoreInterrupts(enabled);
}

void GXDrawDone(void)
{
    // GXSetDrawDone uses GXFlush()
    // This functions requires less lines in GXFlush
    // but then GXFlush doesnt match
    GXSetDrawDone();
    GXWaitDrawDone();
}

void GXPixModeSync(void)
{
    GX_WRITE_RAS_REG(gx->peCtrl);
    gx->bpSentNot = 0;
}

#if DEBUG
void __GXBypass(u32 reg)
{
    GX_WRITE_RAS_REG(reg);
    gx->bpSentNot = 0;
}

u16 __GXReadPEReg(u32 reg)
{
    return GX_GET_PE_REG(reg);
}
#endif

void GXPokeAlphaMode(GXCompare func, u8 threshold)
{
    u32 reg;

    reg = (func << 8) | threshold;
    GX_SET_PE_REG(3, reg);
}

void GXPokeAlphaRead(GXAlphaReadMode mode)
{
    u32 reg;

    reg = 0;
    SET_REG_FIELD(reg, 2, 0, mode);
    SET_REG_FIELD(reg, 1, 2, 1);
    GX_SET_PE_REG(4, reg);
}

void GXPokeAlphaUpdate(GXBool update_enable)
{
    u32 reg;

    reg = GX_GET_PE_REG(1);
    SET_REG_FIELD(reg, 1, 4, update_enable);
    GX_SET_PE_REG(1, reg);
}

void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor,
                     GXLogicOp op)
{
    u32 reg;

    reg = GX_GET_PE_REG(1);
    SET_REG_FIELD(reg, 1, 0, (type == GX_BM_BLEND) || (type == GX_BM_SUBTRACT));
    SET_REG_FIELD(reg, 1, 11, (type == GX_BM_SUBTRACT));
    SET_REG_FIELD(reg, 1, 1, (type == GX_BM_LOGIC));
    SET_REG_FIELD(reg, 4, 12, op);
    SET_REG_FIELD(reg, 3, 8, src_factor);
    SET_REG_FIELD(reg, 3, 5, dst_factor);
    SET_REG_FIELD(reg, 8, 24, 0x41);
    GX_SET_PE_REG(1, reg);
}

void GXPokeColorUpdate(GXBool update_enable)
{
    u32 reg;

    reg = GX_GET_PE_REG(1);
    SET_REG_FIELD(reg, 1, 3, update_enable);
    GX_SET_PE_REG(1, reg);
}

void GXPokeDstAlpha(GXBool enable, u8 alpha)
{
    u32 reg = 0;

    SET_REG_FIELD(reg, 8, 0, alpha);
    SET_REG_FIELD(reg, 1, 8, enable);
    GX_SET_PE_REG(2, reg);
}

void GXPokeDither(GXBool dither)
{
    u32 reg;

    reg = GX_GET_PE_REG(1);
    SET_REG_FIELD(reg, 1, 2, dither);
    GX_SET_PE_REG(1, reg);
}

void GXPokeZMode(GXBool compare_enable, GXCompare func, GXBool update_enable)
{
    u32 reg = 0;

    SET_REG_FIELD(reg, 1, 0, compare_enable);
    SET_REG_FIELD(reg, 3, 1, func);
    SET_REG_FIELD(reg, 1, 4, update_enable);
    GX_SET_PE_REG(0, reg);
}

void GXPeekZ(u16 x, u16 y, u32* z)
{
    u32 addr = 0xc8000000;
    addr = (addr | (x << 2)) & 0xffc00fff;
    addr = (addr | (y << 12)) & 0xff3fffff;
    *z = *(u32*)addr;
}

void GXPokeZ(u16 x, u16 y, u32 z)
{
    u32 addr = 0xc8000000;
    addr = (addr | (x << 2)) & 0xffc00fff;
    addr = (addr | (y << 12)) & 0xff3fffff;
    *(u32*)addr = z;
}

GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback cb)
{
    GXDrawSyncCallback oldcb;
    BOOL enabled;

    oldcb = TokenCB;
    enabled = OSDisableInterrupts();
    TokenCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}

static void GXTokenInterruptHandler(__OSInterrupt interrupt, OSContext* context)
{
    u16 token;
    OSContext exceptionContext;
    u32 reg;

    token = GX_GET_PE_REG(7);
    if (TokenCB != NULL)
    {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        TokenCB(token);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
    reg = GX_GET_PE_REG(5);
    SET_REG_FIELD(reg, 1, 2, 1);
    GX_SET_PE_REG(5, reg);
}

GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb)
{
    GXDrawDoneCallback oldcb;
    BOOL enabled;

    oldcb = DrawDoneCB;
    enabled = OSDisableInterrupts();
    DrawDoneCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}

static void GXFinishInterruptHandler(__OSInterrupt interrupt, OSContext* context)
{
    OSContext exceptionContext;
    u32 reg;

    reg = GX_GET_PE_REG(5);
    SET_REG_FIELD(reg, 1, 3, 1);
    GX_SET_PE_REG(5, reg);
    DrawDone = 1;
    if (DrawDoneCB != NULL)
    {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        DrawDoneCB();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
    OSWakeupThread(&FinishQueue);
}

void __GXPEInit(void)
{
    u32 reg;
    __OSSetInterruptHandler(0x12, GXTokenInterruptHandler);
    __OSSetInterruptHandler(0x13, GXFinishInterruptHandler);
    OSInitThreadQueue(&FinishQueue);
    __OSUnmaskInterrupts(0x2000);
    __OSUnmaskInterrupts(0x1000);
    reg = GX_GET_PE_REG(5);
    SET_REG_FIELD(reg, 1, 2, 1);
    SET_REG_FIELD(reg, 1, 3, 1);
    SET_REG_FIELD(reg, 1, 0, 1);
    SET_REG_FIELD(reg, 1, 1, 1);
    GX_SET_PE_REG(5, reg);
}
