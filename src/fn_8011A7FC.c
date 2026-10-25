// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A7FC-0x8011A888 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern f32 lbl_8029D50C;
extern f32 lbl_8029D510;
extern f32 lbl_8029D514;
extern f32 lbl_802FFE64;
extern f32 lbl_80302C50;
s32 Script_GetInteger(void *, void *);
s32 fn_80119470(void);
void fn_8011F298(f32);
void fn_8011E094(f32);
void fn_8011A7FC(f32 farg0, f32 farg1) {
    volatile double _dummy;
    if (fn_80119470() == 0) {
        Script_GetInteger(QB_DEBUGSOUNDFX, 0);
        lbl_80302C50 = farg0;
        farg0 = (farg0 * lbl_802FFE64) / lbl_8029D50C;
        if (farg0 < lbl_8029D510) {
            farg0 = lbl_8029D514;
        }
        fn_8011F298(farg0);
        fn_8011E094(farg0);
    }
}
