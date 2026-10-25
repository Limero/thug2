// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F8D2C-0x801F8D70 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
f32 fn_801F8C14();                                  

void fn_801F8D2C(Unk_C8FEE62D *arg0) {
    if ((s32) arg0->unk0x18 != 0) {
        *((f32 *)&arg0->unk0xC) = (f32) (fn_801F8C14() + *((f32 *)&arg0->unk0x20));
    }
}
