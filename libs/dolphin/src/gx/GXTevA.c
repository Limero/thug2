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

static struct {
    u32 rid : 8;
    u32 dest : 2;
    u32 shift : 2;
    u32 clamp : 1;
    u32 sub : 1;
    u32 bias : 2;
    u32 sela : 4;
    u32 selb : 4;
    u32 selc : 4;
    u32 seld : 4;
} TEVCOpTableST0[5] = {
    {192, 0, 0, 1, 0, 0, 15, 8, 10, 15},   // modulate
    {192, 0, 0, 1, 0, 0, 10, 8, 9, 15},    // decal
    {192, 0, 0, 1, 0, 0, 10, 12, 8, 15},   // blend
    {192, 0, 0, 1, 0, 0, 15, 15, 15, 8},   // replace
    {192, 0, 0, 1, 0, 0, 15, 15, 15, 10},  // passclr
};

static struct {
    u32 rid : 8;
    u32 dest : 2;
    u32 shift : 2;
    u32 clamp : 1;
    u32 sub : 1;
    u32 bias : 2;
    u32 sela : 4;
    u32 selb : 4;
    u32 selc : 4;
    u32 seld : 4;
} TEVCOpTableST1[5] = {
    {192, 0, 0, 1, 0, 0, 15, 8, 0, 15},    // modulate
    {192, 0, 0, 1, 0, 0, 0, 8, 9, 15},     // decal
    {192, 0, 0, 1, 0, 0, 0, 12, 8, 15},    // blend
    {192, 0, 0, 1, 0, 0, 15, 15, 15, 8},   // replace
    {192, 0, 0, 1, 0, 0, 15, 15, 15, 0},   // passclr
};

static struct {
    u32 rid : 8;
    u32 dest : 2;
    u32 shift : 2;
    u32 clamp : 1;
    u32 sub : 1;
    u32 bias : 2;
    u32 sela : 3;
    u32 selb : 3;
    u32 selc : 3;
    u32 seld : 3;
    u32 swap : 2;
    u32 mode : 2;
} TEVAOpTableST0[5] = {
    {193, 0, 0, 1, 0, 0, 7, 4, 5, 7, 0, 0},  // modulate
    {193, 0, 0, 1, 0, 0, 7, 7, 7, 5, 0, 0},  // decal
    {193, 0, 0, 1, 0, 0, 7, 4, 5, 7, 0, 0},  // blend
    {193, 0, 0, 1, 0, 0, 7, 7, 7, 4, 0, 0},  // replace
    {193, 0, 0, 1, 0, 0, 7, 7, 7, 5, 0, 0},  // passclr
};

static struct {
    u32 rid : 8;
    u32 dest : 2;
    u32 shift : 2;
    u32 clamp : 1;
    u32 sub : 1;
    u32 bias : 2;
    u32 sela : 3;
    u32 selb : 3;
    u32 selc : 3;
    u32 seld : 3;
    u32 swap : 2;
    u32 mode : 2;
} TEVAOpTableST1[5] = {
    {193, 0, 0, 1, 0, 0, 7, 4, 0, 7, 0, 0},  // modulate
    {193, 0, 0, 1, 0, 0, 7, 7, 7, 0, 0, 0},  // decal
    {193, 0, 0, 1, 0, 0, 7, 4, 0, 7, 0, 0},  // blend
    {193, 0, 0, 1, 0, 0, 7, 7, 7, 4, 0, 0},  // replace
    {193, 0, 0, 1, 0, 0, 7, 7, 7, 0, 0, 0},  // passclr
};

void GXSetTevOp(GXTevStageID id, GXTevMode mode) {
    u32* ctmp;
    u32* atmp;
    u32 tevReg;

    CHECK_GXBEGIN(420, "GXSetTevOp");
    ASSERTMSGLINE(421, id < GX_MAX_TEVSTAGE, "GXSetTevColor*: Invalid Tev Stage Index");
    ASSERTMSGLINE(422, mode <= GX_PASSCLR, "GXSetTevOp: Invalid Tev Mode");

    if (id == GX_TEVSTAGE0) {
        ctmp = (u32*)TEVCOpTableST0 + mode;
        atmp = (u32*)TEVAOpTableST0 + mode;
    } else {
        ctmp = (u32*)TEVCOpTableST1 + mode;
        atmp = (u32*)TEVAOpTableST1 + mode;
    }

    tevReg = gx->tevc[id];
    tevReg = (*ctmp & ~0xFF000000) | (tevReg & 0xFF000000);
    GX_WRITE_RAS_REG(tevReg);
    gx->tevc[id] = tevReg;

    tevReg = gx->teva[id];
    tevReg = (*atmp & ~0xFF00000F) | (tevReg & 0xFF00000F);
    GX_WRITE_RAS_REG(tevReg);
    gx->teva[id] = tevReg;

    gx->bpSentNot = 0;
}
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d) {
    u32 tevReg;

    CHECK_GXBEGIN(578, "GXSetTevColorIn");
    ASSERTMSGLINE(579, stage < GX_MAX_TEVSTAGE, "GXSetTevColor*: Invalid Tev Stage Index");
    ASSERTMSGLINE(580, a <= GX_CC_ZERO, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(581, b <= GX_CC_ZERO, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(582, c <= GX_CC_ZERO, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(583, d <= GX_CC_ZERO, "GXSetTev*In: A/B/C/D argument out of range");

    tevReg = gx->tevc[stage];
    SET_REG_FIELD(586, tevReg, 4, 12, a);
    SET_REG_FIELD(587, tevReg, 4,  8, b);
    SET_REG_FIELD(588, tevReg, 4,  4, c);
    SET_REG_FIELD(589, tevReg, 4,  0, d);

    GX_WRITE_RAS_REG(tevReg);
    gx->tevc[stage] = tevReg;
    gx->bpSentNot = 0;
}
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d) {
    u32 tevReg;

    CHECK_GXBEGIN(614, "GXSetTevAlphaIn");
    ASSERTMSGLINE(615, stage < GX_MAX_TEVSTAGE, "GXSetTevAlpha*: Invalid Tev Stage Index");
    ASSERTMSGLINE(616, a <= GX_CA_ZERO, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(617, b <= GX_CA_ZERO, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(618, c <= GX_CA_ZERO, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(619, d <= GX_CA_ZERO, "GXSetTev*In: A/B/C/D argument out of range");

    tevReg = gx->teva[stage];
    SET_REG_FIELD(622, tevReg, 3, 13, a);
    SET_REG_FIELD(623, tevReg, 3, 10, b);
    SET_REG_FIELD(624, tevReg, 3,  7, c);
    SET_REG_FIELD(625, tevReg, 3,  4, d);

    GX_WRITE_RAS_REG(tevReg);
    gx->teva[stage] = tevReg;
    gx->bpSentNot = 0;
}
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg) {
    u32 tevReg;

    CHECK_GXBEGIN(653, "GXSetTevColorOp");
    ASSERTMSGLINE(654, stage < GX_MAX_TEVSTAGE, "GXSetTevColor*: Invalid Tev Stage Index");

    tevReg = gx->tevc[stage];
    SET_REG_FIELD(663, tevReg, 1, 18, op & 1);
    if (op <= 1) {
        SET_REG_FIELD(665, tevReg, 2, 20, scale);
        SET_REG_FIELD(666, tevReg, 2, 16, bias);
    } else {
        SET_REG_FIELD(668, tevReg, 2, 20, (op >> 1) & 3);
        SET_REG_FIELD(672, tevReg, 2, 16, 3);
    }
    SET_REG_FIELD(672, tevReg, 1, 19, clamp & 0xFF);
    SET_REG_FIELD(673, tevReg, 2, 22, out_reg);

    GX_WRITE_RAS_REG(tevReg);
    gx->tevc[stage] = tevReg;
    gx->bpSentNot = 0;
}
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg) {
    u32 tevReg;

    CHECK_GXBEGIN(699, "GXSetTevAlphaOp");
    ASSERTMSGLINE(700, stage < GX_MAX_TEVSTAGE, "GXSetTevAlpha*: Invalid Tev Stage Index");

    tevReg = gx->teva[stage];
    SET_REG_FIELD(708, tevReg, 1, 18, op & 1);
    if (op <= 1) {
        SET_REG_FIELD(710, tevReg, 2, 20, scale);
        SET_REG_FIELD(711, tevReg, 2, 16, bias);
    } else {
        SET_REG_FIELD(713, tevReg, 2, 20, (op >> 1) & 3);
        SET_REG_FIELD(717, tevReg, 2, 16, 3);
    }
    SET_REG_FIELD(717, tevReg, 1, 19, clamp & 0xFF);
    SET_REG_FIELD(718, tevReg, 2, 22, out_reg);

    GX_WRITE_RAS_REG(tevReg);
    gx->teva[stage] = tevReg;
    gx->bpSentNot = 0;
}
