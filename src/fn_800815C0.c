// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800815C0-0x80081630 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_800145AC(void);

typedef struct {
    char pad0[0x10];
    u32 unk0x10;
} N815C0;

typedef struct {
    char pad0[0x20];
    N815C0 **unk0x20;
    s32 unk0x24;
} O815C0;

void fn_800815C0(O815C0 *arg0) {
    u32 v;
    s32 i;

    v = fn_800145AC() & 0x7FFFFFFF;
    i = 0;
    while (i < arg0->unk0x24) {
        N815C0 *p = arg0->unk0x20[i];
        p->unk0x10 = (p->unk0x10 & 0x80000000) | v;
        i++;
    }
}
