// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FED0-0x8003FF04 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct LNode LNode;
struct LNode {
    char _pad[0x70];
    LNode *next;
};

typedef struct {
    char _pad[0x64];
    LNode *head;
} LList;

void fn_8003FED0(LList *arg0) {
    register s32 p __asm__("r3");

    p = (s32)arg0->head;
    if (p == 0) return;
    while (*(s32 *)((char *)p + 0x70) != 0) {
        p = *(s32 *)((char *)p + 0x70);
        if (p == 0) return;
    }
}
