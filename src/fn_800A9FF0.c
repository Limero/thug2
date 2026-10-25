// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A9FF0-0x800AA02C (60B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303150[];
s32 fn_800A9FF0(Unk_C7387A53 *arg0) {
    s32 temp_r30;

    temp_r30 = arg0->unk0xC;
    return (*(s32 *)&lbl_80303150 + Tmr_GetTime()) - temp_r30;
}
