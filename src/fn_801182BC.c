// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801182BC-0x80118334 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_802FFE98[];

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8000F68C(void *, s32);
char *fn_8000F36C(void *, s32);
char *strcpy(char *, const char *);

bool ScriptPrintMemInfo(CStruct *pParams, CScript *pScript) {
    char buf[0x40];
    s32 sp48 = 0xC7800B0;
    void *mgr = *(void **)lbl_802FFE98;

    if (pParams != NULL) {
        GetChecksum_2(pParams, 0, &sp48, 0);
    }
    fn_8000F68C(mgr, sp48);
    strcpy(buf, fn_8000F36C(mgr, sp48));
    return true;
}
