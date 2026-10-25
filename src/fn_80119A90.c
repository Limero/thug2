// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119A90-0x80119AF8 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 *lbl_80302C40;
extern s32 lbl_80302C4C;
extern char lbl_80388C18[];

s32 fn_80119470(void);
void StopAllSoundFX(void);

void fn_80119A90(void) {
    s32 temp_r31;
    char *base;
    s32 *var_r9;
    s32 var_ctr;

    temp_r31 = fn_80119470();
    if (temp_r31 == 0) {
        StopAllSoundFX();
        lbl_80302C40 = (s32 *)temp_r31;
        lbl_80302C4C = temp_r31;
        base = lbl_80388C18;
        var_r9 = (s32 *)(base + 0xBF0);
        var_ctr = 0x80;
        do {
            *var_r9 = 0;
            var_r9 = (s32 *)((char *)var_r9 - 0x18);
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
}
