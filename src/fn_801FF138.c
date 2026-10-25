// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FF138-0x801FF164 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802AEA2C;
extern f32 lbl_802AEA30;
void fn_801FF138(CScript *arg0) {
    f32 temp_f13;
    f32 temp_f0;

    temp_f13 = lbl_802AEA2C;
    temp_f0 = lbl_802AEA30;
    arg0->unk0x20 = 0;
    __asm__("" ::: "memory");
    *((f32 *)&arg0->unk0x2C) = temp_f13;
    __asm__("" ::: "memory");
    *((f32 *)&arg0->unk0x24) = temp_f0;
    __asm__("" ::: "memory");
    *((f32 *)&arg0->unk0x28) = temp_f13;
    __asm__("" ::: "memory");
    arg0->unk0x1C = 0;
}
