// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004D314-0x8004D3A4 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
extern char lbl_80300434[];
void GetElement(s32 *, s32, void *, s32, s32);
void fn_80127A18(CStruct *, s32, f32, f32);
void CObject_RemoveRefLink(s32, void *);
void fn_8003F728(void *, f32 *, f32 *);
bool ScriptGetScreenElementPosition(CStruct *pParams, CScript *pScript) {
    struct { s32 a; s32 b; s32 c; s32 d; } sp8;
    f32 sp18;
    f32 sp1C;

    GetElement(&sp8.a, *(s32 *)lbl_80300434, pParams, QB_ID, 1);
    fn_8003F728(sp8.a, &sp18, &sp1C);
    fn_80127A18(pScript->unk0x18, QB_SCREENELEMENTPOS, sp18, sp1C);
    if (sp8.a != 0) {
        CObject_RemoveRefLink(sp8.a, &sp8.a);
        sp8.a = 0;
    }
    return true;
}
