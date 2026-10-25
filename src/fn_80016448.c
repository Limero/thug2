// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016448-0x8001666C (548B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* Allocation stack object behind lbl_802FFE98; only the 0x11C "top" slot is
   read here (fn_8000F2F8 pushes/pops entries at 0xCC/0xD0/0x110). */
typedef struct CardAllocStack {
    char pad0[0x11C];
    void *unk11C;
} CardAllocStack;

/* `self->card` — the CARDFileInfo behind 0x80; +8 is the sector size. */
typedef struct CardHandle {
    char pad0[8];
    s32 sectorSize;
} CardHandle;

/* `self` — 0x50 CARDDesc, 0x68 buffered flag, 0x6C byte cursor,
   0x70 sector bounce buffer, 0x80 card handle. */
typedef struct CardWriter {
    char pad0[0x50];
    char desc[0x18];
    s32 buffered;
    s32 cursor;
    u8 *sectorBuf;
    char pad74[0xC];
    CardHandle *card;
} CardWriter;

extern CardAllocStack *lbl_802FFE98;

void memcpy();                    /* want keeps crclr before all 3 calls */
void memset(void *, s32, s32);    /* want has no crclr here -> prototyped */

void fn_8000F2F8(CardAllocStack *, void *);
void fn_80010D94(void *, s32);
void fn_80010E78(void *);
void fn_8000F320(CardAllocStack *);
s32 Mem_Alloc_3(s32);
s32 CARDWrite(void *, void *, s32, s32);

s32 fn_80016448(CardWriter *self, void *src, s32 len) {
    if (self->sectorBuf == 0) {
        /* No local alias: want reloads lbl_802FFE98 once per call (the page
           anchor is CSE'd into r30, the *value* is not). */
        fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->unk11C);
        fn_80010D94(lbl_802FFE98->unk11C, 0x20);
        self->sectorBuf = (u8 *)Mem_Alloc_3(self->card->sectorSize);
        fn_80010E78(lbl_802FFE98->unk11C);
        fn_8000F320(lbl_802FFE98);
    }

    self->buffered = 0;
    {
        u8 *p = (u8 *)src;
        s32 left = len;
        s32 cursor = self->cursor;
        /* signed modulo: divw + mullw + subf, and the sign of the result is
           NOT provable, which is why want keeps the `fit != 0` test. */
        s32 offset = cursor % self->card->sectorSize;
        s32 fit = self->card->sectorSize - offset;

        if (len < fit) {
            /* whole write lands in the current sector */
            memcpy(self->sectorBuf + offset, p, len);
            self->buffered = 1;
            self->cursor = self->cursor + len;
            return len;
        } else {
            s32 sector = cursor - offset;
            if (fit != 0) {
                s32 ret;
                memcpy(self->sectorBuf + offset, p, fit);
                p = p + fit;
                left = len - fit;
                self->cursor = self->cursor + fit;
                ret = CARDWrite(self->desc, self->sectorBuf, self->card->sectorSize, sector);
                if (ret != 0) {
                    return 0;
                }
                {
                    /* want loads the sector size *before* the buffered store */
                    s32 sz = self->card->sectorSize;
                    self->buffered = ret;
                    sector = sector + sz;
                }
            }
            if (left != 0) {
                do {
                    if (left >= self->card->sectorSize) {
                        s32 ret;
                        memcpy(self->sectorBuf, p, self->card->sectorSize);
                        self->cursor = self->cursor + self->card->sectorSize;
                        left = left - self->card->sectorSize;
                        p = p + self->card->sectorSize;
                        ret = CARDWrite(self->desc, self->sectorBuf, self->card->sectorSize, sector);
                        if (ret != 0) {
                            return 0;
                        }
                        {
                            /* same: want reads the sector size before the store */
                            s32 sz = self->card->sectorSize;
                            self->buffered = ret;
                            sector = sector + sz;
                        }
                    } else {
                        /* tail sector: copy, then zero-pad the remainder */
                        memcpy(self->sectorBuf, p, left);
                        memset(self->sectorBuf + left, 0, self->card->sectorSize - left);
                        self->buffered = 1;
                        self->cursor = self->cursor + left;
                        left = 0;
                    }
                } while (left != 0);
            }
        }
    }
    return len;
}
