#ifndef _DOLPHIN_GX_H_
#define _DOLPHIN_GX_H_

// thug2's <dolphin/gx.h> is consumed by non-GX modules (OS/demo/gd/etc.) that
// only need GX *types* (GXColor/GXRenderModeObj and the enums). The GX module
// itself uses the full tww (SDK 0x2301) header set via <dolphin/gx/GX.h>.
// GXInit.h/GXTransform.h/GXTexture.h are intentionally omitted here because
// they pull in dolphino/mtx/mtx.h, which collides with the tp <dolphin/mtx.h>
// still used by the OS/DVD umbrella.
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXDisplayList.h>
#include <dolphin/gx/GXDraw.h>
#include <dolphin/gx/GXFifo.h>
#include <dolphin/gx/GXFrameBuf.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLight.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/gx/GXPerf.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>

#endif
