// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80163958-0x801639A4 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A8368[];
extern char lbl_80305DF8[];
s32 GetString(CStruct *, s32 *, s32 *, s32);
extern void strcpy(char *, const char *);
bool ScriptSetParkName(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = (s32)lbl_802A8368;
    GetString(pParams, 0, &sp8, 0);
    strcpy((char *)lbl_80305DF8, (char *)sp8);
    return false;
}
