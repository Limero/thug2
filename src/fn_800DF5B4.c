// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DF5B4-0x800DF668 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void GetChecksum_2(void *, void *, void *, void *);
void fn_800DFB64(void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8009D364(s32, s32);
extern char lbl_8030191C[];
s32 GetInteger(CStruct *, void *, s32 *, void *);
void fn_800DF5B4(s32 arg0, CStruct *arg1) {
    s32 sp8;

    if (GetInteger(arg1, QB_PLAYER, &sp8, 0) != 0) {
        fn_800DFB64(arg0, fn_8009D364(*(s32 *)lbl_8030191C, sp8));
    } else if (GetInteger(arg1, QB_CONTROLLER, &sp8, 0) != 0) {
        fn_800DFB64(arg0, sp8);
    }
    GetChecksum_2(arg1, QB_BUTTONSETTINGS, arg0 + 0x530, 0);
}
