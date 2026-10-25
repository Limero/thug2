// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80244440-0x802444D0 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8023821C(s32, Unk_5D1D68CC *, s32 *);
s32 fn_80238964(void);
s32 fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
s32 fn_8024402C(Unk_7044F700 *, Unk_A5D07D11 *, s32, s32, CStruct *);

void fn_80244440(Unk_7044F700 *arg0, s32 arg1, s32 arg2, CStruct *arg3) {
    s32 sp18;
    s32 sp10[2];
    volatile s32 sp8;
    volatile s32 spC;

    fn_80240B0C(&sp8, 0, 0, 0, 0, 0, 0);
    fn_8024402C(arg0, &sp8, arg1, arg2, arg3);
    sp10[0] = sp8;
    *(u16 *)&sp10[1] = *(u16 *)&spC;
    fn_8023821C(fn_80238964(), &sp10, &sp18);
}