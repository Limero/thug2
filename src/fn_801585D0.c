// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801585D0-0x80158668 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];

s32 fn_80174A58(void * a, CStruct * b);
s32 fn_80128E04(CStruct * arg0, void * hash, void *out, s32 defval);
s32 fn_8003A944(s32 a, CStruct * b, s32 c);
void fn_80126FF4(Unk_80577C09 * a, CStruct * b);
void fn_801A57A0(s32 a, s32 b);

bool ScriptSetNeversoftSkater(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 prof;

    prof = fn_80174A58(*(s32 *)&lbl_80305EAC, pParams);
    fn_80128E04(pParams, QB_APPEARANCE, &sp8, 1);
    fn_8003A944(prof + 4, sp8, 1);
    fn_80128E04(pParams, QB_INFO, &spC, 1);
    fn_80126FF4(prof + 0x6C, spC);
    fn_801A57A0(prof, 1);
    return true;
}
