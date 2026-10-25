// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801232EC-0x801233A8 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8039BA58[];
extern char lbl_8039BE9C[];
extern char lbl_8039BE6C[];
extern char lbl_8039BE58[];
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);
void AXRegisterCallback(s32);
void AXSetVoiceState(void *, u16);
void AXFreeVoice(void *);

typedef struct {
    char pad0[4];
    void *unk4;
    char pad8[0x98];
    s32 unkA0;
} CB_t;

void fn_801232EC(void) {
    s32 var_r28;
    void **vp;
    CB_t *cb = (CB_t *)lbl_8039BA58;

    if (cb->unkA0 != 0x4E4F4E45) {
        var_r28 = OSDisableInterrupts();
        vp = (void **)&lbl_8039BE9C;
        AXRegisterCallback(0);
        AXSetVoiceState(vp[0], 0);
        AXSetVoiceState(vp[1], 0);
        AXFreeVoice(vp[0]);
        AXFreeVoice(vp[1]);
        vp[1] = NULL;
        vp[0] = NULL;
        OSRestoreInterrupts(var_r28);
        ((void (*)(s32))cb->unk4)(*(s32 *)&lbl_8039BE6C);
        ((void (*)(s32))cb->unk4)(*(s32 *)&lbl_8039BE58);
    }
}
