// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80238104-0x802381E0 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_802432A0(Unk_9994C3F5 *arg0);
s32 fn_802416F8(s32 arg0);

typedef struct Rect6 {
    u8 left;
    u8 pad1;
    u8 top;
    u8 right;
    u8 pad4;
    u8 bottom;
} Rect6;

s32 fn_80238104(Unk_C7387A53 *arg0, Rect6 *arg1) {
    Rect6 sp8;
    Rect6 *p;
    Unk_C7387A53 *node;
    s32 n2;
    s32 flags;

    node = (Unk_C7387A53 *)arg0->unk0x80;
    if (node != NULL) {
        do {
            n2 = fn_802416F8(fn_802432A0((Unk_9994C3F5 *)node));
            p = &sp8;
            *p = *(Rect6 *)n2;
            if (p->left < arg1->left || p->top < arg1->top ||
                p->right + p->left > arg1->left + arg1->right ||
                p->bottom + p->top > arg1->top + arg1->bottom) {
                flags = *(s32 *)(n2 + 8);
                if (!(flags & 8)) {
                    if (!(flags & 0x100)) {
                        if (flags & 4) {
                            return 1;
                        }
                    }
                }
            }
            node = (Unk_C7387A53 *)node->unk0xC;
        } while (node != NULL);
    }
    return 0;
}
