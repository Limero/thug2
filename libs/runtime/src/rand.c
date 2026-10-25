// rand — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// Newlib rand(): LCG step over _reent._rand_next @ +0x58 via _impure_ptr
// (lbl_803CA420, r13-relative), mult 1103515245 (0x41C64E6D) + 12345,
// returning the low 31 bits. Matches crashwoc's src/runtime/libc/rand.c
// semantics verbatim. (Companion srand() is dead-stripped: 0 callers.)
// range 0x8026AA08-0x8026AA2C (36B). Byte-identical.
#include "types.h"
#include "qb_constants.h"

typedef struct { char _pad[0x58]; s32 state; } rng_t;
extern s32 lbl_803CA420;

s32 rand(void) {
    rng_t *p;
    s32 mul;
    s32 v;
    p = lbl_803CA420;
    __asm__ volatile("");
    mul = QB_RNG_LCG_MULT;
    __asm__ volatile("" : "+r"(mul));
    v = p->state * mul + 0x3039;
    p->state = v;
    return v & QB_UNKNOWN_0x7FFFFFFF;
}
