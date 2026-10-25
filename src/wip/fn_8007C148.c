// PARKED 2026-10-21 at 89.9% (10 words, all in the tail read/store pairs).
// Three bytes are read from lbl_80364C38, converted through ProDG's
// unsigned-char -> double 2^52-bias expansion, scaled by lbl_80300490 (1.0f),
// converted back to int, clamped to 0xFF and stored to lbl_8037B5E8+0x150..152;
// each stored byte is then doubled unless bit 7 is already set (then 0xFF).
//
// ADDRESSING: the destination is reached through a pointer local that is
// RE-ASSIGNED from the symbol before every store group / read-store pair. Each
// assignment gives a fresh constant pseudo that dies at its use, so ngccc
// rematerialises `lis`+`addi` per block (as WANT does) while keeping the offset
// in the store displacement. A single initialiser CSEs the base into one
// register for the whole function (too short, all later words shift); writing
// `lbl_8037B5E8[0x150]` directly folds the symbol's low half into the store
// displacement (also one word short per group).
//
// RESIDUAL: in the last three pairs WANT puts the base in r11 (lis into r9,
// addi into r11) and the mask temp in r9; this body swaps the two. Everything
// else, including the whole float path and all three clamp groups, is exact.
// Declaration order, a second pointer for the tail, mask/value locals, `*2`
// vs `<<1` and inverted conditions all reproduce the same 89.9%.
// The dead `mr rX,r11` prologue moves are the same unsigned-char expansion
// noise ngccc emits for this body; the 2^52 pool constant is ngccc's own.
#include "types.h"

extern u8 lbl_80364C38[]; // .bss: three consecutive u8s
extern u8 lbl_8037B5E8[]; // .bss: destination object, bytes at +0x150..+0x152
extern f32 lbl_80300490;  // .data == 1.0f

s32 fn_8007C148(void) {
    u8 *p = lbl_80364C38;
    u8 *q;
    f32 s = lbl_80300490;
    s32 a, b, c;
    u8 t;

    a = (s32)((f32)((f64)p[0]) * s);
    b = (s32)((f32)((f64)p[1]) * s);
    c = (s32)((f32)((f64)p[2]) * s);

    q = lbl_8037B5E8;
    if (a <= 0xFF) q[0x150] = a; else q[0x150] = 0xFF;
    q = lbl_8037B5E8;
    if (b <= 0xFF) q[0x151] = b; else q[0x151] = 0xFF;
    q = lbl_8037B5E8;
    if (c <= 0xFF) q[0x152] = c; else q[0x152] = 0xFF;

    q = lbl_8037B5E8;
    t = q[0x150];
    q[0x150] = (t & 0x80) ? 0xFF : t << 1;
    q = lbl_8037B5E8;
    t = q[0x151];
    q[0x151] = (t & 0x80) ? 0xFF : t << 1;
    q = lbl_8037B5E8;
    t = q[0x152];
    q[0x152] = (t & 0x80) ? 0xFF : t << 1;
    return 1;
}
