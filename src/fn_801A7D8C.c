// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A7D8C-0x801A7DB4 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801A7D8C(Unk_823C90F7 *arg0, s32 arg1) {
    u16 *half;
    u16 *p;

    half = (u16 *)((char *)arg0 + 0x584);
    arg0->unk0x5D8 = (u16) (arg0->unk0x5D8 + arg1);
    p = half + arg0->unk0x630;
    *p = (u16)(*p + arg1);
}
