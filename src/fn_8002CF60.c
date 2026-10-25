// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002CF60-0x8002CFF8 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *fn_8002DAC0(s32);
void *fn_8002CA4C(void *);
void *memset(void *, s32, s32);
s32 fn_8002CF60(s32 arg0) {
    s32 var_r30;
    s32 *var_r31;
    CScript *temp_r3;

    var_r31 = (s32 *)(arg0 + 0x2C);
    var_r30 = 0;
loop_1:
    if (*var_r31 != NULL) {
        var_r30 += 1;
        var_r31 += 1;
        if (var_r30 <= 0x11) {
            goto loop_1;
        }
        return -1;
    }
    temp_r3 = fn_8002CA4C(fn_8002DAC0(0x1E8));
    *var_r31 = (s32)temp_r3;
    temp_r3->unk0x1E4 = (s32) (temp_r3->unk0x1E4 & QB_UNKNOWN_0xFFFEFFFF);
    memset((void *)(*var_r31 + 4), 0, 0xF0);
    memset((void *)(*var_r31 + 0xF4), 0, 0xF0);
    return var_r30;
}