// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80135AC8-0x80135AFC (52B). Byte-identical.
#include "types.h"
extern u32 lbl_8039D4E8;
extern char lbl_8039D4EC[];
extern char lbl_8039D4F0[];
// AUDSimpleAudioGetFreeReadBufferSamples @ 0x80135AC8
s32 AUDSimpleAudioGetFreeReadBufferSamples(void) {
    u32 temp_r3;
    u32 temp_r0;
    s32 var_r3;

    temp_r3 = *(u32 *)&lbl_8039D4EC;
    temp_r0 = *(u32 *)&lbl_8039D4F0;
    if (temp_r3 >= temp_r0) {
        var_r3 = lbl_8039D4E8 - (temp_r3 - temp_r0);
    } else {
        var_r3 = temp_r0 - temp_r3;
    }
    return var_r3;
}
