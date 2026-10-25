// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012865C-0x801286D0 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: script-node type-7 attribute lookup over the QB node tree
// (fn_80127F60 family = recursive node walker): on success stores the node
// id (arg1) and the fetched value into the 2-word out-param and returns 1;
// on miss optionally resets the walker state via fn_80129570 when arg3 is
// set. Suggested rename: ScriptNodeGetAttr7.
#include "types.h"
#include "structs.h"
s32 fn_80129570(void *, void *);
s32 fn_80127F60(CStruct *, void *, void *, f32 *);
bool fn_8012865C(CStruct *arg0, s32 arg1, CStruct *arg2, s32 arg3) {
    s32 sp8;

    if (fn_80127F60(arg0, arg1, 7, &sp8) != 0) {
        arg2->unk0x0 = arg1;
        arg2->unk0x4 = sp8;
        return true;
    }
    if (arg3 != 0) {
        fn_80129570(arg0, 0);
    }
    return false;
}
