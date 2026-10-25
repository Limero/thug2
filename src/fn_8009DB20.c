// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DB20-0x8009DB74 (84B). Byte-identical.
#include "types.h"
extern bool lbl_80301A10;
extern s32 lbl_80301A2C;
extern s32 lbl_80301A30;
void Mem_Free_3(s32);
void fn_8009DB20(void) {
    lbl_80301A30 = 0;
    if (lbl_80301A2C != 0) {
        Mem_Free_3(lbl_80301A2C);
        lbl_80301A2C = 0;
    }
    lbl_80301A10 = 0;
    fn_8009DEA0();
}
