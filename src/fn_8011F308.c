// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011F308-0x8011F3A4 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029D6C0;
extern s32 lbl_80302CF0;
extern s32 lbl_80302CF8;
extern s32 lbl_8038ED90[];
void Mem_Free_3(s32);
void StopAllSoundFX(void);
void fn_8011F3A4(s32, s32, f32);
// CleanUpSoundFX @ 0x8011F308
void CleanUpSoundFX(void) {
    s32 i;

    StopAllSoundFX();
    lbl_80302CF0 = 0;
    i = 0;
    fn_8011F3A4(0, 0, lbl_8029D6C0);
    for (i = 0; i < lbl_80302CF8; i++) {
        Mem_Free_3(lbl_8038ED90[i]);
        lbl_8038ED90[i] = 0;
    }
    lbl_80302CF8 = 0;
}
