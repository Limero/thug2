// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801511AC-0x80151228 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8001075C(s32);
void fn_80010760(void);
void fn_800F1034(void);
s32 GetText(CStruct *, void *, void *, s32);
void fn_80131234(void);
void fn_8016A67C(s32, s32);
void strcpy(s32, s32);
extern u8 lbl_802A7D18[];
extern u8 lbl_803A0010[];
// ScriptLoadNodeArray @ 0x801511AC
bool ScriptLoadNodeArray(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_8001075C(lbl_802A7D18);
    fn_80131234();
    sp8 = 0;
    GetText(pParams, 0, &sp8, 0);
    strcpy((s32)lbl_803A0010, sp8);
    fn_8016A67C(sp8, 0);
    fn_800F1034();
    fn_80010760();
    return true;
}
