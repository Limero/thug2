// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800615D0-0x8006167C (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct Node {
    void *unk0x0;
    struct Node *unk0x4;
} Node;
typedef struct NodeOwner {
    char pad0x0[0x10];
    Node *unk0x10;
} NodeOwner;
extern s32 fn_8005F878(void *, s32, s32, s32);
s32 fn_800615D0(NodeOwner *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Node * volatile sp8;
    s32 volatile pad;
    Node * volatile sp10;
    Node *cur;
    Node *n;
    s32 res;
    s32 t;
    s32 b1;
    s32 b2;
    register s32 h __asm__("r9");
    register s32 n9 __asm__("r11");

    h = (s32)arg0->unk0x10;
    res = 0;
    sp8 = (Node *)h;
    cur = (h != 0) ? (Node *)(*(s32 *)((char *)(Node *)h + 4)) : NULL;
    goto test;
body:
    t = fn_8005F878(*(void **)sp10->unk0x0, arg1, arg2, arg3);
    b1 = (res != 0) ? 1 : 0;
    b2 = (t != 0) ? 1 : 0;
    n9 = (s32)sp10;
    res = b1 | b2;
    h = (s32)sp8;
    cur = (Node *)(*(s32 *)((char *)(Node *)n9 + 4));
test:
    if ((sp10 = cur, (s32)cur != h)) {
        goto body;
    }
    return res;
}
