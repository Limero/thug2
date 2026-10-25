// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033360-0x80033530 (464B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct {
    char pad0x0[0x20];
    s16 unk0x20;
    char pad0x22[0x2];
    s32 (*unk0x24)(void *, s32, void *, s32);
} Vt;

typedef struct {
    char pad0x0[0x14];
    Vt *unk0x14;
} Node;

typedef struct {
    char pad0x0[0x1C];
    f32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    char pad0x28[0x10];
    s32 unk0x38;
    char pad0x3C[0x4];
    Node *unk0x40[6];
    s32 unk0x58;
} Obj;

extern f32 lbl_80291B5C;
s32 ContainsFlag(void *, s32);
s32 GetFloat(void *, s32, f32 *, s32);
s32 GetChecksum_2(void *, s32, s32 *, s32);
void fn_80032388(Obj *, void *);
void fn_80032698(Obj *, void *);
void *fn_80032778(Obj *, s32);
void fn_80032F18(Obj *);
void fn_80032FB4(Obj *, s32);
void fn_8002DDE8(char *, f32);

s32 fn_80033360(Obj *arg0, u32 arg1, void *arg2, s32 arg3) {
    f32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 i;
    void *temp_r3;
    Vt *vt;
    Node *node;
    Node **entries;
    s32 r;
    f32 f0;
    f32 f1;

    switch (arg1) {
    case QB_ADDANIMCONTROLLER:
        fn_80032388(arg0, arg2);
        return 1;
    case QB_REMOVEANIMCONTROLLER:
        GetChecksum_2(arg2, QB_ID, &sp8, 1);
        temp_r3 = fn_80032778(arg0, sp8);
        if (temp_r3 != NULL) {
            fn_80032698(arg0, temp_r3);
        }
        break;
    case QB_REPLACEANIM:
        GetChecksum_2(arg2, QB_ANIM, &spC, 1);
        GetFloat(arg2, QB_DURATION, &sp10, 1);
        temp_r30 = ContainsFlag(arg2, QB_SYNC);
        arg0->unk0x38 = spC;
        fn_80032F18(arg0);
        fn_80032FB4(arg0, arg0->unk0x38);
        if (temp_r30 != 0) {
            f0 = arg0->unk0x20 / arg0->unk0x24;
            arg0->unk0x20 = lbl_80291B5C;
            f1 = f0 * sp10;
        } else {
            f1 = lbl_80291B5C;
        }
        arg0->unk0x24 = sp10;
        arg0->unk0x1C = lbl_80291B5C;
        fn_8002DDE8((char *)arg0 + 4, f1);
        break;
    default:
        break;
    }

    i = 0;
    if (i < arg0->unk0x58) {
        entries = (Node **)((char *)arg0 + 0x40);
        do {
            node = entries[i];
            vt = node->unk0x14;
            r = vt->unk0x24((char *)node + vt->unk0x20, arg1, arg2, arg3);
            if (r != 2) {
                return r;
            }
            i++;
        } while (i < arg0->unk0x58);
    }
    return 2;
}
