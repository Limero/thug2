// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005F984-0x8005F9C4 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_80301B48[];
s32 fn_800F2AD8(s32, s32, s32);

s32 fn_8005F984(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        return 0;
    }
    return fn_800F2AD8(*(s32 *)&lbl_80301B48, arg0, arg1);
}
