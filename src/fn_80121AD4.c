// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121AD4-0x80121CD0 (508B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
int OSPanic();
s32 DVDReadPrio(void *, void *, u32, u32, s32);
extern char lbl_8029DEB4[];
extern char lbl_8029E08C[];
extern char lbl_8029DF28[];

/* One 10-slot ring-buffer record of the stream manager: absolute sector
   buffer, sectors in this request, running sector total when queued, busy. */
typedef struct {
    void *addr;
    s32 nsect;
    s32 total;
    s32 busy;
} Slot_t;

typedef struct {
    char pad00[0x8C];
    s32 maxRead;          /* +0x08C sectors per stream */
    char pad08[0x2C0 - 0x90];
    s32 flag2C0;          /* +0x2C0 stream open */
    s32 err;              /* +0x2C4 hard read error */
    s32 flag2C8;          /* +0x2C8 prefetch in flight */
    s32 lastarg;          /* +0x2CC arg0 of the in-flight prefetch */
    s32 reading;          /* +0x2D0 async read issued */
    s32 offset;           /* +0x2D4 byte offset inside the sector */
    s32 lba;              /* +0x2D8 current sector */
    s32 ptr;              /* +0x2DC running sector total */
    s32 unk2E0;
    s32 save_off;         /* +0x2E4 wrap-around restore values */
    s32 save_lba;         /* +0x2E8 */
    u32 cur;              /* +0x2EC slot index, wraps mod 10 */
    u32 pad2F0;
    Slot_t slots[10];     /* +0x2F4 */
} CB_t;

extern CB_t lbl_8039BA58;

bool fn_80121AD4(s32 arg0) {
    u32 n;
    u32 i;
    char *addr;
    char *hdr;

    if (lbl_8039BA58.flag2C0 != 0) {
        if (lbl_8039BA58.flag2C8 == 0) {
            n = 10;
            if (arg0 == 0 && (u32)lbl_8039BA58.maxRead <= 9) {
                n = lbl_8039BA58.maxRead;
            }
            for (i = 0; i < n; i++) {
                addr = lbl_8039BA58.slots[lbl_8039BA58.cur].addr;
                if (DVDReadPrio(&lbl_8039BA58.pad00[0xC], addr, lbl_8039BA58.lba,
                                lbl_8039BA58.offset, 2) < 0) {
                    lbl_8039BA58.err = 1;
                    return false;
                }
                lbl_8039BA58.offset = lbl_8039BA58.offset + lbl_8039BA58.lba;
                lbl_8039BA58.slots[lbl_8039BA58.cur].nsect = lbl_8039BA58.lba;
                hdr = addr + lbl_8039BA58.lba - 0x20;
                if (*(u32 *)hdr != QB_FOURCC_FRAM) {
                    OSPanic(lbl_8029DEB4, 0x1A6, lbl_8029E08C);
                }
                lbl_8039BA58.lba = *(s32 *)(hdr + 4);
                if (lbl_8039BA58.lba == 0) {
                    OSPanic(lbl_8029DEB4, 0x1A9, lbl_8029DF28);
                }
                lbl_8039BA58.slots[lbl_8039BA58.cur].busy = 1;
                lbl_8039BA58.slots[lbl_8039BA58.cur].total = lbl_8039BA58.ptr;
                lbl_8039BA58.ptr = lbl_8039BA58.ptr + 1;
                lbl_8039BA58.cur = (lbl_8039BA58.cur + 1) % 10;
                if ((u32)lbl_8039BA58.ptr > (u32)(lbl_8039BA58.maxRead - 1) &&
                    arg0 != 0) {
                    lbl_8039BA58.ptr = 0;
                    lbl_8039BA58.offset = lbl_8039BA58.save_off;
                    lbl_8039BA58.lba = lbl_8039BA58.save_lba;
                }
            }
            lbl_8039BA58.lastarg = arg0;
            lbl_8039BA58.flag2C8 = 1;
            return true;
        }
    }
    return false;
}
