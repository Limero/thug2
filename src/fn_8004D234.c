// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004D234-0x8004D314 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
extern char lbl_80300434[];
typedef struct ScreenElementHandle {
    Unk_31DE137E *element;
    s32 word4;
    s32 word8;
} ScreenElementHandle;
void GetElement(void *, s32, void *, s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
s32 fn_80042AD8(Unk_31DE137E *);
s32 fn_800447B4(Unk_31DE137E *);
void AddInteger(CStruct *, s32, s32);
bool ScriptGetTextElementLength(CStruct *arg0, CScript *arg1) {
    ScreenElementHandle handle;
    s32 handle_pad;
    ScreenElementHandle *h;
    Unk_31DE137E *rec;
    s32 length;
    s32 type;
    register s32 script29 __asm__("r29");

    script29 = (s32)arg1;
    GetElement(&handle, *(s32 *)lbl_80300434, arg0, QB_ID, 1);
    length = 0;
    rec = handle.element;
    type = rec->unk0x1C;
    h = &handle;
    switch (type) {
    case QB_TEXTELEMENT:
        length = fn_80042AD8(rec);
        break;
    case QB_TEXTBLOCKELEMENT:
        length = fn_800447B4(rec);
        break;
    default:
        if (handle.element != 0) {
            CObject_RemoveRefLink(handle.element, (CStruct *)h);
            handle.element = 0;
        }
        return false;
    }
    AddInteger(((CScript *)script29)->unk0x18, QB_LENGTH, length);
    if (handle.element != 0) {
        CObject_RemoveRefLink(handle.element, (CStruct *)h);
        handle.element = 0;
    }
    return true;
}
