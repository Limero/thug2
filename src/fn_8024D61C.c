// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024D61C-0x8024D6B0 (148B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8024D2C8(void *);
extern s32 fn_80250EAC(CStruct *, s32);
s32 fn_8024D61C(Unk_C7387A53 *arg0, s32 arg1) {
    register s32 shift __asm__("r28");
    s32 mult;
    s32 ret;
    s32 v;
    s32 res;

    shift = arg1 - 1;
    mult = 1 << shift;
    ret = fn_8024D2C8(arg0);
    if ((mult == 1) || (ret == 0)) {
        return ret;
    }
    v = fn_80250EAC(arg0->unk0x44, shift);
    res = ((((ret >> 31) ^ ret) - (ret >> 31)) - 1) * mult + v + 1;
    if (ret < 0) {
        res = -res;
    }
    return res;
}
