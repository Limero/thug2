// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009A574-0x8009A5B4 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8009A6C0(void *);
void fn_8009A658(void *);
void fn_8009A574(CStruct *arg0, s32 arg1) {
    if ((s32) arg0->unk0x4 != arg1) {
        arg0->unk0x4 = arg1;
        if (arg1 != 0) {
            fn_8009A6C0(arg0);
        } else {
            fn_8009A658(arg0);
        }
    }
}
