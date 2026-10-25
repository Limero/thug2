// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F5E3C-0x800F5EE8 (172B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_802FFE98;
extern void fn_80010D94(s32, s32);
extern s32 fn_800F36C8(s32, s32, s32, s32, s32, s32);
extern void fn_800F5F8C(Unk_C7387A53 *, void *, CStruct *);
extern void fn_80010E78(s32);
bool fn_800F5E3C(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4, CStruct *arg5) {
    Unk_0E2E8431 *temp_r9;

    fn_80010D94(((Unk_9994C3F5 *)lbl_802FFE98)->unk0x11C, 0x20);
    fn_800F36C8(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_800F5F8C(arg0, arg4, arg5);
    temp_r9 = arg0->unk0x50;
    ((s32 (*)(void *, void *, void *))temp_r9->unk0x74)((char *)arg0 + temp_r9->unk0x70, arg1, arg2);
    fn_80010E78(((Unk_9994C3F5 *)lbl_802FFE98)->unk0x11C);
    return false;
}
