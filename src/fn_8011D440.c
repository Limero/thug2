// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D440-0x8011D4EC (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern f32 lbl_8029D5D0;
extern f32 lbl_8029D5D4;
extern s32 lbl_80302CA4;
extern f32 lbl_80302CA8;
extern bool lbl_80302CBC;
extern s32 lbl_80302CD0;
s32 fn_8011BC38(void);
s32 Script_GetInteger(s32, s32);
f32 fn_801204CC(f32);
// SetVolume @ 0x8011D440
void SetVolume(f32 farg0) {
    volatile double _dummy;

    if ((fn_8011BC38() == 0) && !(farg0 > lbl_8029D5D0) && !(farg0 < lbl_8029D5D4)) {
        lbl_80302CA8 = farg0;
        if ((lbl_80302CBC != 0) && (lbl_80302CD0 == 0) && ((lbl_80302CA4 == 0) || (Script_GetInteger(QB_FORCEAMBIENTSFXTOMUSICVOLUME, 0) != 0))) {
            fn_801204CC(farg0);
        }
    }
}
