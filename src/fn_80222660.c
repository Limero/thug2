// range 0x80222660-0x802226B0 (80B). Byte-identical; link-level exactness was
// verified against the full linked DOL.
//
// "are there any servers?" — walks the node list hanging off
// `lbl_80305F9C + 0x184`, counts nodes, returns whether the count is non-zero.
// A node ends the walk when its +0x4 word reads the -1 sentinel.
//
// The head's sentinel is loaded before the head is copied into the walker;
// the empty-asm barrier carries both values so the copy survives. The trailing
// clobber of the walker register keeps the false arm a literal zero instead of
// a move out of the register the allocator already knows is zero.
#include "types.h"
#include "structs.h"

typedef struct SNode {
    s32 pad0x0;
    s32 key;
    s32 pad0x8;
    struct SNode *next;
} SNode;

typedef struct SMgr {
    char pad[0x184];
    SNode *head;
} SMgr;

extern s32 lbl_80305F9C;

bool ScriptFoundServers(void) {
    SNode *head;
    s32 v;
    s32 count = 0;
    register void *walker __asm__("r9");

    head = *(SNode **)((char *)(*(SMgr **)&lbl_80305F9C) + 0x184);
    v = head->key;
    walker = head;
    __asm__("" : "+r"(walker) : "r"(v), "r"(head));
    while ((((v == -1) && (walker = NULL)), walker != NULL)) {
        walker = ((SNode *)walker)->next;
        count += 1;
        v = ((SNode *)walker)->key;
    }
    __asm__("" : "+r"(walker));
    return count != 0;
}
