// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CDB4-0x8022CE00 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8022D0E4(s32);
void *fn_8022D110(s32);
void *fn_8022C7BC(void *);
void fn_8022D160(void);
void *fn_8022CDB4(Unk_C8FEE62D *arg0) {
    Unk_C7387A53 *temp_r30;

    fn_8022D0E4(arg0->unk0x14);
    temp_r30 = fn_8022C7BC(fn_8022D110(0x24));
    fn_8022D160();
    temp_r30->unk0x20 = (s32)arg0;
    return temp_r30;
}
