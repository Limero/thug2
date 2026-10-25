// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FFCE4-0x801FFD5C (120B). Byte-identical.
// Object-field initializer: after fn_8009F53C() + a 4-iteration delay loop,
// sets unk0x18 = string ptr, unk0x4 = QB hash 0x2C747D8A, and three
// float constants at 0x98/0x9C/0xA4. Likely a script-object spawn setup.
// Suggested rename: fn_InitScriptObjFields.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AEB54;
extern f32 lbl_802AEB58;
extern f32 lbl_802AEB5C;
extern char lbl_802AEBA0[];
void *fn_801FFCE4(Unk_DB0E2BAB *arg0) {
    s32 var_ctr;
    f32 v98;
    f32 v9C;
    f32 vA4;

    fn_8009F53C();
    var_ctr = 4;
    arg0->unk0x18 = (s32)lbl_802AEBA0;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    v98 = lbl_802AEB54;
    v9C = lbl_802AEB58;
    vA4 = lbl_802AEB5C;
    arg0->unk0x4 = QB_UNKNOWN_0x2C747D8A;
    arg0->unk0x98 = v98;
    *((f32 *)&arg0->unk0x9C) = v9C;
    arg0->unk0xA4 = vA4;
    return arg0;
}