// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019C298-0x8019C348 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern char lbl_802AAC3C[];
extern char lbl_802AAC48[];
extern char lbl_802AAC58[];
extern char lbl_802AAC68[];
s32 fn_801745B4(s32);
s32 fn_80128294(CStruct *, void *, void *, s32);
s32 fn_80127C90(CStruct *, void *, CStruct *);
void fn_80127B28(CStruct *, void *, Unk_5AA7B5D7 *);
struct cat_arr { char _pad[0x194]; s32 *_arr[4]; };
bool ScriptGetCreateATrickParams(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;
    register s32 *entry __asm__("r30");
    register s32 idx __asm__("r0");
    register s32 *_arrbase __asm__("r9");

    if ((temp_r29 = fn_801745B4(lbl_80305EAC)) != 0) {
        fn_80128294(pParams, (s32)lbl_802AAC3C, &sp8, 1);
        idx = sp8;
        _arrbase = ((struct cat_arr *)temp_r29)->_arr;
        entry = _arrbase[idx];
        fn_80127C90(pScript->unk0x18, (s32)lbl_802AAC48, *(s32 *)((char *)entry));
        fn_80127B28(pScript->unk0x18, (s32)lbl_802AAC58, ((CStruct *)entry)->unk0x4);
        fn_80127B28(pScript->unk0x18, (s32)lbl_802AAC68, ((CStruct *)entry)->unk0x8);
        return true;
    }
    return false;
}
