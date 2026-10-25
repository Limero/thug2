// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D4F8-0x8011D57C (132B). Byte-identical.
#include "types.h"
extern f32 lbl_8029D5D8;
extern f32 lbl_8029D5DC;
extern f32 lbl_80302CAC;
extern bool lbl_80302CBC;
extern s32 lbl_80302CD0;
s32 fn_8011BC38(void);
f32 fn_801204CC(f32);
// SetMusicStreamVolume @ 0x8011D4F8
void SetMusicStreamVolume(f32 farg0) {
    volatile double _dummy;

    if ((fn_8011BC38() == 0) && !(farg0 > lbl_8029D5D8) && !(farg0 < lbl_8029D5DC)) {
        lbl_80302CAC = farg0;
        if ((lbl_80302CBC != 0) && (lbl_80302CD0 == 1)) {
            fn_801204CC(farg0);
        }
    }
}
