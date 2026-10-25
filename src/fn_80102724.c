// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80102724-0x8010284C (296B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_80102724(Unk_132A52FF *arg0, void *arg1) {
    __ps_t *src = (__ps_t *)arg1;
    f32 g20;
    f32 g30;
    f32 g50;
    f32 g40;
    f32 g44;
    f32 g48;
    f32 g4C;
    f32 g24;
    f32 g34;
    f32 g54;
    f32 g28;
    f32 g38;
    f32 g2C;
    f32 g58;
    f32 g3C;
    f32 g5C;

    ((__ps_t *)((char *)arg0 + 0x20))[0] = src[0];
    ((__ps_t *)((char *)arg0 + 0x20))[1] = src[1];
    ((__ps_t *)((char *)arg0 + 0x20))[2] = src[2];
    {
        __ps_t *mid = (__ps_t *)((char *)arg0 + 0x20);
        __ps_t *end = (__ps_t *)((char *)arg0 + 0x60);

        mid[3] = src[3];
        {
            __ps_t *tail = mid + 4;
            tail[0] = src[4];
            tail[1] = src[5];
        }

    if (mid == end) {
        f32 a0;
        f32 b0;
        f32 a1;
        f32 b1;
        f32 a2;
        f32 b2;
        f32 a3;
        f32 b3;
        f32 a4;
        f32 b4;
        f32 a5;
        f32 b5;
        a0 = arg0->unk0x64;
        b0 = arg0->unk0x70;
        arg0->unk0x64 = b0;
        arg0->unk0x70 = a0;
        a1 = arg0->unk0x68;
        b1 = ((f32 *)mid)[8];
        arg0->unk0x68 = b1;
        ((f32 *)mid)[8] = a1;
        a2 = arg0->unk0x6C;
        b2 = arg0->unk0x90;
        arg0->unk0x6C = b2;
        arg0->unk0x90 = a2;
        a3 = arg0->unk0x78;
        b3 = ((f32 *)mid)[9];
        arg0->unk0x78 = b3;
        ((f32 *)mid)[9] = a3;
        a4 = arg0->unk0x7C;
        b4 = arg0->unk0x94;
        arg0->unk0x7C = b4;
        arg0->unk0x94 = a4;
        a5 = arg0->unk0x98;
        b5 = ((f32 *)mid)[11];
        ((f32 *)mid)[11] = a5;
        arg0->unk0x98 = b5;
        return;
    }

    g20 = *((f32 *)&arg0->unk0x20);
    g30 = arg0->unk0x30;
    arg0->unk0x60 = g20;
    arg0->unk0x64 = g30;
    g40 = ((f32 *)mid)[8];
    g50 = arg0->unk0x50;
    g24 = arg0->unk0x24;
    g34 = arg0->unk0x34;
    arg0->unk0x68 = g40;
    arg0->unk0x6C = g50;
    arg0->unk0x70 = g24;
    arg0->unk0x74 = g34;
    g54 = arg0->unk0x54;
    g44 = ((f32 *)mid)[9];
    g28 = arg0->unk0x28;
    g38 = arg0->unk0x38;
    arg0->unk0x78 = g44;
    arg0->unk0x7C = g54;
    *((f32 *)&arg0->unk0x80) = g28;
    arg0->unk0x84 = g38;
    g48 = ((f32 *)mid)[10];
    g58 = arg0->unk0x58;
    g2C = arg0->unk0x2C;
    g3C = arg0->unk0x3C;
    arg0->unk0x88 = g48;
    arg0->unk0x8C = g58;
    arg0->unk0x90 = g2C;
    arg0->unk0x94 = g3C;
    g5C = arg0->unk0x5C;
    g4C = ((f32 *)mid)[11];
    arg0->unk0x9C = g5C;
    arg0->unk0x98 = g4C;
    }
}

/* SOLVED 2026-09-29: EXACT 100.0% (74/74 words, size-exact 296B), -mps-float,
 * 0 emitted asm. The last two mid pair-stores (mid[4], mid[5]) now go through
 * their own mid-derived base `__ps_t *tail = mid + 4` (tail[0], tail[1]).
 * The extra pointer level stops the RTL combiner from canonicalizing
 * mid+40 -> arg0+72, so the stores emit via r9+32/r9+40 like want instead
 * of folding onto the arg0 (r3) base. (Previously parked 73/74: single word
 * at +0x38, want `psq_st f0,40(r9)` vs got `psq_st f0,72(r3)`.)
 * GUESS: copies a 12-float block from arg1 to obj+0x20, then shuffles the
 * 16 floats at +0x20..+0x5C into +0x60..+0x9C (vertex/blend-shape setup?);
 * the mid==end swap branch is dead (offsets of one base, never equal).
 */
