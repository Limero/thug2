// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80187B0C-0x80187B84 (120B). Byte-identical.
#include "types.h"
#include "structs.h"

extern void* lbl_80305EAC;
extern s32 fn_801A6CCC(Unk_93C2DF4D * arg0);

s32 fn_80187B0C(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r3;
    s32 idx;
    char *base;

    var_r3 = arg2;
    if (arg1 == -1) {
        return 0;
    }
    if (var_r3 == -1) {
        var_r3 = fn_801A6CCC(((Unk_C7387A53 *)lbl_80305EAC)->unk0x24);
    }
    idx = var_r3 * 0xA + arg1 - 1;
    idx <<= 2;
    base = (char *)arg0 + 0x60;
    return *(s32 *)(base + idx) == 0;
}
