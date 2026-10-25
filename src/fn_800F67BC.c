// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F67BC-0x800F682C (112B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800F36C8(void *, s32, s32, s32, s32, s32);
void fn_800F682C(s32, s32, s32);
bool fn_800F67BC(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4, s32 arg5) {
    Unk_0E2E8431 *temp_r9;
    fn_800F36C8(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_800F682C(arg0, arg4, arg5);
    temp_r9 = arg0->unk0x50;
    ((s32 (*)(void *, void *, void *))temp_r9->unk0x74)((char *)arg0 + temp_r9->unk0x70, arg1, arg2);
    return false;
}
