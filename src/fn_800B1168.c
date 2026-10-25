// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B1168-0x800B11D4 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80301B0C[];
// The list header and the list nodes share a layout but not a field type:
// header+4 is the first node pointer, while node+4 is the id being matched
// (want `lwz r3, 4(r3)` then `lwz r0, 4(r3)`).
typedef struct Node { s32 unk0; s32 id; char pad8[0xA0]; struct Node *next; } Node;
typedef struct NodeHead { s32 unk0; struct Node *first; } NodeHead;
void fn_800B15B0(void *, s32);
void fn_800B1168(s32 id, s32 flag) {
    NodeHead *head = *(NodeHead **)lbl_80301B0C;
    if (head != NULL) {
        Node *p = head->first;
        if (p != NULL) {
            for (;;) {
                if (p->id == id) {
                    s32 f = 1;
                    if (flag == 0) f = 0;
                    fn_800B15B0(p, f);
                    return;
                }
                p = p->next;
                if (p == NULL) return;
            }
        }
    }
}
