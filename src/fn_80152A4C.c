// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152A4C-0x80152B78 (300B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A7D78[];
extern char lbl_802A7D84[];
extern char lbl_802A7D90[];
extern s32 lbl_80305EAC;
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 GetStructure_2(CStruct *, void *, s32 *, void *);
s32 GetChecksum_4(CStruct *, void *, void *, void *);
s32 GetStructure_3(CStruct *, void *, void *, void *);
s32 Script_SpawnScript(Unk_15EF4A35 *, void *, void *, Unk_80577C09 *, void *, void *, void *, void *, void *, void *);
s32 fn_801745B4(s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
bool ScriptSpawnSkaterScript(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 temp_r28;
    s32 temp_r29;
    Unk_FFAD6788 *temp_r30;

    sp10 = 0;
    GetChecksum_2(arg0, 0, &sp10, 0);
    sp14 = 0;
    GetStructure_2(arg0, QB_PARAMS, &sp14, 0);
    sp18 = 0;
    GetChecksum_4(arg0, (s32)lbl_802A7D78, &sp18, 0);
    sp1C = 0;
    GetChecksum_4(arg0, (s32)lbl_802A7D84, &sp1C, 0);
    sp20 = 0;
    GetStructure_3(arg0, (s32)lbl_802A7D90, &sp20, 0);
    temp_r30 = (void *)Script_SpawnScript(sp10, sp14, sp1C, sp20, arg1->unk0xB8, sp18, 0, 0, 0, 0);
    temp_r28 = (s32)((char *)temp_r30 + 0xBC);
    temp_r29 = fn_801745B4(lbl_80305EAC);
    if (temp_r30->unk0xBC != 0) {
        CObject_RemoveRefLink(temp_r30->unk0xBC, (void *)temp_r28);
        temp_r30->unk0xBC = 0;
    }
    temp_r30->unk0xBC = temp_r29;
    if (temp_r29 != 0) {
        CObject_AddRefLink((void *)temp_r29, (void *)temp_r28);
    }
    return true;
}
