// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80133F8C-0x8013400C (128B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 sSameOrLowerPrecedence(s32, s32);
void fn_80132458(Unk_B0F19D72 *);
void fn_80133F24(CScript *, s32);
void fn_80133F8C(Unk_B0F19D72 * arg0, s32 arg1) {
    s32 *var_r28;
    s32 *var_r29;
    s32 temp_r0;

    var_r28 = (s32 *)((char *)arg0 + 0x14C);
    var_r29 = (s32 *)((char *)arg0 + 0x148);
loop_1:
    if (arg0->unk0x1EC == 0) {
        goto block_6;
    }
    temp_r0 = arg0->unk0x1E8 * 8;
    if (*(s32 *)((char *)var_r28 + temp_r0) != 0) {
        goto block_6;
    }
    if (sSameOrLowerPrecedence(arg1, *(s32 *)((char *)var_r29 + temp_r0)) == 0) {
        goto block_6;
    }
    fn_80132458(arg0);
    goto loop_1;
block_6:
    fn_80133F24(arg0, arg1);
}
