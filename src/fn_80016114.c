// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016114-0x800161C4 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

// CARDStat out-param of CARDGetStatus (frame offset r1+8, size 0x70).
// Only 0x20 (mtime) and 0x24 (ctime) are read back by this function.
typedef struct CardStat {
    char gameCode[0x20];
    s32 mtime;
    s32 ctime;
    char pad0x28[0x48];
} CardStat;

// The per-slot node: fn_8001621C ctor, then name/date/list splice.
typedef struct CardNode {
    char pad0x00[0x4];
    s32 unk0x4;
    s32 unk0x8;
    struct CardNode *unk0xC;
    struct CardNode *unk0x10;
    s32 unk0x14;
    char unk0x18[0x28];
    char unk0x40[0x8];
    s32 unk0x48;
    u16 unk0x4C;
    char pad0x4E[0x1A];
    s32 unk0x68;
    s32 unk0x6C;
    s32 unk0x70;
    s32 unk0x74;
    s32 unk0x78;
    s32 unk0x7C;
    s32 unk0x80;
} CardNode;

char *strcpy(char *, const char *);
s32 CARDGetStatus(s32 chan, s32 fileNo, CardStat *stat);
void *Mem_NewZero(s32 size);
void fn_80016094(s32 ticks, char *out);
CardNode *fn_8001621C(CardNode *self, s32 a1, CardNode *a2);

bool fn_80016114(CardNode *arg0, s32 arg1, CardNode *arg2) {
    CardStat stat;
    CardNode *temp_r3;
    s32 var_r29;

    var_r29 = 0;
    do {
        if (CARDGetStatus(0, var_r29, &stat) == 0) {
            temp_r3 = fn_8001621C((CardNode *)Mem_NewZero(0x84), 0, arg0);
            strcpy(&temp_r3->unk0x18[0], stat.gameCode);
            temp_r3->unk0x48 = stat.mtime;
            temp_r3->unk0x4C = 3;
            fn_80016094(stat.ctime, &temp_r3->unk0x40[0]);
            temp_r3->unk0x10 = arg2->unk0x10;
            temp_r3->unk0xC = arg2;
            arg2->unk0x10->unk0xC = temp_r3;
            arg2->unk0x10 = temp_r3;
        }
        var_r29 += 1;
    } while (var_r29 <= 0x7E);
    return true;
}
