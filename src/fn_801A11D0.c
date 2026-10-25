// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A11D0-0x801A1220 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void fn_8002DEAC(void *, s32, s32, f32, f32, f32, f32);
typedef struct { char pad0x0[0x3C]; s32 unk0x3C; } S_t;
void fn_801A11D0(void *arg0, f32 farg0) {
    register s32 a0 __asm__("r9");
    a0 = (s32)arg0;
    ((S_t *)a0)->unk0x3C = 0;
    fn_8002DEAC((char *)a0 + (s32)0x40, 0, 0, 0.0f, farg0, 0.0f, 1.0f);
}
