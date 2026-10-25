// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C9D4-0x8009CA38 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern CStruct *lbl_80301914;
extern u32 lbl_80301918;
void fn_8009CAC4(CStruct *arg0, s32 arg1);
void fn_8009C9D4(void) {
    if (lbl_80301918 > 1) {
        lbl_80301918--;
    } else {
        if (lbl_80301914 != 0) {
            fn_8009CAC4(lbl_80301914, 3);
        }
        lbl_80301914 = 0;
        lbl_80301918 = 0U;
    }
}
