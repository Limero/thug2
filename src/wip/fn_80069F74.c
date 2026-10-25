// WIP DRAFT (non-matching) — hand reconstruction from the WANT disassembly
// family=m2c range=0x80069F74-0x8006A1D4 size=608B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
#include "types.h"
#include "structs.h"

/* 16-byte block = 2 paired-single registers = 4 floats (want: 2x psq_l/psq_st) */
typedef struct {
    __ps_t p[2];
} Blk16;

/* 64-byte block = 8 paired-single registers = 16 floats (want: 8x psq_l/psq_st) */
typedef struct {
    __ps_t p[8];
} Blk64;

typedef struct Unk_80069F74 {
    u8 unk00;
    char pad01[3];
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    f32 unk10[3];
    f32 unk1C[3];
    s32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    char pad3C[4];
    Blk16 unk40;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    char pad5C[4];
    Blk64 unk60;
    Blk16 unkA0[3];
    Blk16 unkD0[3];
    Blk16 unk100[3];
    f32 unk130;
    s32 unk134[3];
    s32 unk140;
    s32 unk144;
    s32 unk148;
    s32 unk14C;
    s32 unk150;
    s32 unk154;
    s32 unk158;
    u8 unk15C;
    char pad15D[3];
    s32 unk160;
    s32 unk164;
    s32 unk168;
    s32 unk16C;
    s32 unk170;
    s32 unk174;
    s32 unk178;
    s32 unk17C;
} Unk_80069F74;

void *fn_80069F74(Unk_80069F74 *dst, const Unk_80069F74 *src) {
    volatile u8 sp8;
    s32 i;

    sp8 = dst->unk00;
    dst->unk04 = src->unk04;
    dst->unk08 = src->unk08;
    dst->unk0C = src->unk0C;
    for (i = 0; i < 3; i++) {
        dst->unk10[i] = src->unk10[i];
    }
    for (i = 0; i < 3; i++) {
        dst->unk1C[i] = src->unk1C[i];
    }
    dst->unk28 = src->unk28;
    dst->unk2C = src->unk2C;
    dst->unk30 = src->unk30;
    dst->unk34 = src->unk34;
    dst->unk38 = src->unk38;
    dst->unk40 = src->unk40;
    dst->unk50 = src->unk50;
    dst->unk54 = src->unk54;
    dst->unk58 = src->unk58;
    dst->unk60 = src->unk60;
    for (i = 0; i < 3; i++) {
        dst->unkA0[i] = src->unkA0[i];
    }
    for (i = 0; i < 3; i++) {
        dst->unkD0[i] = src->unkD0[i];
    }
    for (i = 0; i < 3; i++) {
        dst->unk100[i] = src->unk100[i];
    }
    dst->unk130 = src->unk130;
    for (i = 0; i < 3; i++) {
        dst->unk134[i] = src->unk134[i];
    }
    dst->unk140 = src->unk140;
    dst->unk144 = src->unk144;
    dst->unk148 = src->unk148;
    dst->unk14C = src->unk14C;
    dst->unk150 = src->unk150;
    dst->unk154 = src->unk154;
    dst->unk158 = src->unk158;
    dst->unk15C = src->unk15C;
    dst->unk160 = src->unk160;
    dst->unk164 = src->unk164;
    dst->unk168 = src->unk168;
    dst->unk16C = src->unk16C;
    dst->unk170 = src->unk170;
    dst->unk174 = src->unk174;
    dst->unk178 = src->unk178;
    dst->unk17C = src->unk17C;
    return dst;
}

// NOTE (2026-10-06, hand reconstruction): the want is a byte-for-byte block
// copy of a 0x180-byte struct (dst = arg0 = r10, src = arg1) that returns dst.
// The copy strategy per member is what pins the layout:
//   0x004 3 words            (3x lwz/stw, straight line)
//   0x010 3 floats           (lfs/stfs under mtctr 3 / bdnz)
//   0x01C 3 floats           (same)
//   0x028 word, 0x02C-0x038 4 floats (straight line)
//   0x040 16 bytes           (2x psq_l/psq_st -> Blk16 struct assign)
//   0x050 3 words
//   0x060 64 bytes           (8x psq_l/psq_st -> Blk64 struct assign)
//   0x0A0/0x0D0/0x100 48B ea (3-iteration loop, 2x psq per iteration -> Blk16[3])
//   0x130 float, 0x134 3 words (mtctr 3 loop)
//   0x140 7 words, 0x15C byte, 0x160 8 words (straight line)
//   0x3C and 0x5C are NOT copied (4 pad bytes each).
// The first byte of dst is read (lbz 0(r10)) and spilled to 8(r1) but never
// read back, so the only way to force that dead store is a volatile local;
// the 0x18 frame (0x10 stmw r30/r31 save area + one 8-byte slot) is exactly
// what one such local costs.
// PARKED 2026-10-06: PS codegen wall. The body above is the faithful
// member-by-member reconstruction; expected residual diffs are the PS
// allocator/merge behaviour on the Blk16/Blk64 moves (retail reuses f0 for
// every 8-byte psq_l/psq_st pair and lowers the Blk16[3] copies to
// mtctr/bdnz loops) plus the exact member split at 0x04/0x10/0x50 (a merged
// struct assign would change the instruction mix). Not compiled here.
