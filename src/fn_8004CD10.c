// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004CD10-0x8004CDAC (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "structs.h"
#include "qb_constants.h"
extern char lbl_80300434[];
void GetElement(s32 *, s32, void *, s32, s32);
void CObject_RemoveRefLink(s32, void *);
s32 ContainsFlag(CStruct *, s32);
void CScreenElement_SetChildLockState(s32, s32);
bool ScriptSetScreenElementLock(CStruct *pParams, CScript *pScript) { // 0x8004CD10
    struct { s32 a; s32 b; s32 c; s32 d; } sp8;
    s32 *h;

    GetElement(&sp8.a, *(s32 *)lbl_80300434, pParams, QB_ID, 1);
    if (ContainsFlag(pParams, QB_OFF) != 0) {
        CScreenElement_SetChildLockState(sp8.a, 0);
    } else {
        CScreenElement_SetChildLockState(sp8.a, 1);
    }
    h = &sp8.a;
    if (sp8.a != 0) {
        CObject_RemoveRefLink(sp8.a, h);
        sp8.a = 0;
    }
    return true;
}
