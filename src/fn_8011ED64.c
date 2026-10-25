// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011ED64-0x8011EEFC (408B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern f32 lbl_8029D690;
extern f32 lbl_8029D694;
extern f32 lbl_8029D698;
extern f64 lbl_8029D6A0;
extern f64 lbl_8029D6A8;
extern f32 lbl_80302CE8;
extern f32 lbl_80302CEC;

s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);
void fn_8011F590(void *, void *, s32, s32, f32, f32, f32);

typedef struct { s32 a; s32 b; } Ent;
typedef struct { f32 x; f32 y; } P2;
extern Ent lbl_8038EBB8[];

void fn_8011ED64(s32 arg0, P2 *arg1, f32 farg0) {
    u32 var_r31;
    f32 temp_f0;
    s32 entry;
    void *sub;
    u32 intr;

    var_r31 = 0x10000;
    if (farg0 != lbl_8029D690) {
        temp_f0 = farg0 * lbl_8029D694 * lbl_8029D698;
        var_r31 = (u32)temp_f0;
        if (var_r31 > 0xFFFFFU) {
            var_r31 = 0xFFFFF;
        }
        if (var_r31 == 0) {
            var_r31 = 1;
        }
    }
    var_r31 = (u32)((f32)(f64)var_r31 * lbl_80302CEC);
    intr = OSDisableInterrupts();
    entry = lbl_8038EBB8[arg0].a;
    if (entry != 0) {
        sub = (void *)(entry + 0x138);
        if (arg1 != 0) {
            fn_8011F590(sub, (void *)entry, var_r31, 1, arg1->x, arg1->y, lbl_80302CE8);
        } else {
            fn_8011F590(sub, (void *)entry, var_r31, 1, lbl_8029D690, lbl_8029D690, lbl_80302CE8);
        }
    }
    OSRestoreInterrupts(intr);
}
