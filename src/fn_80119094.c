// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119094-0x801192A0 (524B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE48;
extern s32 lbl_802FFE54;
extern bool lbl_802FFE58;
extern bool lbl_802FFE68;
extern s32 lbl_802FFE6C[];
extern char lbl_8029D400[];
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8001473C(void *);
void fn_80014770(void);
bool ScriptSetConfig(CStruct *pParams, CScript *pScript) {
    s32 frame_rate;
    s32 sp8;
    u32 langKey;

    sp8 = 0;
    GetChecksum_2(pParams, QB_LANGUAGE, &sp8, 0);
    langKey = (u32)sp8;
    switch (langKey) {
    case QB_ENGLISH:
        lbl_802FFE48 = 2;
        break;
    case QB_FRENCH:
        lbl_802FFE48 = 3;
        break;
    case QB_SPANISH:
        lbl_802FFE48 = 3;
        break;
    case QB_ITALIAN:
    case QB_GERMAN:
        lbl_802FFE48 = 5;
        break;
    }
    if (ContainsFlag(pParams, QB_CD) != 0) {
        if (lbl_802FFE58 == 0) {
            fn_8001473C(&lbl_8029D400);
        }
        lbl_802FFE58 = 1;
    }
    if (ContainsFlag(pParams, QB_NOTCD) != 0) {
        if (lbl_802FFE58 != 0) {
            fn_80014770();
        }
        lbl_802FFE58 = 0;
    }
    if (ContainsFlag(pParams, QB_GOTEXTRAMEMORY) != 0) {
        lbl_802FFE54 = 1;
    }
    if (ContainsFlag(pParams, QB_NOEXTRAMEMORY) != 0) {
        lbl_802FFE54 = 0;
    }
    if (ContainsFlag(pParams, QB_PAL) != 0) {
        lbl_802FFE68 = 0;
    }
    if (ContainsFlag(pParams, QB_NTSC) != 0) {
        lbl_802FFE68 = 1;
    }
    frame_rate = 60;
    if (GetInteger(pParams, QB_FRAMERATE, &frame_rate, 0) != 0) {
        *(s32 *)&lbl_802FFE6C = frame_rate;
    }
    return true;
}