// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80011CF4-0x80011D7C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0[0x8C];
    s32 used;
    s32 key[5];
    s32 val[5];
} Unk_80011CF4;

bool fn_80011CF4(Unk_80011CF4 *tab, s32 arg1, s32 arg2) {
    s32 *keys;
    s32 *vals;
    s32 i;
    char *vals2;
    s32 off;
    register s32 keys2 __asm__("r7");

    /* pass 1: refresh the value of an existing entry */
    keys = &tab->key[0];
    vals = keys + 5;
    for (i = 0; i < 5; i++) {
        if (vals[-5] == arg1) {
            vals[-5] = arg1;
            *vals = arg2;
            return true;
        }
        vals++;
    }

    /* pass 2: claim the first free slot */
    keys2 = (s32)keys;
    vals2 = (char *)&tab->val[0];
    off = 0;
    for (i = 0; i < 5; i++) {
        if (*(s32 *)((char *)off + keys2) == 0) {
            *(s32 *)((char *)off + (s32)keys) = arg1;
            *(s32 *)vals2 = arg2;
            tab->used = tab->used + 1;
            return true;
        }
        vals2 += 4;
        off += 4;
    }
    return false;
}
