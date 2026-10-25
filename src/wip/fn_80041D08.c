// WIP DRAFT (non-matching) — hand reconstruction from the original function.
// family=hand range=0x80041D08-0x80041E54 size=332B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-23: 86.75% NEAR, 332B (length-exact), 11 differing words.
// The body is fully decoded and every instruction matches except the stack
// addresses of two locals and one hoist slot.
//
// WHAT IT IS: CScreenElement_resolve_just — reads one query element with
// GetArray(ctx, id, &arr, 0) and writes two floats through the caller's out
// pointers. `self` (r3) is unused, exactly like the promoted sibling
// CScreenElement_resolve_rgba (src/fn_80041E54.c).
//
// The element's kind tag is a byte at arr+2:
//   2  -> the two outputs are fn_80129420(arr, 0) and fn_80129420(arr, 1).
//   13 -> the two outputs are the first two entries of an f32[2] scratch
//         array filled by a two-iteration loop that hashes the element
//         (GetChecksum(arr, i)) and maps QB_LEFT/QB_TOP to the first
//         constant, QB_RIGHT/QB_BOTTOM to the second, anything else to the
//         third. The three constants are hoisted into f29-f31 before the
//         loop (which is why the original saves them), and the loop walks
//         the scratch array through a running cursor.
//   other -> nothing is written, the function still returns true.
// GetArray failure returns false.
//
// SHAPE NOTES (all measured):
//  * `if (GetArray(...) != 0) { switch ... return true; } return false;` is
//    required: the `return false; if (ok) {...}` spelling makes ngccc hoist
//    `li r3,0` above the test and moves the epilogue labels.
//  * `for (i = 0, p = v; i <= 1; i++, p++)` — not `p = v; for (...)` — is what
//    puts out0/out1 in r24/r23 and the cursor in r31; the split form assigns
//    r25/r24 and loses the ninth callee-saved register.
//  * The three rodata floats are plain symbol loads (`c0 = lbl_8029238C;`).
//    The expected object carries @ha/@l relocations on them; spelling them as
//    literal addresses drops the score.
//  * RESIDUAL — the frame: retail is 0x70 with arr at 8 and v at 0x10, leaving
//    0x18..0x34 for locals the code never touches. ngccc allocates by object
//    size (larger first), so any padding object takes the bottom of the frame
//    and pushes arr/v up: `volatile s32 pad[6]` puts them at 0x20/0x28 (all
//    other frame words then match, which is the version kept here), while
//    `f32 v[9]` and a 44-byte struct alias both take 8 and drop r23 from the
//    save set. Reproducing arr/v at 8/0x10 together with the 0x34 save offset
//    needs the original's real (dead) locals, not padding.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_8029238C;
extern f32 lbl_80292390;
extern f32 lbl_80292394;

s32 GetArray(CStruct *, s32, CStruct **, s32);
s32 GetChecksum(CStruct *, s32);
f32 fn_80129420(CStruct *, s32);

bool CScreenElement_resolve_just(s32 self, CStruct *ctx, s32 id, f32 *out0,
                                 f32 *out1) {
    CStruct *arr;
    f32 v[2];
    f32 *p;
    s32 i;
    f32 c0;
    f32 c1;
    f32 c2;
    s32 cs;
    volatile s32 frame_pad[6];

    (void)self;
    if (GetArray(ctx, id, &arr, 0) != 0) {
        switch (*(u8 *)((char *)arr + 2)) {
        case 2:
            *out0 = fn_80129420(arr, 0);
            *out1 = fn_80129420(arr, 1);
            break;

        case 13:
            c0 = lbl_8029238C;
            c1 = lbl_80292390;
            c2 = lbl_80292394;
            for (i = 0, p = v; i <= 1; i++, p++) {
                cs = GetChecksum(arr, i);
                if (cs == QB_LEFT || cs == QB_TOP) {
                    *p = c0;
                } else if (cs == QB_RIGHT || cs == QB_BOTTOM) {
                    *p = c1;
                } else {
                    *p = c2;
                }
            }
            *out0 = v[0];
            *out1 = v[1];
            break;
        }
        return true;
    }
    return false;
}
