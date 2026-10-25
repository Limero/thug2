// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015A788-0x8015A854 (204B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFE54;
extern void *lbl_802FFE98;
extern s32 lbl_80301B48;
extern void *lbl_80305EAC;
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 GetText(CStruct *, void *, void *, s32);
void fn_801A2A58(s32);
void fn_8000F2F8(Unk_9F352E7C *, s32);
s32 fn_800F29CC(Unk_C7387A53 *, s32, s32, Unk_C7387A53 *);
void fn_8000F320(Unk_F12C5E01 *);
s32 ScriptReloadSkaterCamAnim(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 ret;
    Unk_C7387A53 *cam;
    s32 movie;

    if (lbl_802FFE54 == 0) {
        return 0;
    }
    if (fn_80128E34(pParams, 0, &sp8, 0) == 0) {
        return 0;
    }
    if (GetText(pParams, 0, &spC, 0) == 0) {
        return 0;
    }
    fn_801A2A58(((Unk_40426380 *)lbl_80305EAC)->unk0x378);
    cam = lbl_802FFE98;
    movie = lbl_80301B48;
    fn_8000F2F8(cam, cam->unk0x178);
    ret = fn_800F29CC(movie, sp8, spC, 0);
    fn_8000F320(lbl_802FFE98);
    return ret;
}
