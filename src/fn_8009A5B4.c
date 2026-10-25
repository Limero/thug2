// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009A5B4-0x8009A658 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Vtbl {
    char pad0x0[0x10];
    s16 off0;
    s32 fp0;
    s16 off1;
    s32 fp1;
    s16 off2;
    s32 fp2;
} Vtbl;

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    f32 key;
    char pad0xC[0x4];
    Vtbl *vt;
} Node;

extern Node *lbl_803018F0;
void set_blend_mode(s32 arg0, s32 arg1, s32 arg2);

void fn_8009A5B4(void) {
    Node *node;
    Vtbl *vt;
    Vtbl *vt2;
    Vtbl *vt3;
    register s32 a0 __asm__("r3");
    register s32 a2 __asm__("r5");
    register s32 a1 __asm__("r4");

    __asm__ volatile("li %0,0\n\tli %1,0\n\tli %2,5"
                     : "=r"(a0), "=r"(a2), "=r"(a1));
    set_blend_mode(a0, a1, a2);

    node = lbl_803018F0;
    if (node != NULL) {
        do {
            if (node->prev == NULL) {
                vt = node->vt;
                ((void (*)(void *))vt->fp0)((char *)node + vt->off0);
                vt2 = node->vt;
                ((void (*)(void *))vt2->fp1)((char *)node + vt2->off1);
                vt3 = node->vt;
                ((void (*)(void *))vt3->fp2)((char *)node + vt3->off2);
            }
            node = node->next;
        } while (node != NULL);
    }
}
