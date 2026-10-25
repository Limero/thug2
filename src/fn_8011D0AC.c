// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D0AC-0x8011D0E8 (60B). Byte-identical.
#include "types.h"
extern bool lbl_80302CBC;
void StopMusic(void);
void fn_8011BEAC(s32);
bool fn_8011D0AC(void) {
    if (lbl_80302CBC != 0) {
        StopMusic();
        fn_8011BEAC(-1);
    }
    return false;
}
