// WIP DRAFT (non-matching) — hand-reconstructed body 2026-10-06.
// Two-layer textured quad emitter: builds three GXTexObjs from one source
// texture (levels 0/1/2, the 2nd and 3rd at half size), loads them into
// texmaps 0/1/2, enables manual tex-coord scaling, then emits a GX_QUADS
// fan of 4 vertices (position + two tex-coord pairs) straight into the FIFO.
// The 28 u16 FIFO writes match the want one-for-one in order; see NOTE below.
// family=m2c range=0x801229CC-0x80122C40 size=628B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

extern char lbl_CC008000[];
extern f32 lbl_8029E244;   /* .rodata2 0.0f (see src/r2d_8029E230.c) */

typedef struct {
    u16 unk0;    /* 0x00 texture S extent (u16 lhz) */
    u16 unk2;    /* 0x02 texture T extent (u16 lhz) */
    u16 unk4;    /* 0x04 level-0 texture width  (u16 lhz) */
    u16 unk6;    /* 0x06 level-0 texture height (u16 lhz) */
    void *unk8;  /* 0x08 level-0 image */
    void *unkC;  /* 0x0C level-1 image */
    void *unk10; /* 0x10 level-2 image */
} TexInfo;

typedef struct {
    u32 texture_filter;
    u32 texture_lod;
    u32 texture_size;
    u32 texture_address;
    u32 user_data;
    u32 texture_format;
    u32 tlut_name;
    u16 texture_time_count;
    u8 texture_tile_type;
    u8 texture_flags;
} GXTexObj;

void GXInitTexObj(GXTexObj *, void *, u16, u16, u32, u32, u32, u32);
void GXInitTexObjLOD(GXTexObj *, u32, u32, f32, f32, f32, u32, u32, u32);
void GXLoadTexObj(GXTexObj *, u32);
void GXSetTexCoordScaleManually(u32, u32, u16, u16);
void GXBegin(u32, u32, u16);

void fn_801229CC(s16 x, s16 y, s16 w, s16 h, TexInfo *p) {
    GXTexObj t0;
    GXTexObj t1;
    GXTexObj t2;
    u16 tw;
    u16 th;
    s16 right;
    s16 bottom;

    tw = p->unk4;
    th = p->unk6;
    GXInitTexObj(&t0, p->unk8, tw, th, 1, 0, 0, 0);
    GXInitTexObjLOD(&t0, 1, 1, lbl_8029E244, lbl_8029E244, lbl_8029E244, 0, 0, 0);
    GXLoadTexObj(&t0, 0);
    tw >>= 1;
    th >>= 1;
    GXInitTexObj(&t1, p->unkC, tw, th, 1, 0, 0, 0);
    GXInitTexObjLOD(&t1, 1, 1, lbl_8029E244, lbl_8029E244, lbl_8029E244, 0, 0, 0);
    GXLoadTexObj(&t1, 1);
    GXInitTexObj(&t2, p->unk10, tw, th, 1, 0, 0, 0);
    GXInitTexObjLOD(&t2, 1, 1, lbl_8029E244, lbl_8029E244, lbl_8029E244, 0, 0, 0);
    GXLoadTexObj(&t2, 2);
    GXSetTexCoordScaleManually(0, 1, 1, 1);
    GXSetTexCoordScaleManually(1, 1, 1, 1);
    GXBegin(0x80, 7, 4);
    right = x + w;
    bottom = y + h;
    /* vertex 0: pos(x, y), tex0(0, 0), tex1(0, 0) */
    *(volatile u16 *)&lbl_CC008000 = x;
    *(volatile u16 *)&lbl_CC008000 = y;
    *(volatile u16 *)&lbl_CC008000 = 0;
    *(volatile u16 *)&lbl_CC008000 = 0;
    *(volatile u16 *)&lbl_CC008000 = 0;
    *(volatile u16 *)&lbl_CC008000 = 0;
    *(volatile u16 *)&lbl_CC008000 = 0;
    /* vertex 1: pos(right, y), tex0(p->unk0, 0), tex1(p->unk0 >> 1, 0) */
    *(volatile u16 *)&lbl_CC008000 = right;
    *(volatile u16 *)&lbl_CC008000 = y;
    *(volatile u16 *)&lbl_CC008000 = 0;
    *(volatile u16 *)&lbl_CC008000 = p->unk0;
    *(volatile u16 *)&lbl_CC008000 = 0;
    *(volatile u16 *)&lbl_CC008000 = p->unk0 >> 1;
    *(volatile u16 *)&lbl_CC008000 = 0;
    /* vertex 2: pos(right, bottom), tex0(p->unk0, p->unk2), tex1(>>1, >>1) */
    *(volatile u16 *)&lbl_CC008000 = right;
    *(volatile u16 *)&lbl_CC008000 = bottom;
    *(volatile u16 *)&lbl_CC008000 = 0;
    *(volatile u16 *)&lbl_CC008000 = p->unk0;
    *(volatile u16 *)&lbl_CC008000 = p->unk2;
    *(volatile u16 *)&lbl_CC008000 = p->unk0 >> 1;
    *(volatile u16 *)&lbl_CC008000 = p->unk2 >> 1;
    /* vertex 3: pos(x, bottom), tex0(0, p->unk2), tex1(0, p->unk2 >> 1) */
    *(volatile u16 *)&lbl_CC008000 = x;
    *(volatile u16 *)&lbl_CC008000 = bottom;
    *(volatile u16 *)&lbl_CC008000 = 0;
    *(volatile u16 *)&lbl_CC008000 = 0;
    *(volatile u16 *)&lbl_CC008000 = p->unk2;
    *(volatile u16 *)&lbl_CC008000 = 0;
    *(volatile u16 *)&lbl_CC008000 = p->unk2 >> 1;
    GXSetTexCoordScaleManually(0, 0, 1, 1);
    GXSetTexCoordScaleManually(1, 0, 1, 1);
}

// NOTE (0x801229CC, 628B, 14 calls, no FPR frame): signature recovered from
// r3..r7 -> x(s16), y(s16), w(s16), h(s16), p(TexInfo*); r27/r28 = lhz 4/6(p)
// are the level-0 dims, halved in place for levels 1/2 (the want's
// `srwi r27,r27,1` destroys them right after the first call's arg copies, so
// the source halves `tw`/`th` between the first and second GXInitTexObj).
// `right`/`bottom` are s16 because the want emits `add` + `extsh` for both
// sums (an int-typed sum would emit a bare `add`).
// Every GXInitTexObjLOD passes 0.0f for min/max/bias (lbl_8029E244) and
// (1, 1) filters + (0, 0, 0) flags; each call re-loads the constant because
// the symbol is non-const and the calls in between may clobber it (matches the
// want's three separate `lfs f1, -0x1dbc(r25)` with one shared `lis r25`).
// The 28 FIFO u16 writes are byte-for-byte the want's sequence (7 values per
// vertex = pos3 + tex0 pair + tex1 pair), and the volatile stores force the
// repeated `lhz 0(r30)` / `lhz 2(r30)` reloads seen in the want.
// PARKED 2026-10-06: body is a full semantic reconstruction (all 14 calls,
// arg registers and store order pinned against the want) but it could not be
// compiled/verified in this round — the residual risk is scheduling, not
// structure: the want hoists the two `srwi`, the `lis r25` and the final
// GXSetTexCoordScaleManually argument setup across the surrounding calls,
// which GCC 2.95's scheduler may place differently.
