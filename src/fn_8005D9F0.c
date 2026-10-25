// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005D9F0-0x8005DA6C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8005D814(void *p);
Unk_DB0E2BAB *fn_8005D9F0(Unk_DB0E2BAB *arg0, s32 arg1) {
    u32 count;
    u32 i;
    char *base;
    char *p;

    count = 1 << arg1;
    arg0->unk0x0 = arg1;
    i = count - 1;
    base = (char *)Mem_Alloc(count * 0xC);
    p = base;
    if (count != 0) {
        do {
            fn_8005D814(p);
            p += 0xC;
        } while (i-- != 0);
    }
    arg0->unk0x4 = (s32)base;
    arg0->unk0x8 = 0;
    arg0->unk0x14 = 0;
    return arg0;
}
