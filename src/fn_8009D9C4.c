// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D9C4-0x8009DA18 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* {mask, byteIndex} table entry — 8 bytes, matched on s32 widths. */
typedef struct {
    s32 mask;
    s32 idx;
} TAB;

/* The object whose +0x1C word is ANDed against every entry mask. */
typedef struct {
    char pad0x00[0x1C];
    s32 unk0x1C;
} OBJ;

extern TAB lbl_8030197C[];

void fn_8009D9C4(OBJ *arg0, s32 arg1) {
    TAB *w = lbl_8030197C;
    TAB *e;
    u8 *p;
    s32 r;
    s32 ff;

    __asm__("" : "+r"(w));
    if (w->mask > 0) {
        e = w;
        p = (u8 *)arg0 + 1;
        ff = 0xFF;
        do {
            r = arg0->unk0x1C & e->mask;
            if (r != 0) {
                p[e->idx] = (u8)ff;
            } else {
                p[e->idx] = (u8)r;
            }
            e++;
        } while (e->mask > 0);
    }
}
