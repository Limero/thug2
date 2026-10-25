// WIP DRAFT (non-matching) — hand-rebuilt from want (m2c body did not compile)
// family=m2c range=0x800264FC-0x80026668 size=364B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED: NEAR 97.8% -- 89 of 91 words byte-identical, object .text = 364B =
// symbols.txt size = the range marker.  No inline asm.  Converts a Q14 vector
// (4x s16) to a unit vector + length in a 5-float out record.
//
// RESIDUAL: 2 words, ONE cause, in the second packed-word update.  want
// materialises the shifted Q14 value first (a left shift by 17 into r0) and
// then inserts it into the packed word with the compensating rotate 31 and
// mask 1..15; this build pre-folds the value into a single rotate-16-with-
// mask-1..15 and inserts it with rotate 0.  Both forms compute the same bits
// (the field ends up holding the low 15 bits of the Q14 value); only the
// instruction shape differs.
//
// WHY IT IS STUCK: gcc-2.95's combine always normalises a masked shifted
// value into one rlwinm before the mask-insert, which forces the insert's
// rotate to 0.  The two halves are mutually exclusive through C: with the
// value's mask `(t & 0x7FFF0000)` the shift folds (rotate 17 / mask 1..14 or
// rotate 16 / mask 1..15, both with rotate-0 insert); dropping the mask
// reproduces the shift exactly but loses mask_insert and costs an extra
// word.  Bitfield routes give the right field bounds but the wrong rotate
// (16 for a 15-bit field) plus a clrlwi, and collapse the two packed-word
// stores into one.  The insert's rotate needs a two-use middle value that the
// original RTL does not have.  Do not re-grind value spellings: every
// `<<16`/`<<17`/`<<17 >>1`/`*131072u >> 1`/s16-temp/operand-swapped variant
// folds identically.
//
// AUDIT: all 5 REL14 and 3 REL24 relocations match want, all 6 ADDR16 pairs
// decode to real symbols.txt entries.  The object carries an 8-byte private
// .rodata (0x4330000080000000) synthesised by the three (f32)(f64)(s32)
// conversions; want's pool copy is lbl_802915D8 with the same bits, so
// tools/fix_fp_pool.py retargets it at promote time.  Nothing else is left.
//
// The body below is the measured best state.  Facts that keep it there:
//  - sqrtf is `f32 sqrtf(f32)` at .text:0x80270CA4 (an s32 return type and a
//    missing operand were the original compile failure).
//  - the out/in records are the file-local OUT264FC / IN264FC typedefs; the
//    promoted callers src/fn_800264A0.c and src/fn_800035FC.c are the oracles.
//  - the zero branch sources its three equal stores z, y, x with `len` last,
//    which is what produces want's store order.
//  - the zero-branch constant uses its own name (temp_f12), not the value
//    branch's temp_f0: sharing one name re-homes the field value and cascades
//    three register renames.
//  - the running sum is two variables: want keeps it in f11 across the first
//    two subtractions and materialises f1 only on the last one.
//  - the packed-word updates must be written on a named local; the memory
//    form never gets mask_insert and costs clrlwi+or instead.
#include "types.h"

extern f32 lbl_802915CC; /* 0.0f  */
extern f32 lbl_802915D0; /* 1.0f  */
extern f32 lbl_802915E0; /* 1/16384 */
f32 sqrtf(f32);

/* out-param: packed word + 4 floats.  in-param: 4 s16 (Q14). */
typedef struct {
    s32 w0;
    f32 x;
    f32 y;
    f32 z;
    f32 len;
} OUT264FC;

typedef struct {
    s16 v;
    s16 a;
    s16 b;
    s16 c;
} IN264FC;

void fn_800264FC(OUT264FC *arg0, IN264FC *arg1) {
    s32 temp_r9;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f8;
    f32 temp_f9;
    f32 temp_f10;

    temp_r9 = arg0->w0;
    temp_r9 = (temp_r9 & ~0x80000000) | (arg1->v & 0x80000000);
    arg0->w0 = temp_r9;
    temp_r9 = (temp_r9 & ~0x7FFF0000) |
              ((((u32)((u16)arg1->v) << 0x11) >> 1U) & 0x7FFF0000);
    arg0->w0 = temp_r9;
    if ((arg1->a == 0) && (arg1->b == 0) && (arg1->c == 0)) {
        temp_f12 = lbl_802915CC;
        arg0->z = temp_f12;
        arg0->y = temp_f12;
        arg0->x = temp_f12;
        arg0->len = lbl_802915D0;
        return;
    }
    temp_f10 = lbl_802915E0;
    temp_f8 = (f32)(f64)(s32)arg1->a * temp_f10;
    temp_f9 = (f32)(f64)(s32)arg1->b * temp_f10;
    temp_f0 = (f32)(f64)(s32)arg1->c * temp_f10;
    temp_f1 = lbl_802915D0 - (temp_f8 * temp_f8);
    temp_f1 = temp_f1 - (temp_f9 * temp_f9);
    temp_f2 = temp_f1 - (temp_f0 * temp_f0);
    if (temp_f2 < lbl_802915CC) {
        temp_f2 = lbl_802915CC;
    }
    arg0->x = temp_f8;
    arg0->y = temp_f9;
    arg0->z = temp_f0;
    if ((u16)arg1->v & 0x8000) {
        arg0->len = -sqrtf(temp_f2);
    } else {
        arg0->len = sqrtf(temp_f2);
    }
}
// 2026-10-21: the mask-pair form `(w & ~0x7FFF0000) | (y & 0x7FFF0000)` is
// required — it is what lets cc1 build a single rlwimi. The equivalent
// `(w & 0x8001FFFF) | (y)` (or with `+`, or with the shifted value in a named
// `u32` local) instead emits `rlwinm r9,r9,0,0xf,0` + `or` (2 words, whole
// body shifts), and the shift pair still folds to rotate-0. The two words stay
// on combine's fold of `(x << 17) >> 1`.
