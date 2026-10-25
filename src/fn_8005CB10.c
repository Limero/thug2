// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005CB10-0x8005CBCC (188B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005D380(CStruct *, s32 *, s32);
s32 fn_8005C5B4(CStruct *);
void fn_8005C6C0(CStruct *, s32);
void fn_8001075C(s32);
extern char lbl_802936B4[];
s32 fn_8005CB10(CStruct *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r3;
    Unk_4E705049 *temp_r9;

    fn_8001075C(lbl_802936B4);
    temp_r9 = arg0->unk0x10;
    temp_r3 = ((s32 (*)(void *, void *, void *, void *, void *, void *, void *))temp_r9->unk0x1C)((char *)arg0 + temp_r9->unk0x18, arg1, arg2, arg3, arg4, arg5, arg7);
    if (temp_r3 != 0) {
        fn_8005C6C0(temp_r3, arg6);
        temp_r30 = arg0->unk0x8;
        sp8 = fn_8005C5B4(temp_r3);
        fn_8005D380(temp_r30, &sp8, temp_r3);
    }
    fn_80010760();
    return temp_r3;
}
