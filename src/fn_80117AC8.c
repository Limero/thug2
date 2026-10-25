// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117AC8-0x80117BF0 (296B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_8029D1C4[];
extern char lbl_8029D2B4[];

u32 strlen(const char *);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
s32 sprintf(char *, const char *, ...);
u32 GetString(CStruct *, s32, void *, s32);
u32 GetInteger(CStruct *, s32, s32 *, s32);
u32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void AddString(CStruct *, s32, void *);

bool ScriptAppendSuffix(CStruct *arg0, Unk_FFAD6788 *arg1) {
    char sp8[0x68];
    char sp70[0x18];
    char *sp88;
    s32 sp8C;
    s32 sp90;
    s32 sp94;
    s32 len;
    s32 suffixLen;

    sp88 = lbl_8029D1C4;
    GetString(arg0, QB_TEXT, &sp88, 0);
    len = strlen(sp88);
    strcpy(sp8, sp88);
    sp8C = 0xF;
    GetInteger(arg0, QB_MAXCHARS, &sp8C, 0);
    sp90 = 1;
    GetInteger(arg0, QB_SUFFIX, &sp90, 0);
    sprintf(sp70, lbl_8029D2B4, sp90);
    suffixLen = strlen(sp70);
    if (len + suffixLen > sp8C) {
        sp8[sp8C - suffixLen] = 0;
    }
    strcat(sp8, sp70);
    sp94 = 0;
    GetChecksum_2(arg0, QB_NEWTEXTNAME, &sp94, 0);
    AddString(*(CStruct **)((char *)arg1 + 0x18), sp94, sp8);
    return true;
}
