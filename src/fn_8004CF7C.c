// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004CF7C-0x8004D098 (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80300434[];
void GetElement(s32 *, s32, void *, s32, s32);
void CObject_RemoveRefLink(s32, void *);
s32 GetString(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_80044D98(Unk_31DE137E *, s32, s32, s32);
s32 fn_80042C9C(Unk_31DE137E *, s32);

s32 ScriptTextElementConcatenate(CStruct *pParams, CScript *pScript) { // 0x8004CF7C
    struct { s32 a; s32 b; s32 c; s32 d; } sp8;
    s32 sp18;
    s32 *h;
    Unk_31DE137E *rec;
    s32 type;
    s32 var_r30;

    GetElement(&sp8.a, *(s32 *)lbl_80300434, pParams, QB_ID, 1);
    h = &sp8.a;
    GetString(pParams, 0, &sp18, 1);
    rec = (Unk_31DE137E *)sp8.a;
    type = rec->unk0x1C;
    if (type == QB_TEXTBLOCKELEMENT) {
        var_r30 = fn_80044D98(rec, sp18, ContainsFlag(pParams, QB_ENFORCE_MAX_WIDTH), ContainsFlag(pParams, QB_LAST_LINE));
        goto L_merge;
    }
    if (type != QB_TEXTELEMENT) goto L_else;
    var_r30 = fn_80042C9C(rec, sp18);
L_merge:
    if (sp8.a != 0) {
        CObject_RemoveRefLink(sp8.a, h);
        sp8.a = 0;
    }
    return var_r30;
L_else:
    if (rec != NULL) {
        CObject_RemoveRefLink(rec, h);
        sp8.a = 0;
    }
    return 0;
}
