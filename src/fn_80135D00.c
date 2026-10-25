// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80135D00-0x80135D4C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_8039D518;
extern void AXSetVoiceState(s32, s32);

// AUDSimplePause @ 0x80135D00
void AUDSimplePause(s32 arg0) {
    s32 var_r29 = (arg0 == 0);
    AXSetVoiceState((s32)lbl_8039D518, var_r29);
    AXSetVoiceState((s32)((Unk_9ED273D2 *)&lbl_8039D518)->unk0x4, var_r29);
}
