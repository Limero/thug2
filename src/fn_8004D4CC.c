// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004D4CC-0x8004D530 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "structs.h"
#include "qb_constants.h"
extern char lbl_80300434[];
void GetElement(s32 *, s32, void *, s32, s32);
void CObject_RemoveRefLink(s32, void *);
bool ScriptScreenElementExists(CStruct *pParams, CScript *pScript) { // 0x8004D4CC
    struct { s32 a; s32 b; s32 c; s32 d; } sp8;
    s32 *h;

    GetElement(&sp8.a, *(s32 *)lbl_80300434, pParams, QB_ID, 0);
    if (sp8.a == 0) {
        return false;
    }
    h = &sp8.a;
    CObject_RemoveRefLink(sp8.a, h);
    sp8.a = 0;
    return true;
}
