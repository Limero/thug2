// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001BFA8-0x8001C9E0 (2616B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_803213D4;
extern s32 lbl_803613E4;

typedef struct {
    char pad0x0[0x4];
    u16 f4;
    u16 f6;
    u16 f8;
    char pad0xA[0xF];
    u8 f19;
} BFA8G;

void GX_SetViewport(f32, f32, f32, f32, f32, f32);
void GX_SetDispCopySrc(s32, s32, s32, s32);
void GX_SetDispCopyDst(s32, s32);
void GX_SetDispCopyYScale(f32);
void GX_SetCopyFilter(s32, void *, s32, void *);
void GX_SetPixelFmt(s32, s32);
void GX_CopyDisp(s32, s32);
void GX_SetScissor(s32, s32, s32, s32);
void GX_SetDispCopyGamma(s32);
void GX_SetVtxAttrFmt(s32, s32, s32, s32, s32);

void fn_8001BFA8(void) {
    BFA8G *temp_r9;
    BFA8G *temp_r9_2;
    BFA8G *temp_r8;
    BFA8G *temp_r4;

    GX_SetViewport(0.0f, 0.0f, 512.0f, 384.0f, 0.0f, 1.0f);
    GX_SetScissor(0, 0, 0x200, 0x180);
    temp_r9 = (BFA8G *)lbl_803613E4;
    GX_SetDispCopySrc(0, 0, temp_r9->f4, temp_r9->f6);
    temp_r9_2 = (BFA8G *)lbl_803613E4;
    GX_SetDispCopyDst(temp_r9_2->f4, temp_r9_2->f8);
    temp_r8 = (BFA8G *)lbl_803613E4;
    GX_SetDispCopyYScale((f32)(f64)(u32)temp_r8->f8 / (f32)(f64)(u32)temp_r8->f6);
    temp_r4 = (BFA8G *)lbl_803613E4;
    GX_SetCopyFilter(temp_r4->f19, (char *)temp_r4 + 0x1A, 1, (char *)temp_r4 + 0x32);
    temp_r9 = (BFA8G *)lbl_803613E4;
    if (temp_r9->f19 != 0) {
        GX_SetPixelFmt(2, 0);
    } else {
        GX_SetPixelFmt(0, 0);
    }
    GX_CopyDisp(lbl_803213D4, 1);
    GX_SetDispCopyGamma(0);
    GX_SetVtxAttrFmt(0, 9, 1, 4, 0);
    GX_SetVtxAttrFmt(0, 0xA, 0, 4, 0);
    GX_SetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GX_SetVtxAttrFmt(0, 0xC, 1, 5, 0);
    GX_SetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GX_SetVtxAttrFmt(0, 0xE, 1, 4, 0);
    GX_SetVtxAttrFmt(0, 0xF, 1, 4, 0);
    GX_SetVtxAttrFmt(0, 0x10, 1, 4, 0);
    GX_SetVtxAttrFmt(0, 0x11, 1, 4, 0);
    GX_SetVtxAttrFmt(0, 0x12, 1, 4, 0);
    GX_SetVtxAttrFmt(0, 0x13, 1, 4, 0);
    GX_SetVtxAttrFmt(0, 0x14, 1, 4, 0);
    GX_SetVtxAttrFmt(1, 9, 1, 3, 6);
    GX_SetVtxAttrFmt(1, 0xA, 0, 3, 0xE);
    GX_SetVtxAttrFmt(1, 0xB, 1, 5, 0);
    GX_SetVtxAttrFmt(1, 0xC, 1, 5, 0);
    GX_SetVtxAttrFmt(1, 0xD, 1, 4, 0);
    GX_SetVtxAttrFmt(1, 0xE, 1, 4, 0);
    GX_SetVtxAttrFmt(1, 0xF, 1, 4, 0);
    GX_SetVtxAttrFmt(1, 0x10, 1, 4, 0);
    GX_SetVtxAttrFmt(1, 0x11, 1, 4, 0);
    GX_SetVtxAttrFmt(1, 0x12, 1, 4, 0);
    GX_SetVtxAttrFmt(1, 0x13, 1, 4, 0);
    GX_SetVtxAttrFmt(1, 0x14, 1, 4, 0);
    GX_SetVtxAttrFmt(2, 9, 1, 4, 0);
    GX_SetVtxAttrFmt(2, 0xA, 0, 3, 0xE);
    GX_SetVtxAttrFmt(2, 0xB, 1, 5, 0);
    GX_SetVtxAttrFmt(2, 0xC, 1, 5, 0);
    GX_SetVtxAttrFmt(2, 0xD, 1, 3, 0);
    GX_SetVtxAttrFmt(2, 0xE, 1, 3, 0);
    GX_SetVtxAttrFmt(2, 0xF, 1, 3, 0);
    GX_SetVtxAttrFmt(2, 0x10, 1, 3, 0);
    GX_SetVtxAttrFmt(2, 0x11, 1, 3, 0);
    GX_SetVtxAttrFmt(2, 0x12, 1, 3, 0);
    GX_SetVtxAttrFmt(2, 0x13, 1, 3, 0);
    GX_SetVtxAttrFmt(2, 0x14, 1, 3, 0);
    GX_SetVtxAttrFmt(3, 9, 1, 4, 0);
    GX_SetVtxAttrFmt(3, 0xA, 0, 3, 0xE);
    GX_SetVtxAttrFmt(3, 0xB, 1, 5, 0);
    GX_SetVtxAttrFmt(3, 0xC, 1, 5, 0);
    GX_SetVtxAttrFmt(3, 0xD, 1, 3, 2);
    GX_SetVtxAttrFmt(3, 0xE, 1, 3, 2);
    GX_SetVtxAttrFmt(3, 0xF, 1, 3, 2);
    GX_SetVtxAttrFmt(3, 0x10, 1, 3, 2);
    GX_SetVtxAttrFmt(3, 0x11, 1, 3, 2);
    GX_SetVtxAttrFmt(3, 0x12, 1, 3, 2);
    GX_SetVtxAttrFmt(3, 0x13, 1, 3, 2);
    GX_SetVtxAttrFmt(3, 0x14, 1, 3, 2);
    GX_SetVtxAttrFmt(4, 9, 1, 4, 0);
    GX_SetVtxAttrFmt(4, 0xA, 0, 3, 0xE);
    GX_SetVtxAttrFmt(4, 0xB, 1, 5, 0);
    GX_SetVtxAttrFmt(4, 0xC, 1, 5, 0);
    GX_SetVtxAttrFmt(4, 0xD, 1, 3, 4);
    GX_SetVtxAttrFmt(4, 0xE, 1, 3, 4);
    GX_SetVtxAttrFmt(4, 0xF, 1, 3, 4);
    GX_SetVtxAttrFmt(4, 0x10, 1, 3, 4);
    GX_SetVtxAttrFmt(4, 0x11, 1, 3, 4);
    GX_SetVtxAttrFmt(4, 0x12, 1, 3, 4);
    GX_SetVtxAttrFmt(4, 0x13, 1, 3, 4);
    GX_SetVtxAttrFmt(4, 0x14, 1, 3, 4);
    GX_SetVtxAttrFmt(5, 9, 1, 4, 0);
    GX_SetVtxAttrFmt(5, 0xA, 0, 3, 0xE);
    GX_SetVtxAttrFmt(5, 0xB, 1, 5, 0);
    GX_SetVtxAttrFmt(5, 0xC, 1, 5, 0);
    GX_SetVtxAttrFmt(5, 0xD, 1, 3, 6);
    GX_SetVtxAttrFmt(5, 0xE, 1, 3, 6);
    GX_SetVtxAttrFmt(5, 0xF, 1, 3, 6);
    GX_SetVtxAttrFmt(5, 0x10, 1, 3, 6);
    GX_SetVtxAttrFmt(5, 0x11, 1, 3, 6);
    GX_SetVtxAttrFmt(5, 0x12, 1, 3, 6);
    GX_SetVtxAttrFmt(5, 0x13, 1, 3, 6);
    GX_SetVtxAttrFmt(5, 0x14, 1, 3, 6);
    GX_SetVtxAttrFmt(6, 9, 1, 4, 0);
    GX_SetVtxAttrFmt(6, 0xA, 0, 3, 0xE);
    GX_SetVtxAttrFmt(6, 0xB, 1, 5, 0);
    GX_SetVtxAttrFmt(6, 0xC, 1, 5, 0);
    GX_SetVtxAttrFmt(6, 0xD, 1, 3, 8);
    GX_SetVtxAttrFmt(6, 0xE, 1, 3, 8);
    GX_SetVtxAttrFmt(6, 0xF, 1, 3, 8);
    GX_SetVtxAttrFmt(6, 0x10, 1, 3, 8);
    GX_SetVtxAttrFmt(6, 0x11, 1, 3, 8);
    GX_SetVtxAttrFmt(6, 0x12, 1, 3, 8);
    GX_SetVtxAttrFmt(6, 0x13, 1, 3, 8);
    GX_SetVtxAttrFmt(6, 0x14, 1, 3, 8);
    GX_SetVtxAttrFmt(7, 9, 1, 4, 0);
    GX_SetVtxAttrFmt(7, 0xA, 0, 3, 0xE);
    GX_SetVtxAttrFmt(7, 0xB, 1, 5, 0);
    GX_SetVtxAttrFmt(7, 0xC, 1, 5, 0);
    GX_SetVtxAttrFmt(7, 0xD, 1, 3, 0xA);
    GX_SetVtxAttrFmt(7, 0xE, 1, 3, 0xA);
    GX_SetVtxAttrFmt(7, 0xF, 1, 3, 0xA);
    GX_SetVtxAttrFmt(7, 0x10, 1, 3, 0xA);
    GX_SetVtxAttrFmt(7, 0x11, 1, 3, 0xA);
    GX_SetVtxAttrFmt(7, 0x12, 1, 3, 0xA);
    GX_SetVtxAttrFmt(7, 0x13, 1, 3, 0xA);
    GX_SetVtxAttrFmt(7, 0x14, 1, 3, 0xA);
}
