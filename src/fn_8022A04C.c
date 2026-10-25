// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022A04C-0x8022A21C (464B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 NextItem(s32);
extern s32 fn_8022986C(CScript *);
extern s32 fn_8022989C(CScript *);
extern s32 fn_801258E8(void *, s32);
extern void AddComponent(CStruct *, s32, s32, void *);
extern void AddInteger(CStruct *, s32, s32);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
extern char lbl_80305F9C[];
extern char lbl_802B02A4[];

void fn_8022A04C(CScript *arg0, s32 arg1) {
    s32 sp8[16];
    s32 temp_r29;
    s32 temp_r30;
    Unk_C7387A53 *temp_r31;
    s32 h2;

    temp_r30 = *(s32 *)&lbl_80305F9C;
    sprintf(&sp8, (s32)lbl_802B02A4, arg1 + 1);
    temp_r29 = CStruct_ctor(CStruct_new(8));
    temp_r31 = NextItem(temp_r30);
    if (fn_8022986C(arg0) != 0) {
        AddComponent(temp_r29, QB_STRING0, 3, fn_801258E8(&sp8, 0));
        Script_RunScript(QB_TOOK_FLAG_YOU, temp_r29, 0, 0, 0);
    } else if ((fn_8022989C(temp_r31) == 0) && (arg1 == temp_r31->unk0x34)) {
        AddInteger((h2 = CStruct_ctor(CStruct_new(8))), QB_TEAM, temp_r31->unk0x34);
        Script_RunScript(QB_SHOW_CTF_ARROW, h2, 0, 0, 0);
        if (h2 != 0) {
            CStruct_delete(h2, 3);
        }
        AddComponent(temp_r29, QB_STRING0, 3, (char *)arg0 + 0x3C);
        Script_RunScript(QB_TOOK_FLAG_YOURS, temp_r29, 0, 0, 0);
    } else {
        AddComponent(temp_r29, QB_STRING0, 3, (char *)arg0 + 0x3C);
        AddComponent(temp_r29, QB_STRING1, 3, fn_801258E8(&sp8, 0));
        Script_RunScript(QB_TOOK_FLAG_OTHER, temp_r29, 0, 0, 0);
    }
    if (temp_r29 != 0) {
        CStruct_delete(temp_r29, 3);
    }
    arg0->unk0x1D8 = (s32) (arg0->unk0x1D8 | (0x800 << arg1));
}
