// WIP DRAFT (non-matching) — fully re-decompiled from the WANT disassembly
// (the old m2c body was DIFF 3.1% and had the wrong frame, the wrong callee
// prototypes, a bogus 6-arg fn_8001B6DC call and a wrong loop shape).
// family=m2c range=0x80121D80-0x8012227C size=1276B
//
// RE-TRIAGED 2026-10-17: still 15.7% (re-measured), body unchanged. The
// residual analysis below stands (second manager-pointer copy + lis pairs,
// two reg swaps, sunk fail block, store groups); no fresh lever. Parking.
// PARKED 2026-10-05 (regalloc): best measured = 15.8% masked index-aligned
// (tools/score_wip.py; official verdict DIFF) and 76.8% when the two streams are
// opcode-aligned first (245/319 words match relocation-masked). Frame and
// register count now match WANT (stwu -0x50 / stmw r19 / 13 callee-saved);
// the object is 1264B vs the 1276B want, i.e. still 3 words short.
//
// What this body decodes (from WANT):
//   s32 fn_80121D80(char *name, s32 audioAllowed)
//     Opens the QB video stream `name` into the global stream manager
//     lbl_8039BA58 (struct Mgr below):
//       - bail out with 0 if a stream is already open (mgr.open != 0);
//       - fn_8001B658(f, name) opens the file handle f = lbl_8039B9E0;
//       - read a 32-byte chunk header (lbl_8039BE00) and require tag 'VID1'
//         plus (hdr.vid.version & 0xFFFF0000) == 0x01000000;
//       - read the next header, require tag 'HEAD'; mgr.offset = len + 0x20;
//         fn_8001B718(f, 0, 0x2C) skips 0x2C bytes; mgr.state = 'NONE';
//       - walk the chunk list with `rem = len - 0xC` while rem > 0x1F:
//           * every iteration consumes the 0x20-byte header (rem -= 0x20);
//           * 'VIDH' -> fix up the 0x1C/0x1E halfword pair when hdr.unk8==0,
//             assert len <= 0x20 twice (lines 0x287/0x288), copy four words
//             into mgr.vid, and stash lbl_8039BE0C into lbl_8039BAE0;
//           * 'AUDH' (and only when arg1 == 0) -> mgr.audio =
//             mgr.alloc(len), struct-copy the 32-byte header into it, take the
//             rest of the chunk with fn_8001B6DC, rem -= (len - 0x20), then
//             memcpy(lbl_8039BAF8, mgr.audio + 0xC, min(len - 0xC, 0x21A));
//           * anything else -> rem = rem + 0x20 - len;
//       - assert mgr.vid.width/height and mgr.vid.f8 (maxBuf) non-zero
//         (lines 0x2B2/0x2B3), compute the aspect f32 via the *unsigned*
//         int->f32 magic (2^52 pool double at 0x8029E1D8, no `xoris`, so both
//         operands are unsigned: u32 at +0x94 divided by u16 at +0x98);
//       - skip to mgr.offset, read the next header and require 'FRAM';
//         save off/lba, strncpy(name) into mgr.name, mark open, zero the
//         ring-buffer cursors and struct-copy 0x3C bytes from lbl_8039BA08
//         into mgr.blk0C; return 1;
//       - any read failure / tag mismatch -> fn_8001B754(f) and return 0.
//
// Residual — all register allocation / block layout, no semantic difference
// left that I could find:
//   * 3 words short overall. The original's loop preheader derives r24 from
//     r31 plus 0xc, copies r30 to r23, loads a 0x803A page high half into r19,
//     derives r25 from r30 plus 0x88, and loads another page high half into
//     r20 — i.e. it keeps a *second* copy of the manager pointer (r23)
//     and two more `lis 0x803A` base registers than this body does, which then
//     forces it to re-materialise `&lbl_8039BA58` after the loop
//     (`lis r9; addi r9, r9, -0x45a8` before `lhz 0x88(r9)` and before
//     `addi r31, r9, r9, -0x45a8`) and `lbl_8039BAF8` before the memcpy
//     (`lis r9; addi r3, r9, -0x4508`).  Those 7 extra `lis/addi` pairs minus
//     the 4 this body spends elsewhere is the whole length delta.
//   * Two two-register swaps remain: WANT hi(lbl_8039BAE0)->r19 /
//     hi(lbl_8039BA58)->r20, this body has them the other way round; WANT
//     mgr.vid->r25 / hi(lbl_8039B9E0)->r26, this body has r26/r25.  Pinning
//     vi to r25 or m to r30 to break either swap makes the rest worse
//     (73.4% / 68.0% on the aligned comparison).
//   * WANT's shared fail block sits between the 'FRAM' test and the success
//     tail (`bl 0x8001b754; li r3,0; b epilogue`); this body's `goto fail`
//     block is sunk to the end, so the success tail ends in `b` instead and
//     the epilogue shares a block with the fail path.
//   * Two store groups come out in a different order: the ring-buffer zero
//     stores (WANT: ...0x2d0 then 0x2dc last; got hoists 0x2dc first) and
//     the off/lba save (WANT 0x2e4,0x2e8,0x2d8,0x2d4; got 0x2d8,0x2d4,0x2e4,
//     0x2e8) even though the source order matches WANT.
//   * The one `li r3, 0` WANT materialises on the `fn_8001B658() == 0` path is
//     missing here (this body tracks `ret` in r29 instead).
// Ruled out: literal vs symbol addresses (the HA/LO mask is 0xFFFF0000, so
// only rD/rA matter, not the displacement); a `Chunk *c` pointer variable
// instead of the global object (the global is what creates the second address
// value and raises register pressure — worth +8 points); -O2/-G0 flags
// (already the project defaults); the `(f64)` spelling of the aspect division
// (WANT has no `xoris`, so unsigned `(f32)` casts are the correct reading);
// the `W4` union at chunk+0x1C / mgr.vid+0x10 (WANT needs lhz+stb+sth there
// AND lwz/stw, so a single-width field cannot produce those instructions).
//
// The `register ... __asm__("rN")` pins are load-bearing (they are how retail
// gets r21/r22 for the two incoming args, r24 for the vid-header pointer and
// r28/r29 for the two loop counters): without them this body scores 66.1%
// instead of 76.8% on the aligned comparison.  Assigning `vh = &hdr.vid`
// BEFORE the `while` (so it is loop-invariant) is what lifts the frame from
// 0x40/stmw r20 to 0x50/stmw r19, i.e. to retail's 13 callee-saved registers;
// assigning it inside the branch costs 4 points.
#include "types.h"
#include "qb_constants.h"

extern char lbl_8029DEB4[];
extern char lbl_8029E0C8[];
extern char lbl_8029E0F0[];
extern char lbl_8029E13C[];
extern char lbl_8029E164[];
extern char lbl_8029E1A8[];
extern char lbl_8039B9E0[];
extern char lbl_8039BA08[];
extern char lbl_8039BAF8[];
extern bool lbl_8039BAE0;
extern bool lbl_8039BE0C;

int OSPanic();
void memcpy();
s32 strncpy(void *, void *, s32);
s32 fn_8001B658(s32, s32);
s32 fn_8001B6DC(s32, s32, s32);
s32 fn_8001B718(s32, s32, s32);
s32 fn_8001B754(s32);

/* Chunk header +0x1C: WANT writes it once as a halfword (sth 0x1c), once as
   a byte (stb 0x1e) and reads it once as a word (lwz 0x1c), so the game type
   has to expose all three widths at that offset. */
typedef union {
    u32 w;
    u16 h[2];
    u8 b[4];
} W4;

typedef struct {
    s32 version;
    s32 f10;
    s32 f14;
    s32 f18;
    W4 f1C;
} VidHdr;

typedef struct {
    u16 width;
    u16 height;
    u32 f4;
    u32 f8;
    u32 fC;
    W4 f10;
    f32 f14;
} VidInfo;

typedef struct {
    s32 type;
    u32 len;
    s32 unk8;
    VidHdr vid;
} Chunk;

typedef struct {
    s32 w[8];
} Blk32;

typedef struct {
    s32 w[15];
} Blk60;

typedef struct {
    void *alloc;
    char pad0x4[0x8];
    Blk60 blk0C;
    char name[0x3F];
    u8 flag87;
    VidInfo vid;
    s32 state;
    char pad0xA4[0x218];
    s32 audio;
    s32 open;
    s32 err;
    s32 flag2C8;
    s32 lastarg;
    s32 reading;
    s32 offset;
    s32 lba;
    s32 ptr;
    s32 unk2E0;
    s32 save_off;
    s32 save_lba;
    u32 cur;
    u32 unk2F0;
    char pad0x2F4[0xA0];
    s32 unk394;
} Mgr;

extern Mgr lbl_8039BA58;
extern Chunk lbl_8039BE00;

s32 fn_80121D80(s32 arg0, s32 arg1) {
    s32 ret;
    register u32 rem __asm__("r29");
    register u32 n __asm__("r28");
    u32 t;
    Mgr *m;
    register VidHdr *vh __asm__("r24");
    VidInfo *vi;
    s32 ab;
    register s32 a0 __asm__("r21") = arg0;
    register s32 a1 __asm__("r22") = arg1;

    ret = 0;
    m = &lbl_8039BA58;
    if (m->open != 0) {
        return 0;
    }
    if (fn_8001B658((s32)lbl_8039B9E0, a0) != 0) {
            if (fn_8001B6DC((s32)lbl_8039B9E0, (s32)&lbl_8039BE00, 0x20) >= 0) {
                if ((lbl_8039BE00.type == QB_FOURCC_VID1) && ((lbl_8039BE00.vid.version & 0xFFFF0000) == 0x01000000)) {
                    if (fn_8001B6DC((s32)lbl_8039B9E0, (s32)&lbl_8039BE00, 0x20) >= 0) {
                        if (lbl_8039BE00.type == QB_FOURCC_HEAD) {
                            m->offset = lbl_8039BE00.len + 0x20;
                            fn_8001B718((s32)lbl_8039B9E0, 0, 0x2C);
                            m->state = QB_STREAM_STATE_NONE;
                            vh = &lbl_8039BE00.vid;
                        rem = lbl_8039BE00.len - 0xC;
                            while (rem > 0x1F) {
                                if (fn_8001B6DC((s32)lbl_8039B9E0, (s32)&lbl_8039BE00, 0x20) < 0) {
                                    goto fail;
                                }
                                rem -= 0x20;
                                if (lbl_8039BE00.type == QB_FOURCC_VIDH) {
                                        if (lbl_8039BE00.unk8 == 0) {
                                        lbl_8039BE00.vid.f1C.h[0] = lbl_8039BE00.vid.f1C.h[1];
                                        lbl_8039BE00.vid.f1C.b[2] = 0;
                                    }
                                    if (lbl_8039BE00.len > 0x20) {
                                        OSPanic(lbl_8029DEB4, 0x287, lbl_8029E0C8);
                                    }
                                    if (lbl_8039BE00.len > 0x20) {
                                        OSPanic(lbl_8029DEB4, 0x288, lbl_8029E0F0);
                                    }
                                    lbl_8039BAE0 = lbl_8039BE0C;
                                    vi = &m->vid;
                                    vi->f4 = vh->f10;
                                    vi->f8 = vh->f14;
                                    vi->fC = vh->f18;
                                    vi->f10.w = vh->f1C.w;
                                } else if ((lbl_8039BE00.type == QB_FOURCC_AUDH) && (a1 == 0)) {
                                    ab = ((s32 (*)(s32))lbl_8039BA58.alloc)(lbl_8039BE00.len);
                                    m->audio = ab;
                                    n = lbl_8039BE00.len - 0xC;
                                    *(Blk32 *)ab = *(Blk32 *)&lbl_8039BE00;
                                    lbl_8039BE00.len = lbl_8039BE00.len - 0x20;
                                    if (lbl_8039BE00.len > 0x1F) {
                                        if ((lbl_8039BE00.len & 0x1F) != 0) {
                                            OSPanic(lbl_8029DEB4, 0x299, lbl_8029E13C);
                                        }
                                        if (fn_8001B6DC((s32)lbl_8039B9E0, m->audio + 0x20, lbl_8039BE00.len) >= 0) {
                                            rem -= lbl_8039BE00.len;
                                        }
                                    }
                                    memcpy(lbl_8039BAF8, (void *)(m->audio + 0xC),
                                           n > 0x21A ? 0x21A : n);
                                } else {
                                    t = rem + 0x20;
                                    rem = t - lbl_8039BE00.len;
                                }
                            }
                            if (m->vid.width == 0 || m->vid.height == 0) {
                                OSPanic(lbl_8029DEB4, 0x2B2, lbl_8029E164);
                            }
                            if (m->vid.f8 == 0) {
                                OSPanic(lbl_8029DEB4, 0x2B3, lbl_8029E1A8);
                            }
                            m->vid.f14 = (f32)m->vid.fC / (f32)m->vid.f10.h[0];
                            fn_8001B718((s32)lbl_8039B9E0, 0, m->offset);
                            if (fn_8001B6DC((s32)lbl_8039B9E0, (s32)&lbl_8039BE00, 0x20) < 0) {
                                goto fail;
                            }
                            if (lbl_8039BE00.type != QB_FOURCC_FRAM) {
                                goto fail;
                            }
                            m->save_off = m->offset + 0x20;
                            m->save_lba = lbl_8039BE00.len;
                            m->lba = lbl_8039BE00.len;
                            m->offset = m->offset + 0x20;
                            strncpy(m->name, (void *)a0, 0x40);
                            m->flag87 = 0;
                            m->open = 1;
                            m->unk394 = 0;
                            m->cur = 0;
                            m->unk2F0 = 0;
                            m->unk2E0 = 0;
                            m->err = 0;
                            m->flag2C8 = 0;
                            m->lastarg = 0;
                            m->reading = 0;
                            m->ptr = 0;
                            m->blk0C = *(Blk60 *)lbl_8039BA08;
                            ret = 1;
                        }
                    }
                }
            }
    }
    return ret;
fail:
    fn_8001B754((s32)lbl_8039B9E0);
    return 0;
}