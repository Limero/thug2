// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121CD0-0x80121D80 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char pad_000[0xC];
    char dvd[0x2B4];
    s32 unk2C0;
    s32 unk2C4;
    s32 unk2C8;
    s32 unk2CC;
    s32 unk2D0;
    s32 unk2D4;
    s32 unk2D8;
    s32 unk2DC;
    s32 unk2E0;
    s32 unk2E4;
    s32 unk2E8;
    s32 unk2EC;
    s32 unk2F0;
    s32 unk2F4;
    s32 unk2F8;
    s32 unk2FC;
    s32 arr[0x28];
} Blk;
extern Blk lbl_8039BA58;
void DVDCancel(void *);
bool fn_80121CD0(void) {
    char *q;
    s32 z;
    s32 k;
    s32 i;

    if (lbl_8039BA58.unk2C0 != 0) {
        lbl_8039BA58.unk2C8 = 0;
        if (lbl_8039BA58.unk2D0 != 0) {
            DVDCancel(&lbl_8039BA58.dvd[0]);
            lbl_8039BA58.unk2D0 = 0;
        }
        q = (char *)lbl_8039BA58.arr;
        z = 0;
        k = 0;
        for (i = 0; i < 10; i++) {
            *(s32 *)(q + k) = z;
            k += 0x10;
        }
        lbl_8039BA58.unk2DC = 0;
        lbl_8039BA58.unk2D4 = lbl_8039BA58.unk2E4;
        lbl_8039BA58.unk2D8 = lbl_8039BA58.unk2E8;
        lbl_8039BA58.unk2C4 = 0;
        lbl_8039BA58.unk2EC = 0;
        lbl_8039BA58.unk2F0 = 0;
        return true;
    }
    return false;
}
