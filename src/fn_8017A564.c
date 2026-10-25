// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017A564-0x8017A5C0 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_8021D95C(Unk_A7137CF0 *);
void fn_8021B3E0(Unk_6A70655D *);
s32 fn_8017A564(void) {
    s32 temp_r30;

    temp_r30 = lbl_80305F9C;
    Script_RunScript(QB_CREATESERVERQUITDIALOG, 0, 0, 0, 0);
    fn_8021D95C(temp_r30);
    fn_8021B3E0(temp_r30);
    return 3;
}
