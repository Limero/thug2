// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FCBB8-0x800FCC0C (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_800FCAA4(void);
void *fn_800FCBB8(Unk_C7387A53 *arg0) {
    if ((s32) arg0->unk0x38 != 0) {
        fn_800FCAA4();
        arg0->unk0x38 = 0;
    }
    if ((s32) arg0->unk0x3C != 0) {
        return (char *)arg0 + 0x18;
    }
    return NULL;
}
