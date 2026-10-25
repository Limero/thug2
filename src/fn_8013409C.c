// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013409C-0x801340FC (96B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80132458(Unk_B0F19D72 *);
void fn_8013409C(CScript *arg0) {
    s32 *var_r10;
    s32 temp_r11;
    s32 temp_r9;

    goto loop_2;
block_5:
    fn_80132458(arg0);
    if (arg0->unk0x1F4 != 0) {
        return;
    }
loop_2:
    var_r10 = (s32 *)((char *)arg0 + 0x14C);
    temp_r11 = arg0->unk0x1E8 * 8;
    temp_r9 = *(s32 *)((char *)var_r10 + temp_r11);
    if (temp_r9 == 0) {
        goto block_5;
    }
    *(s32 *)((char *)var_r10 + temp_r11) = temp_r9 - 1;
}
