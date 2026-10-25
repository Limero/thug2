// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80141880-0x8014190C (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
static s32 Mth_Rnd(s32 arg0);
static s32 fn_80173538(s32 arg0, s32 arg1);
void fn_80141880(Unk_2B0B333E *arg0) {
    s32 temp_r29;
    s32 temp_r3;
    Unk_C6B642AC *temp_r9;
    s32 var_r31;

    temp_r29 = lbl_80305EAC;
    var_r31 = 0;
    do {
        var_r31 += 1;
        temp_r3 = fn_80173538(temp_r29, Mth_Rnd(8));
    } while ((temp_r3 == arg0->unk0x184) && (var_r31 <= 0x13));
    arg0->unk0x184 = temp_r3;
    if (temp_r3 != 0) {
        temp_r9 = arg0->unk0x8;
        ((s32 (*)(void *, s32, s32))temp_r9->unk0x84)((char *)arg0 + temp_r9->unk0x80, temp_r3, 0);
    }
}
