// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80150B44-0x80150B94 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_80305F1C[];
void fn_800B0EA4(s32 arg0);
void fn_800B0590(void);
void fn_801AAF94(Unk_C7387A53 * arg0);
void fn_801A9528(CStruct * arg0);
void fn_800597DC(void);
void fn_8005985C(void);
void fn_80150B44(s32 arg0) {
    Unk_C7387A53 *temp_r30;

    temp_r30 = *(s32 **)&lbl_80305EAC;
    fn_800B0EA4(arg0);
    fn_800B0590();
    fn_801AAF94(temp_r30->unk0x28);
    fn_801A9528(*(s32 *)&lbl_80305F1C);
    fn_800597DC();
    fn_8005985C();
}
