// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016AD8-0x80016B50 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void C_MTX_LookAt(s32 arg0, s32 arg1, s32 arg2, void *arg3);
void fn_8001D424(void *arg0);
typedef struct V3 {
    f32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    char pad0xC[0x1C];
} V3;
void fn_80016AD8(s32 arg0, f32 farg0, f32 farg1, f32 farg2) {
    V3 sp8;
    f32 *p;

    fn_8001D424(&sp8);
    p = (f32 *)&sp8;
    p[0] = farg0;
    p[1] = farg1;
    p[2] = farg2;
    C_MTX_LookAt(arg0, arg0 + 0x3C, arg0 + 0x30, &sp8);
}
