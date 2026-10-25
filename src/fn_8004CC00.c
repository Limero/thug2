// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004CC00-0x8004CC88 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
extern char lbl_80300434[];
void GetElement(s32 *, s32, void *, s32, s32);
void CObject_RemoveRefLink(s32, void *);
typedef struct Rec_4CC00 {
    char pad[0x10];
    s16 unk0x10;
    s32 fn;
} Rec_4CC00;
bool ScriptSetScreenElementProps(CStruct *pParams, CScript *pScript) {
    struct { s32 a; s32 b; s32 c; s32 d; } sp8;
    s32 *h;
    Rec_4CC00 *rec;

    GetElement(&sp8.a, *(s32 *)lbl_80300434, pParams, QB_ID, 1);
    rec = *(Rec_4CC00 **)((char *)sp8.a + 8);
    ((void (*)(void *, void *))rec->fn)((char *)sp8.a + rec->unk0x10, pParams);
    h = &sp8.a;
    if (sp8.a != 0) {
        CObject_RemoveRefLink(sp8.a, h);
        sp8.a = 0;
    }
    return true;
}
