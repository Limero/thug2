// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D29C-0x8011D368 (204B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_80302CC4;
extern s32 lbl_80302CE0;
s32 fn_8011BC38();
s32 Script_GetInteger(s32, s32);
void fn_80120A00(s32, s32);
// PauseMusic @ 0x8011D29C
void PauseMusic(s32);
void PauseMusic(s32 arg0) {
    s32 temp_r0;

    if (fn_8011BC38() == 0) {
        switch (arg0) {
        case -1:
            if (lbl_80302CE0 != 0) {
                return;
            }
            PauseMusic(0);
            return;
        case 1:
            Script_GetInteger(QB_DEBUGSOUNDFX, 0);
            temp_r0 = lbl_80302CC4;
            lbl_80302CC4 = arg0;
            lbl_80302CE0 = temp_r0;
            fn_80120A00(arg0, 1);
            break;
        case 0:
            Script_GetInteger(QB_DEBUGSOUNDFX, 0);
            lbl_80302CC4 = arg0;
            fn_80120A00(arg0, 1);
            break;
        }
    }
}
