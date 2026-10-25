// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801876C8-0x801877F4 (300B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct Node {
    void *unk0;
    struct Node *unk4;
} Node;

typedef struct Ent {
    char pad0x0[0x2C];
    Node *unk0x2C;
    Node *unk0x30;
} Ent;

typedef struct Obj {
    char pad0x0[0x4];
} Obj;

s32 fn_80184168(s32);
Ent *fn_8018B4C0(void *, s32 *, s32 *);
Obj *fn_8018E24C(Ent *);
Ent *GoalManager_GetGoal(s32, s32, s32);
void fn_8018B9D4(Ent *, Obj *);
void fn_8018BC14(Ent *, s32);

void fn_801876C8(s32 arg0) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 n;
    s32 found;
    Ent *res;
    Obj *o;
    Node *node;

    n = fn_80184168(arg0);
    sp8 = 0;
    while (sp8 < n) {
        res = fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
        o = fn_8018E24C(res);
        node = res->unk0x2C;
        for (; node != NULL && node->unk0 != NULL; node = node->unk4) {
            Ent *g = GoalManager_GetGoal(arg0, (s32)node->unk0, 0);
            Node *p = g->unk0x30;
            found = 0;
            for (; p != NULL && p->unk0 != NULL; p = p->unk4) {
                if (p->unk0 == (void *)o) {
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                fn_8018B9D4(g, o);
            }
        }
        sp8 += 1;
    }
    sp10 = 0;
    while (sp10 < n) {
        Ent *g = fn_8018B4C0((char *)arg0 + 4, &sp10, &sp14);
        if (g->unk0x30->unk0 == NULL) {
            fn_8018BC14(g, 0);
        }
        sp10 += 1;
    }
}
