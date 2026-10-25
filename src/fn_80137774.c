// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137774-0x801377A4 (48B). Byte-identical.
#include "types.h"
void strcpy(s32, s32);
void fn_80137774(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r9;

    temp_r9 = (arg1 << 5) + 0x21A8;
    strcpy(arg0 + temp_r9, arg2);
}
