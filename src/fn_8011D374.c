// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D374-0x8011D440 (204B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_80302CC8;
extern s32 lbl_80302CE4;
s32 fn_8011BC60();
s32 Script_GetInteger(s32, s32);
void fn_80120A00(s32, s32);
// PauseStream @ 0x8011D374
void PauseStream(s32);
void PauseStream(s32 arg0) {
    s32 temp_r0;

    if (fn_8011BC60() == 0) {
        switch (arg0) {
        case -1:
            if (lbl_80302CE4 != 0) {
                return;
            }
            PauseStream(0);
            return;
        case 1:
            Script_GetInteger(QB_DEBUGSOUNDFX, 0);
            temp_r0 = lbl_80302CC8;
            lbl_80302CC8 = arg0;
            lbl_80302CE4 = temp_r0;
            fn_80120A00(arg0, 0);
            break;
        case 0:
            Script_GetInteger(QB_DEBUGSOUNDFX, 0);
            lbl_80302CC8 = arg0;
            fn_80120A00(arg0, 0);
            break;
        }
    }
}
