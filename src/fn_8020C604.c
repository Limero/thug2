// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020C604-0x8020C648 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801A99B0(Unk_03123917 *, s32 *, s32);
extern void fn_8020C54C(Unk_BF3B6DA6 *, s32);
s32 fn_8020C604(Unk_03123917 *arg0, void *arg1, s32 arg2) {
    s32 ret = fn_801A99B0((char *)arg0 + 0x1404, arg1, arg2);
    fn_8020C54C(arg0, 0);
    return ret;
}
