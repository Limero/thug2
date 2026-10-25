// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015332C-0x8015339C (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern s32 lbl_80305F9C;
extern s32 lbl_80305EAC;
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8017D060(CScript *);
s32 fn_80219680(CStruct *);
void fn_80219668(CStruct *);
void fn_8000F320(Unk_F12C5E01 *);
bool ScriptStartServer(CStruct *pParams, CScript *pScript) {
    Unk_9994C3F5 *temp_r3;
    s32 temp_r31;
    s32 temp_r30;

    temp_r3 = *(void **)&lbl_802FFE98;
    temp_r30 = lbl_80305EAC;
    temp_r31 = lbl_80305F9C;
    fn_8000F2F8((s32)temp_r3, temp_r3->unk0x11C);
    fn_8017D060(temp_r30);
    if (fn_80219680(temp_r31) == 0) {
        fn_80219668(temp_r31);
    }
    fn_8000F320(*(void **)&lbl_802FFE98);
    return true;
}
