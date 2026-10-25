// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019C4E0-0x8019C600 (288B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern char lbl_802AAC3C[];
extern char lbl_802AAC48[];
extern char lbl_802AAC58[];
extern char lbl_802AAC68[];
s32 fn_801745B4(s32);
s32 fn_80128294(CStruct *, void *, void *, s32);
s32 GetStructure_3(CStruct *, void *, void *, s32);
s32 fn_80128610(CStruct *, void *, void *, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void fn_80126E28(Unk_5AA7B5D7 *, Unk_5AA7B5D7 *);
struct cat_arr { char _pad[0x194]; s32 *_arr[4]; };
bool ScriptSetCreateATrickParams(CStruct *pParams, CScript *pScript) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    Unk_EE1FD121 *temp_r30;
    register s32 *entry __asm__("r9");
    register s32 idx __asm__("r0");
    register s32 *_arrbase __asm__("r11");

    if ((temp_r30 = fn_801745B4(lbl_80305EAC)) != 0) {
        fn_80128294(pParams, (s32)lbl_802AAC3C, &sp8, 1);
        if (temp_r30->unk0x198 != 0) {
            if (GetStructure_3(pParams, (s32)lbl_802AAC48, &spC, 1) != 0) {
                idx = sp8;
                _arrbase = ((struct cat_arr *)temp_r30)->_arr;
                entry = _arrbase[idx];
                fn_80126FF4(*(s32 *)((char *)entry), spC);
            }
            if (fn_80128610(pParams, (s32)lbl_802AAC58, &sp10, 1) != 0) {
                idx = sp8;
                _arrbase = ((struct cat_arr *)temp_r30)->_arr;
                entry = _arrbase[idx];
                fn_80126E28(((CStruct *)entry)->unk0x4, sp10);
            }
            if (fn_80128610(pParams, (s32)lbl_802AAC68, &sp14, 1) != 0) {
                idx = sp8;
                _arrbase = ((struct cat_arr *)temp_r30)->_arr;
                entry = _arrbase[idx];
                fn_80126E28(((CStruct *)entry)->unk0x8, sp14);
            }
            return true;
        }
    }
    return false;
}
