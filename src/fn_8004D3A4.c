// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004D3A4-0x8004D4CC (296B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
extern char lbl_80300434[];
extern char lbl_80292948[];
extern char lbl_80292950[];
void GetElement(s32 *, s32, void *, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80128A90(CStruct *, void *);
void CObject_RemoveRefLink(s32, void *);
s32 fn_8003FFC4(Unk_31DE137E *);

typedef struct ScreenElementHandle {
    s32 element;
    s32 word4;
    s32 word8;
    s32 wordC;
    s32 word10;
    s32 word14;
} ScreenElementHandle;

s32 ScriptMenuSelectedIndexIs(CStruct *pParams, CScript *pScript) {
    ScreenElementHandle h8;
    s32 *h;
    Unk_31DE137E *rec;
    s32 sel;
    s32 result;

    GetElement(&h8.element, *(s32 *)lbl_80300434, pParams, QB_ID, 1);
    rec = (Unk_31DE137E *)h8.element;
    h = &h8.element;
    sel = rec->unk0x190;
    if (sel == -1) {
        if (h8.element != 0) {
            CObject_RemoveRefLink(h8.element, h);
            h8.element = 0;
        }
        return 0;
    }
    result = 0;
    if (GetInteger(pParams, 0, &h8.word10, 0) != 0) {
        result = (h8.word10 == sel);
    } else if (fn_80128A90(pParams, (s32)lbl_80292948) != 0) {
        result = (sel == 0);
    } else if (fn_80128A90(pParams, (s32)lbl_80292950) != 0) {
        result = (sel == (fn_8003FFC4(rec) - 1));
    }
    if (h8.element != 0) {
        CObject_RemoveRefLink(h8.element, h);
        h8.element = 0;
    }
    return result;
}
