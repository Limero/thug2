// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E4558-0x800E45A8 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029A7AC;

/* file-local layouts: the shared Unk_C7387A53 class types 0x78 as s32, but
   retail loads it with lfs, so the merged majority type is wrong here. */
typedef struct fn_800E4558_sub {
    char pad0x0[0x78];
    f32 f_0x78;
    char pad0x7C[0xCC];
    s32 i_0x148;
} fn_800E4558_sub;

typedef struct fn_800E4558_obj {
    char pad0x0[0x1C];
    fn_800E4558_sub *unk0x1C;
} fn_800E4558_obj;

bool fn_800E4558(fn_800E4558_obj *arg0) {
    s32 var_r10;
    fn_800E4558_sub *temp_r11;

    temp_r11 = arg0->unk0x1C;
    if (temp_r11 != NULL) {
        var_r10 = 0;
        if ((temp_r11->i_0x148 != 0) || (temp_r11->f_0x78 > lbl_8029A7AC)) {
            var_r10 = 1;
        }
        if (var_r10 != 0) {
            return true;
        }
        return false;
    }
    return false;
}
