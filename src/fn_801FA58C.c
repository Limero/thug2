// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA58C-0x801FA5E4 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_803A30E0[];
#include "structs.h"
extern f32 lbl_802AE5AC;
void fn_801F9734(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, f32 farg0);
void fn_801FA58C(Unk_C7387A53 *arg0) {
    CStruct *var_r31;
    register s32 pg29 __asm__("r29");
    var_r31 = arg0->unk0x24;
    if (var_r31 != NULL) {
        pg29 = (s32)0x803A0000;
        do {
            fn_801F9734(var_r31, (s32)((char *)pg29 + 0x30E0), (s32)((char *)pg29 + 0x30E0), lbl_802AE5AC);
            var_r31 = var_r31->unk0x4;
        } while (var_r31 != NULL);
    }
}
