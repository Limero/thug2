// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185F9C-0x801860B8 (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Script_RunScript(void *, void *, void *, void *, void *);
void CStruct_dtor(s32 arg0);
s32 fn_80184170(Unk_C8FEE62D *arg0, s32 arg1);
extern char lbl_80305F9C[];
s32 ScriptInMultiplayerGame(s32 arg0, s32 arg1);
s32 fn_8009CF2C(CStruct *arg0);
s32 fn_80184168(void *arg0);
s32 fn_8018B4C0(void *arg0, s32 *arg1, s32 *arg2);
typedef struct { s16 unk0x0; s16 pad; s32 (*unk0x4)(void *); } Ent;
typedef struct { char pad[0x14]; Ent *vt; } Obj;
void fn_80185F9C(Unk_C8FEE62D *arg0) {
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    Obj *o;

    temp_r30 = *(s32 *)&lbl_80305F9C;
    sp8 = 0;
    while (sp8 < fn_80184168(arg0)) {
        o = (Obj *)fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
        if (o->vt[0x1E].unk0x4((char *)o + o->vt[0x1E].unk0x0) != 0) {
            if (fn_8009CF2C((CStruct *)temp_r30) == 0) {
                arg0->unk0x4C = arg0->unk0x4C - 1;
                arg0->unk0x44 = arg0->unk0x44 - 1;
                arg0->unk0x48 = arg0->unk0x48 - 1;
            }
        }
        sp8 += 1;
    }
    if (fn_8009CF2C((CStruct *)temp_r30) == 0) {
        CStruct_dtor(arg0->unk0x1C);
    }
    if ((fn_80184170(arg0, 0) == 0) && (ScriptInMultiplayerGame(0, 0) == 0)) {
        Script_RunScript(QB_GOALMANAGER_SHOWGOALPOINTS, 0, 0, 0, 0);
    }
}
