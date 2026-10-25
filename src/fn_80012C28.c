// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012C28-0x80012D18 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE98;
void fn_8000F2F8(Unk_9994C3F5 *, s32);
void fn_8000F320(Unk_9994C3F5 *);
void Pip_LoadPre(s32);
void GetString(CStruct *, s32 *, s32 *, s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
bool ScriptLoadPipPre(CStruct *arg0) {
    u32 swv1;
    s32 spC;
    s32 sp8;

    GetString(arg0, 0, &sp8, 1);
    spC = 0;
    GetChecksum_2(arg0, QB_HEAP, &spC, 0);
    switch (swv1 = spC) {
    case 0x0:
        spC = 0;
        break;
    case QB_TOPDOWN:
        fn_8000F2F8((void *)lbl_802FFE98, ((Unk_9994C3F5 *)lbl_802FFE98)->unk0x118);
        break;
    case QB_BOTTOMUP:
        fn_8000F2F8((void *)lbl_802FFE98, ((Unk_9994C3F5 *)lbl_802FFE98)->unk0x11C);
        break;
    default:
        spC = 0;
        break;
    }
    Pip_LoadPre(sp8);
    if (spC != 0) {
        fn_8000F320((void *)lbl_802FFE98);
    }
    return true;
}
