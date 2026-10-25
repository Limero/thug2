// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CD0E0-0x800CD150 (112B). Byte-identical.
// extra_cflags: -mps-float -fno-schedule-insns
#include "types.h"
#include "structs.h"
void fn_800B2748(void *, s32, s32);
s32 fn_80024660(void *);
bool fn_800CD0E0(Unk_FFAD6788 *arg0, void *arg1, Unk_EA529D06 *arg2) {
    struct out {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
    } sp8;

    if ((arg1 != 0) && (arg0->unk0xC4 != 0)) {
        fn_800B2748(&sp8, arg0->unk0xC4, fn_80024660(arg1));
        arg2->unk0x8 = ((Unk_2D7DC1B6 *)&sp8)->unk0x8;
        arg2->unk0x0 = ((Unk_2D7DC1B6 *)&sp8)->unk0x0;
        return true;
    }
    return false;
}
