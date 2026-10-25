// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80229720-0x80229770 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
extern s32 fn_802069CC(Unk_31DE137E * arg0, s32 arg1);
s32 fn_80229720(CScript *arg0, s32 arg1) {
    s32 var_r3;

    var_r3 = arg0->unk0x18;
    if (var_r3 != 0) {
        var_r3 = GetChecksum_3((void *)var_r3, QB_TAGGING);
        if (var_r3 != 0) {
            return fn_802069CC((void *)var_r3, arg1);
        }
    }
    return var_r3;
}
