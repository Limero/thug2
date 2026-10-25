// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005C3A0-0x8005C3E0 (64B). Byte-identical.
#include "types.h"
void fn_8005C3A0(void *o, s32 x1, s32 x2, s32 x3, s32 x4, u32 *arg) {
    register u32 tmp asm("r0");
    u32 local;
    void **t;
    tmp = *arg;
    t = *(void ***)((char *)o + 8);
    local = tmp;
    ((void (*)(void *, s32, s32, s32, s32, u32 *))*(void **)((char *)t + 0xbc))((char *)o + (s16)*(s16 *)((char *)t + 0xb8), x1, x2, x3, x4, &local);
}
