// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004D098-0x8004D158 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80300434[];
void GetElement(s32 *, s32, void *, s32, s32);
void CObject_RemoveRefLink(s32, void *);
s32 fn_800448D0(Unk_31DE137E *);
s32 fn_80042D44(Unk_31DE137E *);

s32 ScriptTextElementBackspace(CStruct *pParams, CScript *pScript) { // 0x8004D098
    // NOTE: pScript is unused (never read — no r4 save/use in the prologue/body),
    // but the handler takes two args per the Front::ScriptTextElementBackspace
    // (CStruct*, CScript*) symbol and the Get* sibling convention (fn_8004D158).
    struct { s32 a; s32 b; s32 c; s32 d; } sp8;
    s32 *h;
    Unk_31DE137E *rec;
    s32 type;
    s32 temp_r3;

    GetElement(&sp8.a, *(s32 *)lbl_80300434, pParams, QB_ID, 1);
    rec = (Unk_31DE137E *)sp8.a;
    h = &sp8.a;
    type = rec->unk0x1C;
    switch (type) {
    case QB_TEXTBLOCKELEMENT:
        goto L_arm1;
    case QB_TEXTELEMENT:
        break;
    default:
        goto L_else;
    }
    temp_r3 = fn_80042D44(rec);
    goto L_merge;
L_arm1:
    temp_r3 = fn_800448D0(rec);
L_merge:
    if (sp8.a != 0) {
        CObject_RemoveRefLink(sp8.a, h);
        sp8.a = 0;
    }
    return temp_r3;
L_else:
    if (sp8.a != 0) {
        CObject_RemoveRefLink(sp8.a, h);
        sp8.a = 0;
    }
    return 0;
}
