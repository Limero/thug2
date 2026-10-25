// family=m2c range=0x80082F38-0x8008345C size=1316B
// FLAG: -fno-branch-count-reg
//   Targets W:0x80083274 `cmpwi r11,3` / W:0x8008334C `cmpwi r11,3` and the
//   two other edge-loop latches.  All three edge loops in the want are
//   `li r11,0 … addi r11,r11,1 / cmpwi r11,3 / ble`, i.e. an explicit
//   immediate compare, while the got body converts each of them to a
//   count-register loop (`li r0,4 / mtctr r0 / … / bdnz`) — 3 extra
//   instructions per loop and the main reason the object is 29 words short.
//   The corner pointer walk (`cmpw r31,r30 / ble`) is unaffected by the flag.
//   NOTE: if this compile FAILs, this one line is the cause.
// REBUILD : from-scratch transcription of the want
// instruction stream in build/b34pkt/fn_80082F38.psdiff.txt / .diff.txt.
// INERT: not registered in splits.txt/configure.py — never compiled.
//
// — first COMPILED this body (13.68%, got 1204B vs
// want 1316B) and fixed the two things the measured diff
// (build/b34pkt/fn_80082F38.rb.diff.txt) proved wrong:
//
//  1. FRAME WAS 0x30 SHORT (got `stwu -0xc0`, want `stwu -0xf0`, so every
//     callee-saved offset was 0x30 low too).  Retail's layout is
//     locals r1+8..r1+0x77, a 0x30 DEAD HOLE at r1+0x78..r1+0xa7 that the
//     code never touches, then stmw r26,0xa8 / stfd f26..f31 at
//     0xc0..0xe8 / lr 0xf4.  GCC 2.95 gives every AGGREGATE local a stack
//     slot at expansion time (`assign_stack_local` in expand_decl) and only
//     scalars become pseudos, so 0x30 of declared-but-eliminated aggregate
//     locals is exactly what produces the hole.  Three Vec4s = 0x30, and
//     declaring them AFTER tri[] makes GCC place them at r1+0x78 (slot
//     assignment is ascending in declaration order: box 0x8, tri 0x48,
//     spare 0x78 — verified against the 0xc0 body).  `spare` is therefore
//     deliberately UNUSED: it is frame ballast, not algorithm.
//
//  2. CORNER LOOP IS A POINTER WALK, not an index loop.  Retail is
//     `addi r31,r31,0x10 / cmpw r31,r30 / ble` with r30 = r1+0x38 = &box[3]
//     (set up once at 0x8008301C and never rewritten), i.e. the loop
//     variable is a Vec4* compared against a COMPUTED end address.  The
//     index form `for (i=0;i<=3;i++) &box[i]` instead left `cmpwi r31,3`
//     (immediate) as the test plus a separate strength-reduced pointer.
//     The three EDGE loops are left as index loops on purpose: retail keeps
//     BOTH a counter (r11, `addi r11,r11,1 / cmpwi r11,3 / ble`) and a
//     strength-reduced walking pointer (r10, `addi r10,r10,0x10`) there,
//     which is what `box[i]` + `box[(i+1)%4]` produces.
//
// Recovered shape — every item below is read off the want disassembly:
//
//  * Signature: six FLOAT args in f1..f6 (f30<-f1, f31<-f2, f28<-f3,
//    f29<-f4, f27<-f5, f26<-f6), i.e. (x0,y0) (x1,y1) (x2,y2).  No GPR
//    argument is ever read, so the extra s32 args in the old draft are gone.
//  * Constants: lbl_80296548 = -1.0f, lbl_8029654C = 1.0f,
//    lbl_80296550 = 0.0f (src/r2d_80296540.c).  Each guard block loads its
//    constant once (CSE) and each of the three init values is loaded once.
//  * Locals: seven 16-byte points.  r1+8..r1+0x47 is walked by the corner
//    loop (4 corners), r1+0x48/0x58/0x68 are handed to fn_80082EB8.  Frame
//    is 0xf0: stmw r26,0xa8 / stfd f26..f31 at 0xc0..0xe8 / lr at 0xf4.
//    The want never touches r1+0x78..r1+0xa7, so that 48 bytes are dead
//    frame space (GCC outgoing-argument area or three unused slots) — the
//    one part of the frame this transcription cannot pin down.
//  * Guard: four cheap rejects, 3 comparisons each — all three x below -1,
//    all three x above 1, all three y below -1, all three y above 1.
//    Failures use bge (unordered counts as >=) and the last conjunct of
//    each group is inverted into the shared `return 0` tail, which is the
//    plain `if (a && b && c) return 0;` codegen.
//  * Corner loop: for i <= 3, fn_80082EB8(&box[i], &tri[0], &tri[1],
//    &tri[2]) != 0 -> return 1.  fn_80082EB8 is the MATCHED point-in-
//    triangle helper (src/fn_80082EB8.c); arg0 is the query point.
//  * Three "vertex inside box" early accepts: x >= -1 && x <= 1 &&
//    y >= -1 && y <= 1 for (x0,y0), then (x1,y1), then (x2,y2).  These are
//    the cror cr0un,cr0eq,cr0gt/cr0lt + bns/bso chains: the negations must
//    be true for NaN, i.e. exactly `&&` on ordered >= / <=.
//  * Three edge loops, one per triangle edge, each against the four box
//    edges: (sdx,sdy,point) = (x1-x0,y1-y0,(x0,y0)), (x2-x0,y2-y0,(x0,y0)),
//    (x2-x1,y2-y1,(x1,y1)).  Body:
//        dx = B.x-A.x; dy = B.y-A.y; den = dy*sdx - dx*sdy;
//        if (den != 0) { t = (dx*(py-A.y) - dy*(px-A.x))/den;
//                        u = (sdx*(py-A.y) - sdy*(px-A.x))/den;
//                        if (t <= 1 && u <= 1) return 1; }
//    The op order is exact: the subtracted product is expanded first
//    (fmuls) and the leading product folds into fmsubs, which is what
//    `A*B - C*D` produces; px-A.x is evaluated before py-A.y.
//  * The index is a SIGNED int and the wrap is `(i + 1) % 4` — the want
//    emits the signed power-of-two modulo sequence (cmpwi/bge/addui, then
//    rlwinm to clear the low two bits), not a plain `& 3`.
#include "types.h"

extern f32 lbl_80296548;
extern f32 lbl_8029654C;
extern f32 lbl_80296550;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

s32 fn_80082EB8(const Vec4 *, const Vec4 *, const Vec4 *, const Vec4 *);

s32 fn_80082F38(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2) {
    Vec4 box[4];
    Vec4 tri[3];
    char spare_hole[44]; /* frame ballast: retail's dead r1+0x78..r1+0xa7 */
    f32 sdx;
    f32 sdy;
    s32 i;
    Vec4 *p;
    Vec4 *t0;           /* &tri[0..2] hoisted: targets W:0x800830B8 mr r5,r26 */
    Vec4 *t1;           /*                            W:0x800830C0 mr r6,r27 */
    Vec4 *t2;           /*                            W:0x80082F58 stmw r26,0xa8 */

    if (x0 < lbl_80296548 && x1 < lbl_80296548 && x2 < lbl_80296548) {
        return 0;
    }
    if (x0 > lbl_8029654C && x1 > lbl_8029654C && x2 > lbl_8029654C) {
        return 0;
    }
    if (y0 < lbl_80296548 && y1 < lbl_80296548 && y2 < lbl_80296548) {
        return 0;
    }
    if (y0 > lbl_8029654C && y1 > lbl_8029654C && y2 > lbl_8029654C) {
        return 0;
    }

    box[0].x = lbl_80296548; box[0].y = lbl_80296548;
    box[0].z = lbl_80296550; box[0].w = lbl_80296550;
    box[1].x = lbl_8029654C; box[1].y = lbl_80296548;
    box[1].z = lbl_80296550; box[1].w = lbl_80296550;
    box[2].x = lbl_8029654C; box[2].y = lbl_8029654C;
    box[2].z = lbl_80296550; box[2].w = lbl_80296550;
    box[3].x = lbl_80296548; box[3].y = lbl_8029654C;
    box[3].z = lbl_80296550; box[3].w = lbl_80296550;

    tri[0].x = x0; tri[0].y = y0;
    tri[0].z = lbl_80296550; tri[0].w = lbl_8029654C;
    tri[1].x = x1; tri[1].y = y1;
    tri[1].z = lbl_80296550; tri[1].w = lbl_8029654C;
    tri[2].x = x2; tri[2].y = y2;
    tri[2].z = lbl_80296550; tri[2].w = lbl_8029654C;

    t0 = &tri[0];
    t1 = &tri[1];
    t2 = &tri[2];
    /* The three tri pointers are LOOP-INVARIANT but must stay live across the
       fn_80082EB8 call, which is what makes them callee-saved in retail
       (r29/r26/r27) instead of being re-materialised as `addi r4,r1,0x48`
       every iteration the way the got body does. */
    for (p = box; p <= &box[3]; p++) {
        if (fn_80082EB8(p, t0, t1, t2) != 0) {
            return 1;
        }
    }

    if (x0 >= lbl_80296548 && x0 <= lbl_8029654C &&
        y0 >= lbl_80296548 && y0 <= lbl_8029654C) {
        return 1;
    }
    if (x1 >= lbl_80296548 && x1 <= lbl_8029654C &&
        y1 >= lbl_80296548 && y1 <= lbl_8029654C) {
        return 1;
    }
    if (x2 >= lbl_80296548 && x2 <= lbl_8029654C &&
        y2 >= lbl_80296548 && y2 <= lbl_8029654C) {
        return 1;
    }

    /* triangle edge (x0,y0) -> (x1,y1) */
    sdx = x1 - x0;
    sdy = y1 - y0;
    for (i = 0; i <= 3; i++) {
        f32 ax = box[i].x;
        f32 ay = box[i].y;
        f32 bx = box[(i + 1) % 4].x;
        f32 by = box[(i + 1) % 4].y;
        f32 dx = bx - ax;
        f32 dy = by - ay;
        f32 den = dy * sdx - dx * sdy;

        if (den != lbl_80296550) {
            f32 t = (dx * (y0 - ay) - dy * (x0 - ax)) / den;
            f32 u = (sdx * (y0 - ay) - sdy * (x0 - ax)) / den;

            if (t <= lbl_8029654C && u <= lbl_8029654C) {
                return 1;
            }
        }
    }

    /* triangle edge (x0,y0) -> (x2,y2) */
    sdx = x2 - x0;
    sdy = y2 - y0;
    for (i = 0; i <= 3; i++) {
        f32 ax = box[i].x;
        f32 ay = box[i].y;
        f32 bx = box[(i + 1) % 4].x;
        f32 by = box[(i + 1) % 4].y;
        f32 dx = bx - ax;
        f32 dy = by - ay;
        f32 den = dy * sdx - dx * sdy;

        if (den != lbl_80296550) {
            f32 t = (dx * (y0 - ay) - dy * (x0 - ax)) / den;
            f32 u = (sdx * (y0 - ay) - sdy * (x0 - ax)) / den;

            if (t <= lbl_8029654C && u <= lbl_8029654C) {
                return 1;
            }
        }
    }

    /* triangle edge (x1,y1) -> (x2,y2) */
    sdx = x2 - x1;
    sdy = y2 - y1;
    for (i = 0; i <= 3; i++) {
        f32 ax = box[i].x;
        f32 ay = box[i].y;
        f32 bx = box[(i + 1) % 4].x;
        f32 by = box[(i + 1) % 4].y;
        f32 dx = bx - ax;
        f32 dy = by - ay;
        f32 den = dy * sdx - dx * sdy;

        if (den != lbl_80296550) {
            f32 t = (dx * (y1 - ay) - dy * (x1 - ax)) / den;
            f32 u = (sdx * (y1 - ay) - sdy * (x1 - ax)) / den;

            if (t <= lbl_8029654C && u <= lbl_8029654C) {
                return 1;
            }
        }
    }

    return 0;
}

// ---------------------------------------------------------------------------
// SUPERSEDED BODY (m2c husk) — earlier findings preserved verbatim below.
// The body above replaced it (worker rebuild + measured-diff repair loop,
// 2); keep these notes, they are still the local lore.
// ---------------------------------------------------------------------------
// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py
// PARKED 2026-10-07: a earlier full rewrite (want decoded: 6 float args,
//   triangle-vs-box [-1,1]^2 predicate) measured 1.52% vs this body's 2.13%, so it
//   was reverted.  Blocker: the m2c husk's `0;` statements and s32-typed f32 slots
//   hide the real ten-slot 16-byte array (want frame 0xf0 vs got 0x58).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
