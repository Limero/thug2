// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022DD54-0x8022DD94 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80056174(Unk_CFB386B2 * arg0);
void fn_8022D4C4(Unk_DB0E2BAB * arg0);
s32 fn_8022DD54(void *arg0) {
    register void *a0 __asm__("r29");
    s32 temp_r30;

    a0 = arg0;
    temp_r30 = fn_80056174(((Unk_C8FEE62D *)a0)->unk0x14);
    fn_8022D4C4(a0);
    return temp_r30;
}
