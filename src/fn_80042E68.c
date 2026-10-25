// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80042E68-0x80042ED0 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80043800(Unk_E80761A5 *, s32, s32);
void fn_800438E8(Unk_E80761A5 *, s32);
void fn_80050188(void *, s32);
// CTextElement_DetachBlurEffect @ 0x80042E68
void CTextElement_DetachBlurEffect(Unk_C7387A53 *arg0) {
    s32 temp;

    if ((s32) arg0->unk0x1A8 != 0) {
        fn_800438E8(arg0, 0);
        temp = arg0->unk0x1A8;
        if (temp != 0) {
            fn_80050188(temp, 3);
        }
        arg0->unk0x1A8 = 0;
        fn_80043800(arg0, 1, 0);
    }
}
