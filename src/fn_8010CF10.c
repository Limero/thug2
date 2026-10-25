// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010CF10-0x8010CF70 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029CE34;
extern f32 lbl_8029CE38;
extern f32 lbl_8029CE3C;

// WINNER fn_8010CF10 (96B) - twin of 8010CEB0, offsets 0x70/0x6C,
// consts CE34/38/3C.
f32 fn_8010CF10(CStruct *arg0, s32 arg1, f32 farg0) {
    register f32 var_f1 __asm__("fr1");
    register f32 temp_f10 __asm__("fr10");

    var_f1 = farg0;
    temp_f10 = *((f32 *)&arg0->unk0x70);
    if ((temp_f10 != lbl_8029CE34) || (*((f32 *)&arg0->unk0x6C) != lbl_8029CE38)) {
        var_f1 = ((*((f32 *)&arg0->unk0x6C) - temp_f10) * var_f1 * lbl_8029CE3C) + temp_f10;
    }
    if ((arg1 != 0) && (var_f1 > *((f32 *)&arg0->unk0x6C))) {
        return *((f32 *)&arg0->unk0x6C);
    }
    return var_f1;
}
