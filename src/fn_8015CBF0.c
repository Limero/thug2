// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015CBF0-0x8015CD00 (272B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_8019BD3C(CStruct *, CStruct *, s32);
s32 fn_8019B834(Unk_9994C3F5 *);
s32 fn_8017471C(s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_80126F88(Unk_80577C09 *, CStruct *);
s32 fn_800093A4(Unk_9994C3F5 *);
void AddString(CStruct *, s32, void *);
void AddChecksum(CStruct *, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_800092B0(Unk_9994C3F5 *, s32);
typedef struct { char _0[0x374]; s32 fld; } G_t;
bool ScriptApplyToHorsePanelString(CStruct *pParams, CScript *pScript) {
    s32 sp8[4];
    s32 sp18;
    s32 sp1C;
    s32 temp_r30;
    s32 temp_r28;
    G_t *g2;

    fn_80128E34(pParams, QB_WHICHSTRING, &sp18, 1);
    fn_80128E34(pParams, QB_ID, &sp1C, 1);
    fn_8019BD3C(&sp8[0], (*(G_t **)&lbl_80305EAC)->fld, sp18);
    g2 = *(G_t **)&lbl_80305EAC;
    temp_r30 = fn_8017471C((s32)g2, fn_8019B834(g2->fld));
    temp_r28 = CStruct_ctor(CStruct_new(8));
    fn_80126F88(temp_r28, pParams);
    AddString(temp_r28, QB_TEXT, fn_800093A4(&sp8[0]));
    AddChecksum(temp_r28, QB_ID, sp1C);
    Script_RunScript(QB_CREATE_HORSE_PANEL_MESSAGE, temp_r28, temp_r30, 0, 0);
    if (temp_r28 != 0) {
        CStruct_delete(temp_r28, 3);
    }
    fn_800092B0(&sp8[0], 2);
    return true;
}
