// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80036370-0x800363BC (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float -fno-schedule-insns
#include "types.h"

extern f32 lbl_80291ED4;

/* 0x20-stride record: 3 s32 head, unused hole at 0xC, 4-float tail. */
typedef struct {
    s32 a, b, c;
    f32 x, y, z, w;
} Rec;

/* 16-byte splat temp built on the stack, then copied as two PS pairs. */
typedef struct {
    f32 x, y, z, w;
} Splat;

void fn_80036370(Rec *arg0) {
    Splat sp8;
    s32 zero = 0;
    f32 w = lbl_80291ED4;
    register s32 o __asm__("r9");
    register s32 sp __asm__("r10");
    o = (s32)arg0;
    sp = (s32)&sp8;
    *(f32 *)(sp + 0) = w;
    *(f32 *)(sp + 12) = w;
    *(f32 *)(sp + 8) = w;
    *(f32 *)(sp + 4) = w;
    *(s32 *)((char *)o + 8) = zero;
    *(__ps_t *)((char *)o + 24) = *(__ps_t *)(sp + 8);
    *(s32 *)((char *)o + 0) = zero;
    *(__ps_t *)((char *)o + 16) = *(__ps_t *)(sp + 0);
    *(s32 *)((char *)o + 4) = zero;
}
