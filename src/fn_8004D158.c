// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004D158-0x8004D234 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80300434[];
void GetElement(s32 *, s32, void *, s32, s32);
void CObject_RemoveRefLink(s32, void *);
s32 fn_80044614(Unk_31DE137E *, void *, s32);
void AddString(CStruct *, s32, s32);

bool ScriptGetTextElementString(CStruct *pParams, CScript *pScript) { // 0x8004D158
    struct { s32 a; s32 b; s32 c; s32 d; } sp8;
    char sp18[0x200];
    s32 *h;
    Unk_31DE137E *rec;
    s32 type;
    s32 temp_r3;

    GetElement(&sp8.a, *(s32 *)lbl_80300434, pParams, QB_ID, 1);
    rec = (Unk_31DE137E *)sp8.a;
    type = rec->unk0x1C;
    if (type == QB_TEXTBLOCKELEMENT) goto L_arm1;
    if (type != QB_TEXTELEMENT) goto L_cleanup;
    if (rec->unk0x190 != 0) {
        AddString(pScript->unk0x18, QB_STRING, rec->unk0x190);
    }
    goto L_cleanup;
L_arm1:
    if (fn_80044614(rec, sp18, 0x200) != 0) {
        AddString(pScript->unk0x18, QB_STRING, sp18);
    }
L_cleanup:
    temp_r3 = sp8.a;
    h = &sp8.a;
    if (temp_r3 != 0) {
        CObject_RemoveRefLink(temp_r3, h);
        sp8.a = 0;
    }
    return false;
}
