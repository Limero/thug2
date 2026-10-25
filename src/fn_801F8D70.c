// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F8D70-0x801F8DA8 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
f32 fn_801F8C14();                                  

void fn_801F8D70(Unk_C7387A53 *arg0) {
    *((f32 *)&arg0->unk0x20) = (f32) (*((f32 *)&arg0->unk0xC) - fn_801F8C14());
}
