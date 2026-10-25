// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C5AA0-0x801C5C0C (364B). Byte-identical.
#include "types.h"
extern char lbl_80305EAC[];
extern char lbl_80305F9C[];
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
s32 CStruct_ctor(void *);
void CStruct_dtor(CStruct *);
void CStruct_delete(CStruct *, s32);
s32 fn_8014510C(Unk_EE36B018 *);
void AddComponent(CStruct *, s32, s32, void *);
void Script_RunScript(s32, void *, void *, s32, s32);
s32 fn_8017471C(void *, s32);
s32 fn_8021F6CC(Unk_2EC243AC *);

s32 fn_801C5AA0(void *arg0) {
    CStruct *entry;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r3;

    entry = *(s32 **)arg0;
    temp_r3 = fn_8021F6CC(*(s32 *)&lbl_80305F9C);
    if (*(u8 *)entry != temp_r3) {
        return 4;
    }
    arg0 = *((void * *)&((CScript *)arg0)->unk0x18);
    temp_r28 = fn_8017471C(*(s32 *)&lbl_80305EAC, entry->unk0x4);
    if (temp_r28 == 0) {
        return 1;
    }
    temp_r29 = fn_8017471C(*(s32 *)&lbl_80305EAC, entry->unk0x8);
    if (temp_r29 == 0) {
        return 1;
    }
    if (((CScript *)arg0)->unk0x18 == entry->unk0x4) {
        entry = (s32 *)CStruct_ctor((void *)CStruct_new(8));
        CStruct_dtor(entry);
        AddComponent((s32)entry, QB_STRING0, 3, fn_8014510C(temp_r29));
        Script_RunScript(0xB3FF911, entry, arg0, 0, 0);
        if (entry != NULL) {
            CStruct_delete(entry, 3);
        }
    } else if (((CScript *)arg0)->unk0x18 == entry->unk0x8) {
        entry = (s32 *)CStruct_ctor((void *)CStruct_new(8));
        CStruct_dtor(entry);
        AddComponent((s32)entry, QB_STRING0, 3, fn_8014510C(temp_r28));
        Script_RunScript(QB_GRAFFITISTEALOTHER, entry, arg0, 0, 0);
        if (entry != NULL) {
            CStruct_delete(entry, 3);
        }
    }
    return 1;
}
