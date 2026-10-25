// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F7748-0x801F77B8 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F7C;
s32 fn_80238964(void);
s32 fn_80057C90(CStruct *);
void fn_8022DD94(s32, s32, s32);
void fn_8024078C(s32);
void fn_8005572C(void);
void fn_8022D4C4(s32);
void fn_801F7748(CStruct *arg0) {
    s32 temp_r29;

    temp_r29 = *(s32 *)fn_80238964();
    fn_8022DD94(temp_r29, fn_80057C90(arg0), 0);
    fn_8024078C(0);
    fn_8005572C();
    if (lbl_80305F7C != 0) {
        fn_8022D4C4(*(s32 *)fn_80238964());
    }
}
