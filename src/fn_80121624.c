// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121624-0x80121798 (372B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern char lbl_8029DEB4[];
extern char lbl_8029DEE8[];
extern char lbl_8029DF28[];
extern bool lbl_8039BD1C;
extern void fn_8012156C(void);

typedef struct {
    s32 addr;   /* +0x0 absolute sector buffer (1st DVDReadAsyncPrio arg) */
    s32 nsect;  /* +0x4 sectors read for this slot (== err), 0 = failure */
    s32 total;  /* +0x8 running sector total when this slot was queued */
    s32 busy;   /* +0xC slot occupied */
} Slot_t;

typedef struct {
    char pad00[0x8C];
    s32 maxRead;
    char pad08[0x2D0 - 0x90];
    s32 reading;
    s32 offset;
    s32 lba;
    s32 ptr;
    char pad10[0x2EC - 0x2E0];
    u32 cur;
    u32 pad11;
    Slot_t slots[10];
} CB_t;

extern CB_t lbl_8039BA58;

void fn_80121624(s32 err) {
    if (err == -1) {
        lbl_8039BD1C = 1;
        return;
    }
    if (err == -3) {
        return;
    }
    {
        CB_t *cb = &lbl_8039BA58;
        u32 *hdr;

        cb->reading = 0;
        cb->slots[cb->cur].total = cb->ptr;
        cb->slots[cb->cur].nsect = err;
        cb->slots[cb->cur].busy = 1;
        cb->ptr = cb->ptr + 1;
        cb->offset = cb->offset + cb->lba;
        if ((u32)cb->ptr < (u32)cb->maxRead) {
            hdr = (u32 *)((char *)cb->slots[cb->cur].addr + cb->lba) - 8;
            if (hdr[0] != QB_FOURCC_FRAM) {
                OSPanic(lbl_8029DEB4, 0xE0, lbl_8029DEE8);
            }
            cb->lba = hdr[1];
            if (cb->lba == 0) {
                OSPanic(lbl_8029DEB4, 0xE4, lbl_8029DF28);
            }
        } else {
            cb->lba = 0;
        }
        {
            CB_t *c2 = &lbl_8039BA58;

            c2->cur = (c2->cur + 1) % 10;
            if (c2->slots[c2->cur].busy == 0) {
                fn_8012156C();
            }
        }
    }
}
