// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801878EC-0x80187934 (72B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 lbl_80305EC0;
extern s32 fn_80198F7C(s32 arg0);
extern s32 AddInteger(CStruct * arg0, s32 arg1, s32 arg2);

void fn_801878EC(Unk_6BF95B44 *arg0, s32 arg1) {
    s32 ret = fn_80198F7C(lbl_80305EC0);
    AddInteger(arg0->unk0x3A8, ret, arg1);
}
