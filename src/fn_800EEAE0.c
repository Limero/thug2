// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EEAE0-0x800EEB10 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: script command wrapper. Resolves the object id stored at
// arg0+0x1C and reads script property `arg1` (hash) from it via the generic
// property getter GetFloat, returning the value as a float. The real
// signature takes two args (obj, property-hash); arg1 passes through to the
// getter untouched (hence the passthrough r4). Suggested rename:
// ScriptGetPropertyFloat or similar (property-getter family).
#include "types.h"
#include "structs.h"
extern void GetFloat(CStruct *, s32, f32 *, s32);
f32 fn_800EEAE0(Unk_31DE137E *arg0, s32 arg1) {
    f32 sp8;

    GetFloat(arg0->unk0x1C, arg1, &sp8, 1);
    return sp8;
}
