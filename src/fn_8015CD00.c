// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015CD00-0x8015CD84 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_8019BD3C(CStruct *, CStruct *, s32);
s32 fn_800093A4(Unk_9994C3F5 *);
void AddString(CStruct *, s32, void *);
void fn_800092B0(Unk_9994C3F5 *, s32);
typedef struct { char _0[0x374]; s32 fld; } G_t;
bool ScriptGetHorseString(CStruct *pParams, CScript *pScript) {
    s32 sp8[4];
    s32 sp18;
    s32 temp_r30;
    register G_t *g __asm__("r11");

    fn_80128E34(pParams, QB_WHICHSTRING, &sp18, 1);
    g = (G_t *)lbl_80305EAC;
    fn_8019BD3C(&sp8[0], g->fld, sp18);
    temp_r30 = pScript->unk0x18;
    AddString(temp_r30, QB_TEXT, fn_800093A4(&sp8[0]));
    fn_800092B0(&sp8[0], 2);
    return true;
}
