// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CBC24-0x800CBCB4 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Node_800CBC24 {
    char _pad0[4];
    s32 unk4;              /* -1 == end-of-list sentinel */
    char _pad8[0x1C];
    void *unk24;           /* ->next object */
} Node_800CBC24;

typedef struct Obj_800CBC24 {
    char _pad0[0x38];
    Node_800CBC24 *unk38;  /* head, reached via the +0x38 shortcut */
} Obj_800CBC24;

extern f32 lbl_8029944C[];                /* .rodata2 0x8029944C == 0.0f */

f32 fn_800CBC24(Obj_800CBC24 *arg0) {
    Node_800CBC24 *p;
    Node_800CBC24 *p2;
    void *q;
    void *r;
    Node_800CBC24 *s;
    s32 t;

    p = arg0->unk38;
    if (p->unk4 == -1) {
        p = NULL;
    }
    if (p != NULL) {
        p2 = p->unk24;
        __asm__("" : "+r"(p2));
        t = (p2->unk4 == -1);
        q = p2;
        if (t) {
            q = NULL;
        }
        r = (q != NULL) ? (char *)q - 4 : NULL;
        if (r == NULL) {
            return lbl_8029944C[0];
        }
        if (t) {
            p2 = NULL;
        }
        s = (p2 != NULL) ? (char *)p2 - 4 : NULL;
        return *(f32 *)((char *)s + 0x20);
    }
    return lbl_8029944C[0];
}
