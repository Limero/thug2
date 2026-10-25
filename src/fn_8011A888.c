// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A888-0x8011A8FC (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern s32 fn_80119470(void);
extern void Script_GetInteger(s32, s32);
extern void fn_8011F2A4(f32);
extern void fn_8011E0C4(f32);
extern f32 lbl_8029D518;
extern f32 lbl_80302C54;

void fn_8011A888(f32 farg0) {
    volatile double dum1;
    f32 var_f31;

    var_f31 = farg0;
    if (fn_80119470() == 0) {
        Script_GetInteger(QB_DEBUGSOUNDFX, 0);
        if (var_f31 <= lbl_8029D518) {
            var_f31 = lbl_8029D518;
        }
        lbl_80302C54 = var_f31;
        fn_8011F2A4(var_f31);
        fn_8011E0C4(var_f31);
    }
}
