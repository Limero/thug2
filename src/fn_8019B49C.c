// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019B49C-0x8019B634 (408B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad0x0[0x8];
    s32 unk0x8;
    char pad0xC[4];
    s32 unk0x10;
    char pad0x14[0x10];
} GoalEntry;

s32 Game_GetGoalManager(void);
s32 fn_801868AC(s32);
void *CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_8003E7CC(s32);
void *fn_80128F94(void *);
void fn_80129068(void *, s32, s8);
void AddString(CStruct *, s32, void *);
void AddInteger(CStruct *, s32, s32);
void AddChecksum(CStruct *, s32, s32);
s32 fn_800093A4(void *);
s32 fn_8019A448(void *, s32);
void fn_80129314(void *, s32, CStruct *);
void fn_80127AAC(void *, s32, void *);
void fn_80126A30(void *);
void fn_80128FB4(void *, s32);
void *Script_SpawnScript(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32);
void CStruct_delete(void *, s32);

void fn_8019B49C(void *arg0) {
    CStruct *obj_a;
    void *list;
    CStruct *e;
    GoalEntry *ent;
    s32 i;
    char *flags;
    s32 sp8;
    s32 spC;
    s32 ctr;

    if (fn_801868AC(Game_GetGoalManager()) != 0) {
        obj_a = (CStruct *)CStruct_ctor(CStruct_new(8));
        list = fn_80128F94((void *)fn_8003E7CC(0xC));
        fn_80129068(list, 5, 0xA);
        ctr = 8;
        do {
        } while (--ctr != 0);
        i = 0;
        flags = (char *)arg0 + 0x1C;
        do {
            e = (CStruct *)CStruct_ctor(CStruct_new(8));
            ent = (GoalEntry *)((char *)arg0 + 0xC + i * 0x24);
            AddString(e, QB_NAME, (void *)fn_800093A4(ent));
            AddInteger(e, QB_SCORE, fn_8019A448(ent, *(s32 *)((char *)arg0 + 8)));
            if (*(s32 *)(flags + i * 0x24) == 0) {
                AddChecksum(e, 0, QB_PLAYER);
            }
            fn_80129314(list, i, e);
            i++;
        } while (i <= 4);
        fn_80127AAC(obj_a, QB_LEADER_BOARD, list);
        fn_80126A30(list);
        if (list != 0) {
            fn_80128FB4(list, 3);
        }
        spC = 0;
        sp8 = 0;
        Script_SpawnScript(QB_GOAL_COMP_ADD_LEADER_BOARD, obj_a, 0, 0, 0, 0, 0, 0, sp8, spC);
        if (obj_a != 0) {
            CStruct_delete(obj_a, 3);
        }
    }
}
