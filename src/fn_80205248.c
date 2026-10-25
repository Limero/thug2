// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80205248-0x80205278 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: script property-getter wrapper (same family as
// fn_800EEAE0). Resolves the object id at arg0+0x28, reads script property
// `arg1` (hash) via the generic getter GetFloat, returns the float value.
// Suggested rename: ScriptGetPropertyFloat variant.
#include "types.h"
#include "structs.h"
s32 GetFloat(CStruct *, void *, f32 *, void *);
f32 fn_80205248(Unk_C7387A53 *arg0, s32 arg1) {
    f32 sp8;

    GetFloat(arg0->unk0x28, arg1, &sp8, 1);
    return sp8;
}
