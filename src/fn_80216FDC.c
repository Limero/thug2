// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80216FDC-0x80217234 (600B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800168B0(void *);
void fn_800168B8(void);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
bool ScriptObjectExists(s32, s32);
void CStruct_dtor(CStruct *);
void Script_RunScript(s32, s32, s32, s32, s32);
s32 fn_800145AC(void);
void CStruct_delete(CStruct *, s32);
extern u32 lbl_80305FA4;

void fn_80216FDC(void) {
    u8 sp8[0x100];
    s32 v;
    s32 var_r31;

    if (fn_800168B0(sp8) > 0) {
        v = (s8)sp8[0];
        if ((v == 25) || (v == 32)) {
            var_r31 = CStruct_ctor(CStruct_new(8));
            AddChecksum(var_r31, QB_ID, QB_KEYBOARD_ANCHOR);
            if (ScriptObjectExists(var_r31, 0) == 0) {
                CStruct_dtor(var_r31);
                AddChecksum(var_r31, QB_ID, QB_CURRENT_MENU_ANCHOR);
                if (ScriptObjectExists(var_r31, 0) == 0) {
                    CStruct_dtor(var_r31);
                    AddChecksum(var_r31, QB_ID, QB_DIALOG_BOX_ANCHOR);
                    if (ScriptObjectExists(var_r31, 0) == 0) {
                        Script_RunScript(QB_ENTER_KB_CHAT, 0, 0, 0, 0);
                        fn_800168B8();
                    }
                }
            }
        } else if (v == 27) {
            if ((u32)(fn_800145AC() - lbl_80305FA4) > 0x7D0U) {
                var_r31 = CStruct_ctor(CStruct_new(8));
                AddChecksum(var_r31, QB_STRING_ID, QB_PROPS_STRING);
                Script_RunScript(QB_SENDTAUNTMESSAGE, var_r31, 0, 0, 0);
                if (var_r31 != 0) {
                    CStruct_delete(var_r31, 3);
                }
                lbl_80305FA4 = fn_800145AC();
            }
        } else if (v == 28) {
            if ((u32)(fn_800145AC() - lbl_80305FA4) > 0x7D0U) {
                var_r31 = CStruct_ctor(CStruct_new(8));
                AddChecksum(var_r31, QB_STRING_ID, QB_YOUR_DADDY_STRING);
                Script_RunScript(QB_SENDTAUNTMESSAGE, var_r31, 0, 0, 0);
                if (var_r31 != 0) {
                    CStruct_delete(var_r31, 3);
                }
                lbl_80305FA4 = fn_800145AC();
            }
        } else if (v == 29) {
            if ((u32)(fn_800145AC() - lbl_80305FA4) > 0x7D0U) {
                var_r31 = CStruct_ctor(CStruct_new(8));
                AddChecksum(var_r31, QB_STRING_ID, QB_GET_SOME_STRING);
                Script_RunScript(QB_SENDTAUNTMESSAGE, var_r31, 0, 0, 0);
                if (var_r31 != 0) {
                    CStruct_delete(var_r31, 3);
                }
                lbl_80305FA4 = fn_800145AC();
            }
        } else if (v == 30) {
            if ((u32)(fn_800145AC() - lbl_80305FA4) > 0x7D0U) {
                var_r31 = CStruct_ctor(CStruct_new(8));
                AddChecksum(var_r31, QB_STRING_ID, QB_NO_WAY_STRING);
                Script_RunScript(QB_SENDTAUNTMESSAGE, var_r31, 0, 0, 0);
                if (var_r31 != 0) {
                    CStruct_delete(var_r31, 3);
                }
                lbl_80305FA4 = fn_800145AC();
            }
        }
    }
}
