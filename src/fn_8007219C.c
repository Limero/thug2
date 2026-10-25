// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007219C-0x80072230 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern bool lbl_803015F0;
extern char lbl_8036B3A0[];

typedef struct TableChild {
    char pad0x0[0x4];
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    char pad0x20[0x40];
} TableChild;

typedef struct TableEntry {
    char pad0x0[0x1C];
    s32 count;
    TableChild children[512];
    s32 key;
    s32 callback;
} TableEntry;

s32 fn_8007219C(s32 arg0) {
    char *ret;
    TableEntry *out;
    u32 var_r10;
    char *base;
    char *entry;
    char *key;
    char *copy;
    s32 val;

    var_r10 = 0U;
    if (var_r10 < (u32)lbl_803015F0) {
        base = lbl_8036B3A0;
        key = base + 0xC020;
        entry = base;
        do {
            val = *(s32 *)key;
            key += 0xC028;
            __asm__("mr %0,%1" : "=r"(copy) : "r"(entry));
            if (val == arg0) {
                return (s32)entry;
            }
            entry = copy + 0xC028;
            var_r10 += 1;
        } while (var_r10 < (u32)lbl_803015F0);
    }

    var_r10 = (u32)lbl_803015F0;
    switch (var_r10) {
    case 0:
        out = (TableEntry *)lbl_8036B3A0;
        lbl_803015F0 = 1;
        out->count = 0;
        out->key = arg0;
        break;
    default:
        return 0;
    }
    return (s32)out;
}
