// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023F5E0-0x8023F6D0 (240B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Script_RunScript(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
s32 fn_8023897C(void * arg0, s32 arg1, s32 *arg2);
void CStruct_ctor(s32 arg0);
void AddString(CStruct * arg0, s32 arg1, void * arg2);
void CStruct_delete(CStruct * arg0, s32 arg1);
void fn_8023F5E0(CStruct *arg0) {
    volatile s32 sp8;
    s32 var_r30;
    Unk_056BA7B1 *temp_r31;
    Unk_FEC0E135 *list;

    var_r30 = 0;
    Script_RunScript(QB_PARKED_MAKE_PIECE_MENU, NULL, 0, 0, 0);
    Script_RunScript(QB_PARKED_MAKE_SET_MENU, NULL, 0, 0, 0);
    list = *(s32 **)arg0;
    goto check;
    do {
        temp_r31 = fn_8023897C(*(s32 *)arg0, var_r30, 0);
        if (temp_r31->unk0x150 != 0) {
            CStruct_ctor((s32)&sp8);
            AddString((s32)&sp8, QB_SET_NAME, temp_r31->unk0x4);
            Script_RunScript(QB_PARKED_MAKE_SET_MENU_ITEM, &sp8, 0, 0, 0);
            CStruct_delete((s32)&sp8, 2);
        }
        list = *(s32 **)arg0;
        var_r30++;
check: ;
    } while (var_r30 < list->unk0x13C90);
    arg0->unk0x4 = 0;
}
