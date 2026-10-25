// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010CEB0-0x8010CF10 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029CE28;
extern f32 lbl_8029CE2C;
extern f32 lbl_8029CE30;

// WINNER fn_8010CEB0 (96B) - doc 27. register f32 pin fr1 + fr10; identity
// init from farg0 occupies fr1 before any other pseudo can steal it; single-
// def conditional (no else reassignment) keeps one web through the branch.
f32 fn_8010CEB0(Unk_C7387A53 *arg0, s32 arg1, f32 farg0) {
    register f32 var_f1 __asm__("fr1");
    register f32 temp_f10 __asm__("fr10");

    var_f1 = farg0;
    temp_f10 = *((f32 *)&arg0->unk0x78);
    if ((temp_f10 != lbl_8029CE28) || (*((f32 *)&arg0->unk0x74) != lbl_8029CE2C)) {
        var_f1 = ((*((f32 *)&arg0->unk0x74) - temp_f10) * var_f1 * lbl_8029CE30) + temp_f10;
    }
    if ((arg1 != 0) && (var_f1 > *((f32 *)&arg0->unk0x74))) {
        return *((f32 *)&arg0->unk0x74);
    }
    return var_f1;
}
