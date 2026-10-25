// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80229770-0x802297C0 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
extern s32 fn_802069C4(Unk_31DE137E * arg0);
s32 fn_80229770(CScript *arg0) {
    s32 temp_r0;
    s32 temp_r3;

    temp_r0 = arg0->unk0x18;
    if (temp_r0 == 0) {
        return 0;
    }
    temp_r3 = GetChecksum_3(temp_r0, QB_TAGGING);
    if (temp_r3 == 0) {
        return 0;
    }
    return fn_802069C4(temp_r3);
}
