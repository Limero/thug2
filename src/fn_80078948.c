// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80078948-0x8007899C (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
} Out78948;

void fn_80078948(Out78948 *arg0, u32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 cond = (arg2 < arg4 - 1);

    arg1 = (u32 *)((char *)arg1 + (arg3 * arg4 + arg2) * 4);
    arg0->unk0x0 = (s32)arg1[0];
    arg0->unk0x4 = (s32)arg1[cond];
    if (arg3 < arg5 - 1) {
        arg1 += arg4;
    }
    arg0->unk0x8 = (s32)arg1[0];
    arg0->unk0xC = (s32)arg1[cond];
}
