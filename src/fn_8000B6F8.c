// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000B6F8-0x8000B7F0 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void PADReset(s32 mask);
void fn_8000BEEC(s32);
extern char lbl_802901D8[];
extern s8 lbl_80312434[];

/* linked-list node: f04 is the payload (== -1 is the "no entry" sentinel),
   f0C is the next node */
typedef struct Nd {
    s32 f00;
    s32 f04;
    s32 f08;
    struct Nd *f0C;
} Nd;

/* 12-byte stack iterator at r1+8: f04 = cursor, f08 = lbl_802901D8 */
typedef struct It {
    s32 f00;
    Nd *f04;
    s32 f08;
} It;

/* arg0: the +0x20 field is the head node pointer */
typedef struct Holder {
    char pad0x00[0x20];
    Nd *f20;
} Holder;

void fn_8000B6F8(Holder *arg0) {
    s32 scratch;
    s32 pad1;
    s32 pad2;
    Nd *node;
    s32 v;
    s32 w;
    u32 m;

    ((It *)&scratch)->f08 = (s32)lbl_802901D8;
    ((It *)&scratch)->f04 = arg0->f20;
    node = ((It *)&scratch)->f04->f0C;
    if (node->f04 == -1) {
        node = NULL;
    }
    ((It *)&scratch)->f04 = node;
    w = (node != 0) ? node->f04 : 0;
    v = w;

    m = (lbl_80312434[0xa] == -1) ? 0x80000000 : 0;
    if (lbl_80312434[0x16] == -1) {
        m |= 0x40000000;
    }
    if (m != 0) {
        PADReset(m);
    }
    while (v != 0) {
        register Nd *lnode __asm__("r11");
        fn_8000BEEC(v);
        lnode = ((It *)&scratch)->f04->f0C;
        if (lnode->f04 == -1) {
            lnode = NULL;
        }
        ((It *)&scratch)->f04 = lnode;
        v = (lnode != 0) ? lnode->f04 : 0;
    }
    /* keeps pad1/pad2 live with zero emitted instructions so the iterator
       occupies r1+8 (see WALL 1 above) */
    __asm__("" : : "m"(pad1), "m"(pad2));
    ((It *)&scratch)->f08 = (s32)lbl_802901D8;
}
