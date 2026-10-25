// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FEAF8-0x801FEB48 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 fn_801417B8(CScript * arg0, s32 arg1);
bool fn_801FEAF8(Unk_D13885F6 *arg0) {
    f32 temp_f1;

    temp_f1 = fn_801417B8(arg0->unk0xC, 0xB84F532);
    *((f32 *)&arg0->unk0x20) = temp_f1;
    *((u16 *)&arg0->unk0x24) = 0;
    arg0->unk0x1C = 2;
    return true;
}
