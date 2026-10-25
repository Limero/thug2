// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801306F4-0x801307E0 (236B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 CStruct_dtor(void *);
s32 fn_8012DC0C(s32, s32, s32);
s32 GetInteger(s32, s32, s32, s32);

typedef struct Node1306F4 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    char pad14[0x20];
} Node1306F4;

typedef struct Obj1306F4 {
    char pad0[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
    Node1306F4 *f1C;
    char pad20[0x14];
    Node1306F4 *f34;
} Obj1306F4;

void fn_801306F4(Obj1306F4 *arg0) {
    Node1306F4 *node;
    Node1306F4 *n1;
    s32 t10;

    node = arg0->f1C;
    if (node->fC != 0) {
        arg0->f10 = arg0->f10 + 1;
        CStruct_dtor((void *)arg0->f14);
        arg0->f1C->f4 = fn_8012DC0C(arg0->f14, arg0->f10, arg0->f18);
        arg0->f1C->f8 = GetInteger(arg0->f14, 0, (s32)arg0->f1C + 0x10, 0);
        arg0->f1C->fC = 0;
    }
    n1 = arg0->f1C;
    if (n1->f8 != 0) {
        n1->f10 = n1->f10 - 1;
        n1 = arg0->f1C;
        t10 = n1->f10;
        if (t10 == 0) {
            goto tail_special;
        }
    }
    arg0->f10 = n1->f0;
    return;
tail_special:
    arg0->f10 = n1->f4;
    if (n1 == arg0->f34) {
        arg0->f1C = (Node1306F4 *)t10;
        return;
    }
    arg0->f1C = (Node1306F4 *)((char *)n1 - 0x14);
}
