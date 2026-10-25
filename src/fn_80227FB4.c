// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80227FB4-0x8022805C (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void AddString(CStruct *, s32, void *);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
extern char lbl_802B016C[];
bool fn_80227FB4(u8 **arg0) {
    s32 sp8[64];
    s32 temp_r31;
    u8 *temp_r30;

    temp_r30 = *arg0;
    temp_r31 = CStruct_ctor(CStruct_new(8));
    sprintf(&sp8[0], (s32)lbl_802B016C, (s8)*(u8 *)temp_r30 + 2, temp_r30 + 1, temp_r30 + 0x11);
    AddString(temp_r31, QB_TEXT, &sp8[0]);
    Script_RunScript(QB_CREATE_CONSOLE_MESSAGE, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
