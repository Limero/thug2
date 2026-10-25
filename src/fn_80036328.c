// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80036328-0x80036370 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    s32 key;
    s32 flags;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
} Entry;

typedef struct {
    s32 unk0x00[5];
    s32 count;
    Entry *entries;
} LookupObj;

Entry *fn_80036328(LookupObj *arg0, s32 arg1) {
    register s32 count __asm__("r0");
    s32 i = 0;
    count = arg0->count;
    if (i < count) {
        Entry *base = arg0->entries;
        register s32 limit __asm__("r8");
        s32 off = 0;
        Entry *ptr = base;
        limit = count;
        do {
            if (arg1 == *(s32 *)((char *)(off + (s32)base))) {
                return ptr;
            }
            i++;
            ptr = (Entry *)((char *)ptr + 0x20);
            off += 0x20;
        } while (i < limit);
    }
    return 0;
}
