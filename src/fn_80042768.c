// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80042768-0x800427AC (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80053790(s32);                               

void fn_80042768(Unk_CACD1EF6 *arg0, s32 arg1) {
    arg0->unk0x194 = arg1;
    arg0->unk0x198 = fn_80053790(arg1);
    arg0->unk0xC = (s32) (arg0->unk0xC | 0x1000);
}
