// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A32C0-0x800A3308 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    s32 unk0x00;
    s32 id;       /* +0x04 */
    s32 owner;    /* +0x08 */
    s32 *next;    /* +0x0C */
    s32 *prev;    /* +0x10 */
    void *vt;     /* +0x14 */
} TNode32C0;

typedef struct {
    s32 unk0x00;
    TNode32C0 node;   /* +0x04 .. +0x1B */
    s32 unk0x1C;
    s32 unk0x20;
    s32 unk0x24;
    s32 unk0x28;
    void *vt;         /* +0x2C */
} TA32C0;

extern char lbl_80297FA8[];
extern char lbl_80297FF0[];

void *fn_800A32C0(void *arg0) {
    TA32C0 *p = (TA32C0 *)arg0;
    TNode32C0 *q = &p->node;
    p->vt = lbl_80297FA8;
    q->id = -1;
    q->owner = 0;
    q->next = q;
    q->prev = q;
    q->vt = lbl_80297FF0;
    p->unk0x1C = 0;
    p->unk0x20 = 0;
    p->unk0x28 = 0;
    return arg0;
}
