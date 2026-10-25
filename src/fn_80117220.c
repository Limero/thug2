// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117220-0x80117284 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void GetString(CStruct *, s32, void *, s32);
void strcpy(void *, void *);
void UpperCase(char *);
void AddString(CStruct *, s32, void *);

bool ScriptGetUpperCaseString(CStruct *arg0, Unk_FFAD6788 *arg1) {
    char buf[0x80];
    void *sp88;

    GetString(arg0, 0, &sp88, 1);
    strcpy(buf, sp88);
    UpperCase(buf);
    AddString(*(CStruct **)((char *)arg1 + 0x18), 0xFE366B7B, buf);
    return true;
}
