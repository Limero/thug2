// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DB74-0x8009DBB0 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80301A2C;
extern s32 lbl_80301A30;
void fn_8009DB74(void) {
    s32 temp_r3;
    s32 *p2c;
    s32 *p30;

    p2c = &lbl_80301A2C;
    p30 = &lbl_80301A30;
    fn_8009DE7C();
    temp_r3 = Mem_Alloc_3();
    *p2c = temp_r3;
    *p30 = temp_r3;
}