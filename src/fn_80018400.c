// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80018400-0x800184D8 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* 12-byte row / 0x40-byte ring table, byte-proven by the promoted callees
   src/fn_800186D8.c (enqueue), src/fn_800187BC.c (queue_front_2) and
   src/fn_8001836C.c (BPCallback, which matches with sp8 at 0x8 / sp18 at
   0x18 — the same offsets and the same struct-assignment store order here). */
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
} Row187BC;

typedef struct {
    Row187BC rows[5];
    u16 unk0x3C;
    u16 unk0x3E;
} Table187BC;

extern char lbl_8031E748[];
extern char lbl_8031E788[];
extern char lbl_8031E7E0[];
extern u8 lbl_8031E7D8;
extern s32 lbl_80300158;

void enqueue(Table187BC *arg0, Row187BC *arg1);
void dequeue(Row187BC *out, Table187BC *t);
Row187BC *queue_front_2(Row187BC *out, Table187BC *t);
s32 queue_empty(Table187BC *t);
void OSWakeupThread(void *q);
void GX_EnableBreakPt(s32 x);
void GX_DisableBreakPt(void);

void SetNextBreakPt(void) {
    Row187BC sp8;
    Row187BC sp18;
    s32 (*temp_r0)();

    dequeue(&sp18, (Table187BC *)lbl_8031E748);
    sp8 = sp18;
    enqueue((Table187BC *)lbl_8031E788, &sp8);
    OSWakeupThread(lbl_8031E7E0);
    if (queue_empty((Table187BC *)lbl_8031E748) != 0) {
        GX_DisableBreakPt();
        lbl_8031E7D8 = 0;
    } else {
        queue_front_2(&sp18, (Table187BC *)lbl_8031E748);
        sp8 = sp18;
        GX_EnableBreakPt(sp8.unk0x0);
        temp_r0 = *(s32 (**)())&lbl_80300158;
        if (temp_r0 != NULL) {
            ((s32 (*)())temp_r0)();
        }
    }
}
