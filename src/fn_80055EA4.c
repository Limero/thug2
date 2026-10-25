// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80055EA4-0x80055EEC (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800579C4(CStruct *, s32 *, s32);
s32 fn_80057C90(CStruct *);
void fn_80055EA4(Unk_FFAD6788 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 temp_r29;

    temp_r29 = arg0->unk0xD0;
    sp8 = fn_80057C90(arg1);
    fn_800579C4(temp_r29, &sp8, arg1);
}
