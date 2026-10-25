// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B6958-0x800B69A0 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_80061140(s32);
s32 fn_800B6958(CScript *arg0) {
    s32 v = arg0->unk0x210;
    s32 r = 0;
    if (v != 0 && fn_80061140(v) != 0) {
        r = 1;
    }
    return r;
}
