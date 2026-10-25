// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EF80C-0x800EF9C0 (436B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct LinkNode {
    CStruct *container;
    CStruct *prev;
    CStruct *next;
} LinkNode;
typedef struct PlayStreamScript {
    char pad0x0[0xBC];
    LinkNode link;
} PlayStreamScript;
s32 fn_8011E548(s32);
void fn_800EFB60(Unk_C7387A53 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(s32, s32, s32);
void AddInteger(s32, s32, s32);
s32 GetChecksum_3(s32, s32);
s32 fn_800CBDE0(void);
void fn_800EF9C0(Unk_C7387A53 *, s32, s32);
s32 fn_8011C820(s32, s32);
s32 fn_800F2AD8(s32, s32, s32);
PlayStreamScript *Script_SpawnScript(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void CStruct_delete(s32, s32);
void CObject_AddRefLink(CStruct *, LinkNode *);
void CObject_RemoveRefLink(CStruct *, LinkNode *);
extern s32 lbl_80301B48;
bool fn_800EF80C(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_2;
    CStruct *temp_r29;
    PlayStreamScript *temp_r3_3;
    LinkNode *temp_r28;

    if (fn_8011E548(arg1) == 0) {
        return false;
    }
    fn_800EFB60(arg0);
    temp_r31 = CStruct_ctor(CStruct_new(8));
    AddChecksum(temp_r31, QB_STREAM_CHECKSUM, arg1);
    if (arg3 != 0) {
        AddInteger(temp_r31, QB_VOL, arg3);
    }
    if (arg2 == 0) {
        AddInteger(temp_r31, QB_USE_POS_INFO, 0);
        GetChecksum_3(arg0->unk0xC, QB_ANIMBLENDER);
        temp_r3 = fn_800CBDE0();
        fn_800EF9C0(arg0, arg1, temp_r3);
        temp_r3_2 = fn_8011C820(arg1, arg4);
        AddChecksum(temp_r31, QB_STREAMID, temp_r3_2);
        arg0->unk0x20 = temp_r3_2;
        if (fn_800F2AD8(lbl_80301B48, arg1 + temp_r3, 0) != 0) {
            AddChecksum(temp_r31, 0, QB_PLAY_ANIM);
        }
    }
    temp_r3_3 = Script_SpawnScript(QB_FAM_PLAY_STREAM, temp_r31, 0, 0, 0, 0, 0, 0, 0, 0);
    temp_r29 = (CStruct *)arg0->unk0xC;
    temp_r28 = &temp_r3_3->link;
    if (temp_r3_3->link.container != NULL) {
        CObject_RemoveRefLink(temp_r3_3->link.container, temp_r28);
        temp_r3_3->link.container = NULL;
    }
    temp_r3_3->link.container = temp_r29;
    if (temp_r29 != NULL) {
        CObject_AddRefLink(temp_r29, temp_r28);
    }
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
