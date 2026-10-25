// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801227CC-0x801229CC (512B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// NOTE (2026-10-04): this object has a PRIVATE 8-byte .rodata pool — the
// 0.0f / -1.0f / 1.0f literals plus the 0x4330000080000000 int->f64 magic.
// tools/fix_fp_pool.py retargets its 4 pool sites to lbl_8029E230 / E238 /
// E23C / E240 and empties .rodata. This ONLY links because ngccc CSEs the
// `lis`: ONE HA reloc feeds TWO LO relocs, which the old proximity-based
// HA/LO pairing mis-matched (recipes §6gu). Do not re-derive the pool
// constants as externs — the plain-literal spelling is load-bearing for the
// `fmr f3,f1 / fmr f5,f3 / fmr f2,f1` copy chain and for the frame.
#include "types.h"
typedef struct {
    char pad0x0[4];
    unsigned short width;
    unsigned short height;
} Unk_801227CC_arg;

void GXSetPixelFmt(s32, s32);
void GXSetProjection(const void *, s32);
void GXSetViewport(f32, f32, f32, f32, f32, f32);
void GXSetScissor(s32, s32, s32, s32);
void GXSetCurrentMtx(s32);
void GXSetZMode(s32, s32, s32);
void GXSetBlendMode(s32, s32, s32, s32);
void GXSetColorUpdate(s32);
void GXSetAlphaUpdate(s32);
void GXSetDispCopyGamma(s32);
void GXSetNumChans(s32);
void GXSetNumTexGens(s32);
void GXSetTexCoordGen2(s32, s32, s32, s32, s32, s32);
void GXInvalidateTexAll(void);
void GXClearVtxDesc(void);
void GXSetVtxDesc(s32, s32);
void GXSetVtxAttrFmt(s32, s32, s32, s32, s32);
void GXSetNumTevStages();
void fn_8024E2C8(s32);
void C_MTXOrtho(f32 m[4][4], f32, f32, f32, f32, f32, f32);

void fn_801227CC(Unk_801227CC_arg *arg0) {
    f32 mtx[20];
    unsigned short w = arg0->width;
    unsigned short h = arg0->height;

    GXSetPixelFmt(0, 0);
    C_MTXOrtho(mtx, 0.0f, (f32) (f64) (s32) h, 0.0f,
               (f32) (f64) (s32) w, 0.0f, -1.0f);
    GXSetProjection(mtx, 1);
    GXSetViewport(0.0f, 0.0f, (f32) (f64) (s32) w,
                  (f32) (f64) (s32) h, 0.0f, 1.0f);
    GXSetScissor(0, 0, w, h);
    GXSetCurrentMtx(0x3C);
    GXSetZMode(1, 7, 0);
    GXSetBlendMode(0, 1, 0, 0);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetDispCopyGamma(0);
    GXSetNumChans(0);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(1, 1, 5, 0x3C, 0, 0x7D);
    GXInvalidateTexAll();
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxDesc(0xE, 1);
    GXSetVtxAttrFmt(7, 9, 1, 3, 0);
    GXSetVtxAttrFmt(7, 0xD, 1, 2, 0);
    GXSetVtxAttrFmt(7, 0xE, 1, 2, 0);
    fn_8024E2C8(1);
    GXSetNumTevStages();
}
