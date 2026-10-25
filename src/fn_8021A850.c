// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021A850-0x8021A8C8 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80303448;
extern char lbl_802AFDF0[];
s32 fn_801370C4(Unk_F386DC9F * arg0, s32 arg1, char * arg2, s32 arg3, s32 arg4, s32 arg5);
void *fn_80139510(s32 arg0, s32 arg1, Unk_C8FEE62D * arg2, s32 arg3, s32 arg4, s32 arg5);
s32 fn_8022ACE0(s32 arg0, s32 arg1, s32 arg2);
s32 fn_8021A850(Unk_C7387A53 *arg0) {
    s32 temp_r3;

    temp_r3 = fn_801370C4(lbl_80303448, 0, (s32)lbl_802AFDF0, 0x141F, 0, 0x35);
    arg0->unk0x24 = temp_r3;
    fn_80139510(temp_r3 + 4, 0x10, (s32)fn_8022ACE0, 3, (s32)arg0, 0x80);
    return arg0->unk0x24;
}
