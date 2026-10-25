// WIP DRAFT (non-matching) — hand-rewritten from the retail disassembly.
// family=m2c range=0x8007A334-0x8007A9F8 size=1732B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (park-8007A334-lfscale): best measured 0.50% masked,
// DIFF, object 1612B vs want 1732B (120B short), frame -0x90 vs want -0xb0.
// (The m2c draft this replaced measured 1.15% but was semantically broken —
// see the "superseded" note at the bottom; its higher number was alignment
// luck on a 340B-short object, not a better body.)
//
// What this rewrite fixed vs the m2c body (all verified against retail bytes):
//  * lbl_8029585C/6C are 16-byte (4×s32) objects — m2c used the 64-byte
//    Unk_59AB5482, which is what blew the old frame out to -0x100.
//  * fn_8007A2A8 is `u32 f(u16 *)`; m2c declared a 6-arg s32 stub.
//  * sp39/sp3B were file-scope `static s32` in m2c; they are stack bytes
//    (0x39/0x3b) inside the 16-bit pack pair at 0x38/0x3a.
//  * the palette bytes are the packed 5/6-bit fields LEFT-ALIGNED in the
//    byte: pal.b[0] = (w >> 24) & 0xF8, pal.b[1] = (w >> 19) & 0xFC,
//    pal.b[2] = (w >> 13) & 0xF8. m2c had them as plain 5/6-bit values,
//    which produces a different rlwinm encoding (verified by probe:
//    `(u8)((x>>16)<<3)` != `(x>>16)&0x1F` for ngccc).
//  * the pack pair is built through a reused temp (`tv`), which is what
//    makes ngccc emit `lbz 0x39 / slwi / or / sth 0x38 / rlwinm &0xFF00 /
//    or / sth` instead of a `lhz` reload.
//  * the source record pointer is loop-carried across the whole i/j/k/l
//    nest (retail keeps it in a callee-saved reg for the entire function).
//
// Residual: everything is offset ~9 instructions from the loop preamble
// because retail hoists eight loop-invariant address/constant registers
// (r15-r18, r20, r22, r23, r27=0xFF, r30=0x55555556, r12=1) plus spills
// sp4C/sp48/sp50/sp60 to the stack, while ngccc register-promotes them here
// (frame -0x90, not -0xb0). Also unmatched: retail's second extract load is
// `lwz r8, 0x3a(r1)` (a 32-bit window straddling the pack pair's upper
// halfword and the call-result word); this body uses a clean `pk.w[1]` at
// 0x3c, which is the only formulation expressible without overlapping C
// objects. Ruled out: bitfield structs (ngccc emits rlwimi, not the retail
// rlwinm masks); (x>>16)&0x1F style shifts (wrong rlwinm encoding — the
// retail form is `&0xF8`/`&0xFC`); making sp54/sp58 real memory slots (ngccc
// folds them to r1+0x38 / 3(reg)); forcing the frame with volatile or
// address-taken dummies (not in the original source).
#include "types.h"

typedef struct {
    s32 v[4];
} Quad;

typedef struct {
    u8 f6;
    u8 f7;
    u16 flags;
    s32 *unk10;
    s32 *unk14;
    s32 *unk18;
} Img;

typedef struct {
    Img *unkC;
} Obj;

typedef union {
    u32 w[4];
    u8 b[16];
} Pal;

typedef union {
    u32 w[2];
    u16 h[4];
    u8 b[8];
} Pk;

extern Quad lbl_8029585C;
extern Quad lbl_8029586C;

u32 fn_8007A2A8(u16 *arg0);

void fn_8007A334(Obj *arg0) {
    Img *t;
    Quad sp8;
    Quad sp18;
    Pal pal;
    Pk pk;
    s32 sp40, sp44, sp48, sp4C, sp50;
    u8 *sp54;
    u8 *sp58;
    s32 i, j, k, l, m, n;
    u8 *p;
    u32 tv;

    t = arg0->unkC;
    sp8 = lbl_8029585C;
    sp44 = (((u32)1 << t->f7) >> 3) & 0x1FFF;
    sp40 = (((u32)1 << t->f6) >> 3) & 0x1FFF;
    sp18 = lbl_8029586C;

    p = (u8 *)t->unk10;
    i = 0;
    while (i < sp44) {
        sp4C = i + 1;
        j = 0;
        while (j < sp40) {
            sp50 = i * 8;
            sp48 = j + 1;
            for (k = 0; k < 2; k++) {
                for (l = 0; l < 2; l++) {
                    tv = pk.b[1] | ((u32)p[0] << 8);
                    pk.h[0] = (u16)tv;
                    tv = (tv & 0xFF00) | p[1];
                    pk.h[0] = (u16)tv;
                    tv = pk.b[3] | ((u32)p[2] << 8);
                    pk.h[1] = (u16)tv;
                    tv = (tv & 0xFF00) | p[3];
                    pk.h[1] = (u16)tv;

                    pal.b[3] = 0xFF;
                    pal.b[0] = (pk.w[0] >> 24) & 0xF8;
                    pal.b[1] = (pk.w[0] >> 19) & 0xFC;
                    pal.b[2] = (pk.w[0] >> 13) & 0xF8;
                    pal.b[7] = 0xFF;
                    pal.b[5] = (pk.w[1] >> 19) & 0xFC;
                    pal.b[4] = (pk.w[1] >> 24) & 0xF8;
                    pal.b[6] = (pk.w[1] >> 13) & 0xF8;
                    pal.b[8] = (pal.b[1] * 2 + pal.b[5]) / 3;
                    pal.b[9] = (pal.b[2] * 2 + pal.b[6]) / 3;
                    pal.b[10] = (pal.b[0] * 2 + pal.b[4]) / 3;
                    pal.b[11] = 0xFF;
                    pal.b[12] = (pal.b[0] + pal.b[4] * 2) / 3;
                    pal.b[13] = (pal.b[1] + pal.b[5] * 2) / 3;
                    pal.b[14] = (pal.b[2] + pal.b[6] * 2) / 3;
                    pal.b[15] = 0xFF;

                    pk.w[1] = fn_8007A2A8((u16 *)(p + 4));

                    for (m = 0; m < 4; m++) {
                        for (n = 0; n < 4; n++) {
                            s32 *dst = t->unk18 + (sp50 + k * 4 + m) * (s32)(u16)(1 << t->f6) + j * 8 + l * 4 + n;
                            u32 sel = ((u32)pk.b[4 + m] & sp8.v[n]) >> sp18.v[n];

                            switch (sel) {
                            case 0: *dst = pal.w[0]; break;
                            case 1: *dst = pal.w[1]; break;
                            case 2: *dst = pal.w[2]; break;
                            case 3: *dst = pal.w[3]; break;
                            }
                        }
                    }
                    p += 8;
                }
            }
            j = sp48;
        }
        i = sp4C;
    }

    if (t->unk14 != 0 && (t->flags & 2)) {
        p = (u8 *)t->unk14;
        i = 0;
        while (i < sp44) {
            sp4C = i + 1;
            j = 0;
            while (j < sp40) {
                sp50 = i * 8;
                sp48 = j + 1;
                for (k = 0; k < 2; k++) {
                    for (l = 0; l < 2; l++) {
                        sp54 = pk.b;
                        sp58 = pk.b + 2;
                        sp54[0] = p[0];
                        sp54[1] = p[1];
                        sp58[0] = p[2];
                        sp58[1] = p[3];

                        pal.b[3] = 0xFF;
                        pal.b[0] = (pk.w[0] >> 24) & 0xF8;
                        pal.b[1] = (pk.w[0] >> 19) & 0xFC;
                        pal.b[2] = (pk.w[0] >> 13) & 0xF8;
                        pal.b[7] = 0xFF;
                        pal.b[5] = (pk.w[1] >> 19) & 0xFC;
                        pal.b[4] = (pk.w[1] >> 24) & 0xF8;
                        pal.b[6] = (pk.w[1] >> 13) & 0xF8;
                        pal.b[8] = (pal.b[1] * 2 + pal.b[5]) / 3;
                        pal.b[9] = (pal.b[2] * 2 + pal.b[6]) / 3;
                        pal.b[10] = (pal.b[0] * 2 + pal.b[4]) / 3;
                        pal.b[11] = 0xFF;
                        pal.b[12] = (pal.b[0] + pal.b[4] * 2) / 3;
                        pal.b[13] = (pal.b[1] + pal.b[5] * 2) / 3;
                        pal.b[14] = (pal.b[2] + pal.b[6] * 2) / 3;
                        pal.b[15] = 0xFF;

                        pk.w[1] = fn_8007A2A8((u16 *)(p + 4));

                        if (t->flags & 4) {
                            pal.b[3] = pal.b[1];
                            pal.b[7] = pal.b[5];
                            pal.b[11] = pal.b[9];
                            pal.b[15] = pal.b[13];
                        }
                        if (t->flags & 8) {
                            pal.b[3] = pal.b[0];
                            pal.b[7] = pal.b[4];
                            pal.b[11] = pal.b[8];
                            pal.b[15] = pal.b[12];
                        }
                        if (t->flags & 0x10) {
                            pal.b[3] = pal.b[2];
                            pal.b[7] = pal.b[6];
                            pal.b[11] = pal.b[10];
                            pal.b[15] = pal.b[14];
                        }

                        for (m = 0; m < 4; m++) {
                            for (n = 0; n < 4; n++) {
                                s32 *dst = t->unk18 + (sp50 + k * 4 + m) * (s32)(u16)(1 << t->f6) + j * 8 + l * 4 + n;
                                u32 sel = ((u32)pk.b[4 + m] & sp8.v[n]) >> sp18.v[n];

                                switch (sel) {
                                case 0: *dst = (*dst & 0xFFFFFF00) | pal.b[3]; break;
                                case 1: *dst = (*dst & 0xFFFFFF00) | pal.b[7]; break;
                                case 2: *dst = (*dst & 0xFFFFFF00) | pal.b[11]; break;
                                case 3: *dst = (*dst & 0xFFFFFF00) | pal.b[15]; break;
                                }
                            }
                        }
                        p += 8;
                    }
                }
                j = sp48;
            }
            i = sp4C;
        }
    }
}

// Superseded measurements (kept for the record):
//  * 1.26% — same body but with `p = (u8 *)t->unk10;` *inside* the l loop.
//    That variant scores higher only because it lets ngccc drop the
//    loop-carried pointer, and it is WRONG: all four (k,l) passes re-read
//    record 0 instead of four consecutive records. Not kept.
//  * 0.25% / 0.49% — loop-carried source index (`rec`) and a hoisted
//    destination base pointer; both correct, both worse on the metric.
