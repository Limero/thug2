// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B63D8-0x800B6404 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    f32 unk0x0;
    s32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
    s32 unk0x10;
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 rest : 29;
} T800B63D8;

void fn_800B63D8(T800B63D8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                f32 farg0, f32 farg1, f32 farg2)
{
    arg0->unk0x0 = farg0;
    arg0->unk0x4 = arg1;
    arg0->unk0x8 = farg1;
    arg0->unk0xC = farg2;
    arg0->unk0x10 = arg2;
    arg0->b0 = 1;
    arg0->b1 = arg3;
    arg0->b2 = arg4;
}
