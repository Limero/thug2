#include <dolphin/gx.h>
#include <dolphin/os.h>

#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>

// thug2's GXTev uses the public gx global (GXInit.h GXData layout), not the
// internal __GXData struct from bfbb's __gx.h (which is 0xB8 larger). The DOL
// accesses texmapId@0x49C / tevTcEnab@0x4E0 / dirtyState@0x4F4.
#ifndef OLD_SET_REG_FIELD
#define OLD_SET_REG_FIELD(line, reg, size, shift, val) \
do { \
    ASSERTMSGLINE(line, ((u32)(val) & ~((1 << (size)) - 1)) == 0, "GX Internal: Register field out of range"); \
    (reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)); \
} while (0)
#endif

// GX.h defines a 4-arg SET_REG_FIELD; the GXTev sources use the 5-arg
// (line-number) form from bfbb's __gx.h. Undef and redefine to match.
#ifdef SET_REG_FIELD
#undef SET_REG_FIELD
#endif
#define SET_REG_FIELD(line, reg, size, shift, val) \
do { \
    ASSERTMSGLINE(line, ((u32)(val) & ~((1 << (size)) - 1)) == 0, "GX Internal: Register field out of range"); \
    (reg) = ((u32)__rlwimi((u32)(reg), (val), (shift), 32 - (shift) - (size), 31 - (shift))); \
} while (0)

#ifndef CHECK_GXBEGIN
#define CHECK_GXBEGIN(line, name) ASSERTMSGLINE(line, !__GXinBegin, "'" name "' is not allowed between GXBegin/GXEnd")
#endif

#ifndef __GXinBegin
extern u8 __GXinBegin;
#endif

void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel) {
    u32* Kreg;

    CHECK_GXBEGIN(872, "GXSetTevKColorSel");
    ASSERTMSGLINE(873, stage < GX_MAX_TEVSTAGE, "GXSetTevKColor*: Invalid Tev Stage Index");

    Kreg = &gx->tevKsel[stage >> 1];
    if (stage & 1) {
        OLD_SET_REG_FIELD(0x36E, *Kreg, 5, 14, sel);
    } else {
        OLD_SET_REG_FIELD(0x370, *Kreg, 5, 4, sel);
    }

    GX_WRITE_RAS_REG(*Kreg);
    gx->bpSentNot = 0;
}
void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel) {
    u32* Kreg;

    CHECK_GXBEGIN(905, "GXSetTevKAlphaSel");
    ASSERTMSGLINE(906, stage < GX_MAX_TEVSTAGE, "GXSetTevKColor*: Invalid Tev Stage Index");

    Kreg = &gx->tevKsel[stage >> 1];
    if (stage & 1) {
        OLD_SET_REG_FIELD(911, *Kreg, 5, 19, sel);
    } else {
        OLD_SET_REG_FIELD(913, *Kreg, 5, 9, sel);
    }

    GX_WRITE_RAS_REG(*Kreg);
    gx->bpSentNot = 0;
}
void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel) {
    u32* pTevReg;

    CHECK_GXBEGIN(942, "GXSetTevSwapMode");
    ASSERTMSGLINE(943, stage < GX_MAX_TEVSTAGE, "GXSetTevSwapMode: Invalid Tev Stage Index");

    pTevReg = &gx->teva[stage];
    OLD_SET_REG_FIELD(946, *pTevReg, 2, 0, ras_sel);
    OLD_SET_REG_FIELD(947, *pTevReg, 2, 2, tex_sel);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSentNot = 0;
}
void GXSetTevSwapModeTable(GXTevSwapSel table, GXTevColorChan red, GXTevColorChan green, GXTevColorChan blue, GXTevColorChan alpha) {
    u32* Kreg;
#if !DEBUG
    // not a real variable, but needed to match release
    int index = table * 2;
#endif

    CHECK_GXBEGIN(978, "GXSetTevSwapModeTable");
    ASSERTMSGLINE(979, table < GX_MAX_TEVSWAP, "GXSetTevSwapModeTable: Invalid Swap Selection Index");

#if DEBUG
    Kreg = &gx->tevKsel[table * 2];
#else
    Kreg = &gx->tevKsel[index];
#endif
    OLD_SET_REG_FIELD(982, *Kreg, 2, 0, red);
    OLD_SET_REG_FIELD(983, *Kreg, 2, 2, green);

    GX_WRITE_RAS_REG(*Kreg);

    Kreg = &gx->tevKsel[table * 2 + 1];
    OLD_SET_REG_FIELD(987, *Kreg, 2, 0, blue);
    OLD_SET_REG_FIELD(988, *Kreg, 2, 2, alpha);

    GX_WRITE_RAS_REG(*Kreg);
    gx->bpSentNot = 0;
}
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1) {
    u32 reg;

    CHECK_GXBEGIN(1046, "GXSetAlphaCompare");
    reg = 0xF3000000;

    OLD_SET_REG_FIELD(1049, reg, 8, 0, ref0);
    OLD_SET_REG_FIELD(1050, reg, 8, 8, ref1);
    OLD_SET_REG_FIELD(1051, reg, 3, 16, comp0);
    OLD_SET_REG_FIELD(1052, reg, 3, 19, comp1);
    OLD_SET_REG_FIELD(1053, reg, 2, 22, op);

    GX_WRITE_RAS_REG(reg);
    gx->bpSentNot = 0;
}
void GXSetZTexture(GXZTexOp op, GXTexFmt fmt, u32 bias) {
    u32 zenv0;
    u32 zenv1;
    u32 type;

    CHECK_GXBEGIN(1077, "GXSetZTexture");

    zenv0 = 0;
    OLD_SET_REG_FIELD(1080, zenv0, 8, 0, bias);
    OLD_SET_REG_FIELD(1081, zenv0, 8, 24, 0xF4);

    zenv1 = 0;
    switch (fmt) {
    case GX_TF_Z8:
        type = 0;
        break;
    case GX_TF_Z16:
        type = 1;
        break;
    case GX_TF_Z24X8:
        type = 2;
        break;
    default:
        ASSERTMSGLINE(1089, 0, "GXSetZTexture: Invalid z-texture format");
        type = 2;
        break;
    }

    OLD_SET_REG_FIELD(1092, zenv1, 2, 0, type);
    OLD_SET_REG_FIELD(1093, zenv1, 2, 2, op);
    OLD_SET_REG_FIELD(1094, zenv1, 8, 24, 0xF5);

    GX_WRITE_RAS_REG(zenv0);
    GX_WRITE_RAS_REG(zenv1);
    gx->bpSentNot = 0;
}
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color) {
    u32* ptref;
    u32 tmap;
    u32 tcoord;
    static int c2r[] = { 0, 1, 0, 1, 0, 1, 7, 5, 6 };

    CHECK_GXBEGIN(1131, "GXSetTevOrder");
    ASSERTMSGLINE(1132, stage < GX_MAX_TEVSTAGE, "GXSetTevOrder: Invalid Tev Stage Index");
    ASSERTMSGLINE(1134, coord < GX_MAX_TEXCOORD || coord == GX_TEXCOORD_NULL, "GXSetTevOrder: Invalid Texcoord");
    ASSERTMSGLINE(1136, (map & ~GX_TEX_DISABLE) < GX_MAX_TEXMAP || map == GX_TEXMAP_NULL, "GXSetTevOrder: Invalid Tex Map");
    ASSERTMSGLINE(1138, color >= GX_COLOR0A0 && color <= GX_COLOR_NULL, "GXSetTevOrder: Invalid Color Channel ID");

    ptref = &gx->tref[stage / 2];
    gx->texmapId[stage] = map;

    tmap = map & ~GX_TEX_DISABLE;
    tmap = (tmap >= GX_MAX_TEXMAP) ? GX_TEXMAP0 : tmap;

    if (coord >= GX_MAX_TEXCOORD) {
        tcoord = GX_TEXCOORD0;
        gx->tevTcEnab = gx->tevTcEnab & ~(1 << stage);
    } else {
        tcoord = coord;
        gx->tevTcEnab = gx->tevTcEnab | (1 << stage);
    }

    if (stage & 1) {
        OLD_SET_REG_FIELD(1158, *ptref, 3, 12, tmap);
        OLD_SET_REG_FIELD(1159, *ptref, 3, 15, tcoord);
        OLD_SET_REG_FIELD(1161, *ptref, 3, 19, (color == GX_COLOR_NULL) ? 7 : c2r[color]);
        OLD_SET_REG_FIELD(1163, *ptref, 1, 18, (map != GX_TEXMAP_NULL && !(map & GX_TEX_DISABLE)));
    } else {
        OLD_SET_REG_FIELD(1166, *ptref, 3, 0, tmap);
        OLD_SET_REG_FIELD(1167, *ptref, 3, 3, tcoord);
        OLD_SET_REG_FIELD(1169, *ptref, 3, 7, (color == GX_COLOR_NULL) ? 7 : c2r[color]);
        OLD_SET_REG_FIELD(1171, *ptref, 1, 6, (map != GX_TEXMAP_NULL && !(map & GX_TEX_DISABLE)));
    }

    GX_WRITE_RAS_REG(*ptref);
    gx->bpSentNot = 0;
    gx->dirtyState |= 1;
}
void GXSetNumTevStages(u8 nStages) {
    CHECK_GXBEGIN(1187, "GXSetNumTevStages");

    ASSERTMSGLINE(1189, nStages != 0 && nStages <= 16, "GXSetNumTevStages: Exceed max number of tex stages");
    OLD_SET_REG_FIELD(1190, gx->genMode, 4, 10, nStages - 1);
    gx->dirtyState |= 4;
}
