// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070DB0-0x80070E74 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80070C78(void *, s32);
s32 fn_80070D40(s32);
// UPDATED 2026-09-21 (doc-56): fn_80070BF0 was called with NO prototype in
// scope -> ngccc emitted `crclr cr1eq` (one extra word, tail shifted);
// 46.0% -> 65.3%. Residual is the list-walker web, parked.
void fn_80070BF0(Unk_C8FEE62D *arg0);
extern char lbl_803015E8[];
extern char lbl_803015EC[];
void fn_80070DB0(void) {
    CStruct *temp_r31;
    s32 *var_r30;
    Unk_DB0E2BAB *var_r31;

    if ((s32 *) *(s32 * *)&lbl_803015EC != NULL) {
        do {
            temp_r31 = *(s32 *)&lbl_803015EC;
            var_r30 = (s32 *)lbl_803015E8;
            fn_80070D40(temp_r31);
            temp_r31->unk0x4 = (s32) (temp_r31->unk0x4 & QB_UNKNOWN_0xFFFFFEFF);
goto test;
inc:
            var_r30 = *((s32 **)var_r30);
test:
            if (*((s32 *)var_r30) != NULL) {
                if (fn_80070C78(temp_r31, *((s32 *)var_r30)) >= 0) {
                    goto inc;
                }
            }
            temp_r31->unk0x0 = *((s32 *)var_r30);
            *((s32 *)var_r30) = temp_r31;
        } while ((s32 *) *(s32 *)&lbl_803015EC != NULL);
    }
    var_r31 = *(void * *)&lbl_803015E8;
    if (var_r31 != NULL) {
        do {
            if ((s32) var_r31->unk0x14 != 0) {
                fn_80070BF0(var_r31);
            }
            var_r31 = var_r31->unk0x0;
        } while (var_r31 != NULL);
    }
}
