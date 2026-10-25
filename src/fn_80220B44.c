// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80220B44-0x80220BA8 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_80305F9C;
extern char lbl_802AFE88[];
void fn_80128294(s32, s32, s32 *, s32);
s32 fn_8021D358(s32, s32);
s32 fn_80229B94(void *);
s32 ScriptPlayerHasFlag(s32 arg0) {
    s32 sp8;
    void *flag = lbl_80305F9C;
    s32 temp_r3;

    fn_80128294(arg0, (s32)lbl_802AFE88, &sp8, 0);
    temp_r3 = fn_8021D358((s32)flag, ((Unk_B0EC4F37 *)&sp8)->unk0x2);
    return temp_r3 != 0 ? fn_80229B94((void *)temp_r3) : 1;
}
