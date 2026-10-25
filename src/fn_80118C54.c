// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118C54-0x80118CF4 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8000F2F8(Unk_9F352E7C *, s32);
s32 fn_8000F320(Unk_F12C5E01 *);
s32 fn_80054B24(s32, s32);
s32 GetText(CStruct *, s32, s32 *, s32);
extern char lbl_802FFE98[];
typedef struct { char pad0x0[0x178]; s32 unk0x178; } Unk_Scene;
bool ScriptAddScene(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    Unk_Scene *temp_r3;
    sp8 = 0;
    spC = 0;
    GetText(pParams, QB_SCENE, &sp8, 0);
    GetText(pParams, QB_ADD, &spC, 0);
    if ((sp8 != 0) && (spC != 0)) {
        temp_r3 = *(Unk_Scene **)&lbl_802FFE98;
        fn_8000F2F8((Unk_9F352E7C *)temp_r3, temp_r3->unk0x178);
        fn_80054B24(sp8, spC);
        fn_8000F320(*(Unk_F12C5E01 **)&lbl_802FFE98);
    }
    return true;
}
