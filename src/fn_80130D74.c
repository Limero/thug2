// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80130D74-0x80130E34 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8012543C(s32);
bool fn_80130D74(Unk_15EF4A35 *arg0) {
    s32 i;

    if (arg0->unk0x38 == 0) {
        if (arg0->unk0xC != 0)
            return true;
        if (fn_8012543C(arg0->unk0xC8) != 0)
            return true;
        return false;
    }
    if (fn_8012543C(arg0->unk0xC8) == 0)
        return false;
    i = 0;
    if (arg0->unk0xC != 0) {
        i = 1;
    }
    if (i >= arg0->unk0x38)
        return true;
    for (; i < arg0->unk0x38; i++) {
        if (fn_8012543C(*(s32 *)(arg0->unk0x94 + i * 0x2C)) == 0)
            return false;
    }
    return true;
}
