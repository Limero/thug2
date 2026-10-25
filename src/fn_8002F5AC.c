// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002F5AC-0x8002F700 (340B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Node {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Node;

typedef struct Vec {
    s32 unk0;
    u32 cnt;
    s32 *data;
} Vec;

typedef struct Res {
    u8 pad0[2];
    u8 kind;
    u8 pad3[1];
    s32 unk4;
    s32 unk8;
    Vec *vec;
} Res;

Node *fn_80127358(void *ctx, Node *cur);
Res *fn_80125480(s32 x);
s32 GetChecksum(Vec *v, u32 i);

bool fn_8002F5AC(void *arg0, void *arg1) {
    s32 *p = *(s32 **)((char *)arg0 + 0x24);
    s32 cond;
    s32 a;
    s32 b;
    s32 c1;
    s32 c2;
    s32 target;
    Node *node;
    Vec *vec;
    u32 i;

    cond = p[1] + 1 == 0;
    a = (s32)p;
    if (cond) {
        a = 0;
    }
    c1 = (a != 0) ? a - 4 : 0;
    if (c1 == 0) {
        target = 0;
    } else {
        b = (s32)p;
        if (cond) {
            b = 0;
        }
        c2 = (b != 0) ? b - 4 : 0;
        target = *(s32 *)((char *)c2 + 0x38);
    }

    node = 0;
    while ((node = fn_80127358(arg1, node)) != 0) {
        if (node->unk4 == 0) {
            u32 v = node->unk0;
            vec = 0;
            if ((v & 0x7F0000) == 0xD0000) {
                Res *res = fn_80125480(node->unk8);
                if ((res != 0) && (res->kind == 0xC)) {
                    vec = res->vec;
                } else if (node->unk8 == target) {
                    return true;
                }
            } else if ((v & 0x7F0000) == 0xC0000) {
                vec = (Vec *)node->unk8;
            }
            if (vec != 0) {
                for (i = 0; i < vec->cnt; i++) {
                    if (GetChecksum(vec, i) == target) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
