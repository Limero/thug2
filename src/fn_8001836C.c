// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001836C-0x80018400 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* Row187BC is byte-proven by the promoted callee src/fn_800187BC.c (queue_front_2):
   it copies three words out[0]/out[4]/out[8] of a 12-byte row. Table187BC is the
   0x40-byte lbl_8031E748 table it indexes. */
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
extern s32 lbl_8031E7D4;
extern u8 lbl_8031E7D9;
extern s32 lbl_8030015C;
void SetNextBreakPt(void);
Row187BC *queue_front_2(Row187BC *arg0, Table187BC *arg1);

void BPCallback(void) {
    Row187BC sp8;
    Row187BC sp18;
    Row187BC *p = &sp18;
    s32 (*temp_r0)();

    queue_front_2(p, (Table187BC *)lbl_8031E748);
    sp8 = sp18;
    if (sp8.unk0x8 == lbl_8031E7D4) {
        lbl_8031E7D9 = 1;
    } else {
        SetNextBreakPt();
    }
    temp_r0 = *(s32 (**)())&lbl_8030015C;
    if (temp_r0 != NULL) {
        ((s32 (*)())temp_r0)();
    }
}
