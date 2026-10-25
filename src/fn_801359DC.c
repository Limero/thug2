// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801359DC-0x80135A38 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8039D518[];
void AXSetVoiceVe(void *, void *);
// AUDSimpleAudioSetVolume @ 0x801359DC
void AUDSimpleAudioSetVolume(s16 arg0, s16 arg1) {
    Unk_B0EC4F37 sp8;
    void **vp;

    vp = (void **)&lbl_8039D518;
    sp8.unk0x2 = 0;
    *(u16 *)&sp8 = arg0;
    AXSetVoiceVe(*vp, &sp8);
    *(u16 *)&sp8 = arg1;
    AXSetVoiceVe(vp[1], &sp8);
}
