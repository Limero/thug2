// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A95C-0x8011A9FC (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_8011A95C: voice-pool slot search over the 59 x 0x3C lbl_80387E44 slots:
// id match with fn_8011ED40(i)!=0 -> *out=i, 1. Retail hoists out!=NULL into cr4
// (mfcr/mtcrf cr-save) — ngccc reproduced it from plain C.
// Suggested rename: fn_VoicePoolFind.
#include "types.h"
extern s32 fn_80119470(void);
extern s32 fn_8011ED40(s32);
extern char lbl_80387E44[];
bool fn_8011A95C(void *arg0, s32 id, s32 *out) {
    s32 i;
    s32 v;
    s32 *p;

    if (fn_80119470() != 0) {
        return false;
    }
    if (id == 0) {
        return false;
    }
    i = 0;
    p = (s32 *)lbl_80387E44;
    do {
        v = *p;
        p += 15;
        if (v == id) {
            if (fn_8011ED40(i) == 0) {
                return false;
            }
            if (out != NULL) {
                *out = i;
            }
            return true;
        }
        i++;
    } while (i <= 0x3A);
    return false;
}
