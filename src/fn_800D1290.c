// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D1290-0x800D12DC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80301A38;
extern s32 fn_800A398C(s32 arg0, s32 arg1);

s32 fn_800D1290(CScript *arg0) {
    s32 var_r3;

    var_r3 = fn_800A398C(lbl_80301A38, arg0->unk0x20);
    if (var_r3 == 0) {
        var_r3 = fn_800A398C(lbl_80301A38, arg0->unk0x1C);
    }
    return var_r3;
}
