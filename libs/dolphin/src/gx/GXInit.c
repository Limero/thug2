// thug2's GXInit block (0x80284E20..0x802861A4) is the Feb 7 2003 (0x2301)
// SDK build that exists in no other decomp. WIRED here are the 3 functions
// whose peephole-off reconstruction is byte-exact (verified 2026-08-19):
//   __GXDefaultTexRegionCallback / __GXDefaultTlutRegionCallback / __GXShutdown
// GXInit main (0x80285050..0x802858E0) stays auto-asm - its reconstruction is
// structurally off (42 extra insns: fully-unrolled suTs/vat loops) and emits
// .sdata2 constants retail lacks. __GXInitGX (0x802858E0..0x802861A4) is wired
// in GXInitGX.c. See docs/parkings/21-gxinit.md.
//
// #pragma peephole off is REQUIRED: retail keeps dead b .+4 chains and
// schedules the gx load after the prologue (docs/dolphin-sdk.md s8.17).

#include <dolphin/base/PPCArch.h>
#include <dolphin/gx.h>
#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>

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

// All data lives in auto-asm (extern route, docs/dolphin-sdk.md §8.14): the
// .sbss counters/register pointers, the .sdata2 gx pointer, AND the .data
// GXDefaultVATList/GXDefaultProjData/GXResetFuncInfo keep their exact retail
// layout only in the auto units. Only .text is claimed.

extern GXData* const gx;

extern u32 resetFuncRegistered;
extern u32 calledOnce;
extern OSTime time;
extern u32 peCount;

extern vu16* __memReg;
extern u16* __peReg;
extern u16* __cpReg;
extern u32* __piReg;

#pragma peephole off

GXTexRegion* __GXDefaultTexRegionCallback(const GXTexObj* obj, GXTexMapID id) {
    GXTexFmt format;

    format = GXGetTexObjFmt(obj);

    if (format != GX_TF_C4 && format != GX_TF_C8 && format != GX_TF_C14X2) {
        return &gx->TexRegions0[gx->nextTexRgn++ % GX_MAX_TEXMAP];
    } else {
        return &gx->TexRegions1[gx->nextTexRgnCI++ % 4];
    }
}

GXTlutRegion* __GXDefaultTlutRegionCallback(u32 tlut) {
    if (tlut >= 0x14) {
        return NULL;
    } else {
        return &gx->TlutRegions[tlut];
    }
}

int __GXShutdown(int final) {
    u32 reg;
    u32 peCountNew;
    OSTime timeNew;

    if (!final) {
        if (!calledOnce) {
            peCount = __GXReadMEMCounterU32(0x28, 0x27);
            time = OSGetTime();
            calledOnce = 1;
            return 0;
        }

        timeNew = OSGetTime();
        peCountNew = __GXReadMEMCounterU32(0x28, 0x27);

        if (timeNew - time < 10) {
            return 0;
        }

        if (peCountNew != peCount) {
            peCount = peCountNew;
            time = timeNew;
            return 0;
        }
    } else {
        GXSetBreakPtCallback(NULL);
        GXSetDrawSyncCallback(NULL);
        GXSetDrawDoneCallback(NULL);

        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);

        PPCSync();

        reg = 0;
        GX_SET_CP_REG(1, reg);

        reg = 3;
        GX_SET_CP_REG(2, reg);

        gx->abtWaitPECopy = 1;

        __GXAbort();
    }

    return 1;
}
