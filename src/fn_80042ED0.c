// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80042ED0-0x80042F38 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800438E8(Unk_E80761A5 *, s32);
void fn_80043800(Unk_E80761A5 *, s32, s32);
// CTextElement_SetShadowState @ 0x80042ED0
void CTextElement_SetShadowState(Unk_B0F19D72 *arg0, s32 arg1) {
    if (arg1 != 0) {
        if ((s32) arg0->unk0x1AC == 0) {
            arg0->unk0x1AC = 1;
            fn_80043800(arg0, arg0->unk0x1A4, 1);
        }
    } else if ((s32) arg0->unk0x1AC != 0) {
        arg0->unk0x1AC = arg1;
        fn_800438E8(arg0, 1);
    }
}
