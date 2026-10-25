// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801358F0-0x8013599C (172B). Byte-identical.
#include "types.h"
extern char lbl_8039D4E4[];
extern char lbl_8039D4F8[];
extern char lbl_8039D518[];
extern char lbl_8039D940[];
extern char fn_8011E8D0[];
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);
void AXRegisterCallback(s32);
void AXSetVoiceState(void *, u16);
void AXFreeVoice(void *);

// AUDSimpleExitAudioDecoder @ 0x801358F0
void AUDSimpleExitAudioDecoder(void) {
    s32 var_r28;
    void **vp;
    void **cb;

    var_r28 = OSDisableInterrupts();
    vp = (void **)&lbl_8039D518;
    AXRegisterCallback((s32)fn_8011E8D0);
    AXSetVoiceState(vp[0], 0);
    AXSetVoiceState(vp[1], 0);
    AXFreeVoice(vp[0]);
    AXFreeVoice(vp[1]);
    vp[1] = NULL;
    vp[0] = NULL;
    OSRestoreInterrupts(var_r28);
    cb = (void **)&lbl_8039D940;
    ((void (*)(s32))cb[1])(*(s32 *)&lbl_8039D4F8);
    ((void (*)(s32))cb[1])(*(s32 *)&lbl_8039D4E4);
}
