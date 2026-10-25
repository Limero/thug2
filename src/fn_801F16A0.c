// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F16A0-0x801F16E8 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 fn_801F1684(s32);

void fn_801F16A0(CStruct *arg0) {
    s32 sp8;
    s32 ret;
    s32 out;

    sp8 = 0;
    GetChecksum_2(arg0, QB_LEVEL, &sp8, 0);
    ret = fn_801F1684(sp8);
    __asm__("mr %0, %1" : "=&r"(out) : "r"(ret));
    sp8 = out;
}
