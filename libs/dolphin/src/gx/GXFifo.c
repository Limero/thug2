// GXFifo.c - GX FIFO / command processor setup (Feb-2003 SDK revision, THUG2).
// Wired byte-exact from retail 0x802861A4..0x802869B4.
// Base: tww GXFifo.c (Sep-2002) with Feb-2003 drift fixed:
//   - the three interrupt handlers are inlined into GXCPInterruptHandler
//   - the cpEnable/cpClr bit helpers write "clear bit (31-pos), set bit pos"
//     (the 0x80000000 >> pos mask form), which mwcc emits for the retail
//     byte pattern
#include <cstddef>

#include <dolphin/base/PPCArch.h>
#include <dolphin/gx/GXFifo.h>
#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>
#include <dolphin/os.h>

static void GXInitFifoLimits(GXFifoObj* fifo, u32 hi_watermark, u32 lo_watermark);

static GXFifoObj* CPUFifo;
static GXFifoObj* GPFifo;
static OSThread* __GXCurrentThread;
static GXBool CPGPLinked;
static u32 GXOverflowSuspendInProgress;
static GXBreakPtCallback BreakPointCB;
static u32 __GXOverflowCount;
static void* __GXCurrentBP;

// The 1-bit register fields below are written with SET_REG_FIELD(reg, 1, pos,
// val). mwcc compiles the "~(1 << pos)" clear mask to a wrapping rlwinm that
// clears bit (31-pos), which is exactly the retail byte pattern (verified
// standalone: pos 0..5 -> clear bits 31,30,29,28,27,26).

static void GXCPInterruptHandler(__OSInterrupt interrupt, OSContext* context) {
    gx->cpStatus = GX_GET_CP_REG(0);

    if (GET_REG_FIELD(gx->cpEnable, 1, 3) && GET_REG_FIELD(gx->cpStatus, 1, 1)) {
        OSResumeThread(__GXCurrentThread);
        GXOverflowSuspendInProgress = FALSE;
        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
    }

    if (GET_REG_FIELD(gx->cpEnable, 1, 2) && GET_REG_FIELD(gx->cpStatus, 1, 0)) {
        __GXOverflowCount += 1;
        __GXWriteFifoIntEnable(0, 1);
        __GXWriteFifoIntReset(1, 0);
        GXOverflowSuspendInProgress = TRUE;
        OSSuspendThread(__GXCurrentThread);
    }

    if (GET_REG_FIELD(gx->cpEnable, 1, 5) && GET_REG_FIELD(gx->cpStatus, 1, 4)) {
        OSContext bpContext;

        SET_REG_FIELD(gx->cpEnable, 1, 5, 0);
        GX_SET_CP_REG(1, gx->cpEnable);

        if (BreakPointCB) {
            OSClearContext(&bpContext);
            OSSetCurrentContext(&bpContext);
            BreakPointCB();
            OSClearContext(&bpContext);
            OSSetCurrentContext(context);
        }
    }
}

void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size) {
    fifo->base = base;
    fifo->end = (void*)((u32)base + size - 4);
    fifo->size = size;
    fifo->rw_dst = 0;
    GXInitFifoLimits(fifo, size - 0x4000, OSRoundDown32B(size / 2));
    GXInitFifoPtrs(fifo, base, base);
}

void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr) {
    int interrupts = OSDisableInterrupts();
    fifo->read_ptr = readPtr;
    fifo->write_ptr = writePtr;
    fifo->rw_dst = (u32)writePtr - (u32)readPtr;
    if (fifo->rw_dst < 0) {
        fifo->rw_dst += fifo->size;
    }
    OSRestoreInterrupts(interrupts);
}

static void GXInitFifoLimits(GXFifoObj* fifo, u32 hi_watermark, u32 lo_watermark) {
    fifo->high_wtrmark = hi_watermark;
    fifo->low_wtrmark = lo_watermark;
}

void GXSetCPUFifo(GXFifoObj* fifo) {
    BOOL interrupts;
    interrupts = OSDisableInterrupts();

    CPUFifo = fifo;

    if (fifo == GPFifo) {
        u32 reg;
        GX_SET_PI_REG(3, (u32)fifo->base & 0x3FFFFFFF);
        GX_SET_PI_REG(4, (u32)fifo->end & 0x3FFFFFFF);
        reg = 0;
        GX_BITFIELD_SET(reg, 6, 21, ((u32)fifo->write_ptr & 0x3FFFFFFF) >> 5);
        GX_BITFIELD_SET(reg, 5, 1, 0);
        GX_SET_PI_REG(5, reg);

        CPGPLinked = GX_TRUE;

        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        u32 reg;
        if (CPGPLinked) {
            __GXFifoLink(0);
            CPGPLinked = GX_FALSE;
        }
        __GXWriteFifoIntEnable(0, 0);

        GX_SET_PI_REG(3, (u32)fifo->base & 0x3FFFFFFF);
        GX_SET_PI_REG(4, (u32)fifo->end & 0x3FFFFFFF);
        reg = 0;
        GX_BITFIELD_SET(reg, 6, 21, ((u32)fifo->write_ptr & 0x3FFFFFFF) >> 5);
        GX_BITFIELD_SET(reg, 5, 1, 0);
        GX_SET_PI_REG(5, reg);
    }

    PPCSync();

    OSRestoreInterrupts(interrupts);
}

void GXSetGPFifo(GXFifoObj* fifo) {
    int interrupts = OSDisableInterrupts();
    __GXFifoReadDisable();
    __GXWriteFifoIntEnable(0, 0);
    GPFifo = fifo;
    GX_SET_CP_REG(16, (u16)fifo->base);
    GX_SET_CP_REG(18, (u16)fifo->end);
    GX_SET_CP_REG(24, (u16)fifo->rw_dst);
    GX_SET_CP_REG(26, (u16)fifo->write_ptr);
    GX_SET_CP_REG(28, (u16)fifo->read_ptr);
    GX_SET_CP_REG(20, (u16)fifo->high_wtrmark);
    GX_SET_CP_REG(22, (u16)fifo->low_wtrmark);

    GX_SET_CP_REG(17, ((u32)fifo->base & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(19, ((u32)fifo->end & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(25, (fifo->rw_dst) >> 16);
    GX_SET_CP_REG(27, ((u32)fifo->write_ptr & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(29, ((u32)fifo->read_ptr & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(21, (fifo->high_wtrmark) >> 16);
    GX_SET_CP_REG(23, (fifo->low_wtrmark) >> 16);

    PPCSync();

    if (CPUFifo == GPFifo) {
        CPGPLinked = GX_TRUE;
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        CPGPLinked = GX_FALSE;
        __GXWriteFifoIntEnable(0, 0);
        __GXFifoLink(0);
    }

    __GXWriteFifoIntReset(1, 1);
    __GXFifoReadEnable();
    OSRestoreInterrupts(interrupts);
}

void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle,
                   GXBool* brkpt) {
    gx->cpStatus = GX_GET_CP_REG(0);
    *overhi = gx->cpStatus & 1;
    *underlow = (gx->cpStatus >> 1) & 1;
    *readIdle = (gx->cpStatus >> 2) & 1;
    *cmdIdle = (gx->cpStatus >> 3) & 1;
    *brkpt = (gx->cpStatus >> 4) & 1;
}

void GXGetFifoPtrs(GXFifoObj* fifo, void** readPtr, void** writePtr) {
    if (fifo == CPUFifo) {
        fifo->write_ptr = OSPhysicalToCached(GX_GET_PI_REG(5) & 0xFBFFFFFF);
    }

    if (fifo == GPFifo) {
        u32 temp = GX_GET_CP_REG(29) << 16;
        temp |= GX_GET_CP_REG(28);
        fifo->read_ptr = OSPhysicalToCached(temp);
        fifo->rw_dst = (GX_GET_CP_REG(25) << 16) | GX_GET_CP_REG(24);
    } else {
        fifo->rw_dst = (u32)fifo->write_ptr - (u32)fifo->read_ptr;
        if (fifo->rw_dst < 0) {
            fifo->rw_dst += fifo->size;
        }
    }

    *readPtr = fifo->read_ptr;
    *writePtr = fifo->write_ptr;
}

GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb) {
    GXBreakPtCallback oldCallback = BreakPointCB;
    int interrupts = OSDisableInterrupts();
    BreakPointCB = cb;
    OSRestoreInterrupts(interrupts);
    return oldCallback;
}

void GXEnableBreakPt(void* break_pt) {
    int interrupts = OSDisableInterrupts();

    __GXFifoReadDisable();
    GX_SET_CP_REG(30, (u32)break_pt);
    GX_SET_CP_REG(31, ((u32)break_pt >> 16) & 0x3FFF);
    SET_REG_FIELD(gx->cpEnable, 1, 1, 1);
    SET_REG_FIELD(gx->cpEnable, 1, 5, 1);
    GX_SET_CP_REG(1, gx->cpEnable);
    __GXCurrentBP = break_pt;
    __GXFifoReadEnable();
    OSRestoreInterrupts(interrupts);
}

void GXDisableBreakPt(void) {
    int interrupts = OSDisableInterrupts();

    SET_REG_FIELD(gx->cpEnable, 1, 1, 0);
    SET_REG_FIELD(gx->cpEnable, 1, 5, 0);
    GX_SET_CP_REG(1, gx->cpEnable);
    __GXCurrentBP = NULL;
    OSRestoreInterrupts(interrupts);
}

void __GXFifoInit(void) {
    __OSSetInterruptHandler(0x11, GXCPInterruptHandler);
    __OSUnmaskInterrupts(0x4000);
    __GXCurrentThread = OSGetCurrentThread();
    GXOverflowSuspendInProgress = 0;
    CPUFifo = NULL;
    GPFifo = NULL;
}

static void __GXFifoReadEnable(void) {
    SET_REG_FIELD(gx->cpEnable, 1, 0, 1);
    GX_SET_CP_REG(1, gx->cpEnable);
}

static void __GXFifoReadDisable(void) {
    SET_REG_FIELD(gx->cpEnable, 1, 0, 0);
    GX_SET_CP_REG(1, gx->cpEnable);
}

static void __GXFifoLink(u8 en) {
    SET_REG_FIELD(gx->cpEnable, 1, 4, (en != 0) ? 1 : 0);
    GX_SET_CP_REG(1, gx->cpEnable);
}

static void __GXWriteFifoIntEnable(u8 hiWatermarkEn, u8 loWatermarkEn) {
    SET_REG_FIELD(gx->cpEnable, 1, 2, hiWatermarkEn);
    SET_REG_FIELD(gx->cpEnable, 1, 3, loWatermarkEn);
    GX_SET_CP_REG(1, gx->cpEnable);
}

static void __GXWriteFifoIntReset(u8 hiWatermarkClr, u8 loWatermarkClr) {
    SET_REG_FIELD(gx->cpClr, 1, 0, hiWatermarkClr);
    SET_REG_FIELD(gx->cpClr, 1, 1, loWatermarkClr);
    GX_SET_CP_REG(2, gx->cpClr);
}

GXFifoObj* GXGetCPUFifo(void) {
    return CPUFifo;
}

GXFifoObj* GXGetGPFifo(void) {
    return GPFifo;
}

u32 GXGetOverflowCount(void) {
    return __GXOverflowCount;
}
