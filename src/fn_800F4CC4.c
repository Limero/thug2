// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F4CC4-0x800F4D50 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8001075C(s32);
void fn_80010760(void);
s32 fn_800F36C8(s32, s32, s32, s32, s32, s32);
extern char lbl_8029B9A4[];
bool fn_800F4CC4(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Unk_0E2E8431 *temp_r9;

    fn_8001075C(lbl_8029B9A4);
    fn_800F36C8(arg0, arg1, arg2, arg3, arg4, arg5);
    temp_r9 = arg0->unk0x50;
    ((s32 (*)(void *, void *, void *))temp_r9->unk0x74)((char *)arg0 + temp_r9->unk0x70, arg1, arg2);
    fn_80010760();
    return false;
}
