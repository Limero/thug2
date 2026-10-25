// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80123938-0x8012399C (100B). Byte-identical.
#include "types.h"
extern s32 lbl_8039BE7C;
extern s32 lbl_8039BE80;
s32 OSDisableInterrupts(void);
s32 fn_8012399C(s32, s32);
s32 OSRestoreInterrupts(s32);
// VIDSimpleAudioStartPlayback @ 0x80123938
void VIDSimpleAudioStartPlayback(s32 arg0, s32 arg1) {
    s32 temp_r29;

    temp_r29 = OSDisableInterrupts();
    if (lbl_8039BE80 != 0) {
        lbl_8039BE7C = 1;
        fn_8012399C(arg0, arg1);
    }
    OSRestoreInterrupts(temp_r29);
}
