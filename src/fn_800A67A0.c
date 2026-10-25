// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A67A0-0x800A681C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_800A6770(void *p);
void *fn_800A67A0(Unk_DB0E2BAB *arg0, s32 arg1) {
    u32 n;
    u32 i;
    void *base;
    void *p;

    n = 1 << arg1;
    arg0->unk0x0 = arg1;
    i = n - 1;
    base = (void *)Mem_Alloc(n * 0xC);
    p = base;
    if (n != 0) {
        do {
            fn_800A6770(p);
            p = (char *)p + 0xC;
        } while (i-- != 0);
    }
    arg0->unk0x4 = (s32)base;
    arg0->unk0x8 = 0;
    arg0->unk0x14 = 0;
    return arg0;
}
