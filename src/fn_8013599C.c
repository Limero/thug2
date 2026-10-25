// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013599C-0x801359DC (64B). Byte-identical.
#include "types.h"
extern char lbl_8039D4EC[];
extern char lbl_8039D4F0[];
extern bool lbl_8039D508;
// AUDSimpleAudioReset @ 0x8013599C
void AUDSimpleAudioReset(void) {
    OSDisableInterrupts();
    *(s32 *)&lbl_8039D4EC = 0;
    *(s32 *)&lbl_8039D4F0 = 0;
    lbl_8039D508 = 0;
    OSRestoreInterrupts();
}
