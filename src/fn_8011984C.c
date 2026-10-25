// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011984C-0x801198C8 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8029D4E4;
extern f32 lbl_80302C3C;
extern char lbl_80388C18[];
extern s32 lbl_80302C40;
extern s32 lbl_80302C44;
extern s32 lbl_80302C4C;
s32 fn_80119470(void);
void CleanUpSoundFX(void);
void fn_8011984C(void) {
    s32 t = fn_80119470();
    s32 i;
    s32 *p;
    char *b;
    if (t == 0) {
        lbl_80302C40 = t;
        lbl_80302C4C = t;
        b = lbl_80388C18;
        p = (s32 *)((char *)b + 0xBF0);
        for (i = 0x80; i != 0; i--) {
            *(s32 *)p = 0;
            p = (s32 *)((char *)p - 0x18);
        }
        CleanUpSoundFX();
        lbl_80302C44 = 0;
        lbl_80302C3C = lbl_8029D4E4;
    }
}
