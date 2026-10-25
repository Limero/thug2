// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005049C-0x8005060C (368B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_80292E8C; /* 1000.0f     */
extern f64 lbl_80292E90; /* 2147483648.0 */

s32 GetPair(void *, s32, void *, s32);
s32 GetFloat(void *, s32, f32 *, s32);
void *fn_80125000(void *);
void fn_80050428(void *, s32);

/* 16-byte out-param block: fn_80125000 clears it, GetPair fills +4 and +8.
 * Three of these are the 0x10 aggregate slots at r1+0x08/0x18/0x28. */
typedef struct {
    s32 unk0;
    f32 x;
    f32 y;
    f32 z;
} Pair_t;

typedef struct {
    char pad[0x480];
    f32 f480;
    f32 f484;
    f32 f488;
    f32 f48C;
    f32 f490;
    f32 f494;
} Obj_t;

void *CBlurEffect_SetMorph(Obj_t *arg0, void *arg1, s32 *arg2) {
    Pair_t p1;
    Pair_t p2;
    Pair_t p3;
    f32 t;
    f32 temp_f0;
    s32 v;

    fn_80125000(&p1);
    if (GetPair(arg1, QB_BLUR_ALPHA_PAIR, &p1, 0) != 0) {
        arg0->f480 = p1.x;
        arg0->f484 = p1.y;
    }
    fn_80125000(&p2);
    if (GetPair(arg1, QB_BLUR_BOTTOM_SCALES, &p2, 0) != 0) {
        arg0->f488 = p2.x;
        arg0->f48C = p2.y;
    }
    fn_80125000(&p3);
    if (GetPair(arg1, QB_BLUR_MAX_DISPLACEMENT, &p3, 0) != 0) {
        arg0->f490 = p3.x;
        arg0->f494 = p3.y;
    }
    if (GetFloat(arg1, QB_TIME, &t, 0) != 0) {
        temp_f0 = t * lbl_80292E8C;
        if (!(temp_f0 >= lbl_80292E90)) {
            v = (s32)temp_f0;
        } else {
            v = (s32)(temp_f0 - lbl_80292E90) ^ 0x80000000;
        }
    } else {
        v = 0;
    }
    fn_80050428(arg0, v);
    if (arg2 != NULL) {
        *arg2 = v;
    }
    return (void *)((char *)arg0 + 0x480);
}
