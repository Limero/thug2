// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058320-0x8005834C (44B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8005F7DC(s32);
void fn_80058320(CStruct *arg0, s32 arg1) {
    if ((s32) arg0->unk0x10 != 0) {
        fn_8005F7DC(arg0->unk0x10);
    }
}
