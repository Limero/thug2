// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E574-0x8009E5A8 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Delegates to fn_80126FF4(arg1, arg0->unk0x24) when unk0x24 is set,
// else returns arg1 unchanged (sibling of fn_8009E474).
// Suggested rename: fn_8009E574_register_or_pass_through.
#include "types.h"
#include "structs.h"
s32 fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 fn_8009E574(Unk_C7387A53 *arg0, CStruct *arg1) {
    if (arg0->unk0x24 != 0) {
        return fn_80126FF4(arg1, arg0->unk0x24);
    }
    return (s32)arg1;
}