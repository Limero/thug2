// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9AA0-0x801A9B1C (124B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void fn_801A9A70(void *);
void *fn_801A9AA0(Unk_DB0E2BAB *arg0, s32 arg1) {
    u32 count = 1 << arg1;
    u32 i;
    void *mem;
    void *p;
    arg0->unk0x0 = arg1;
    i = count - 1;
    mem = Mem_Alloc(count * 12);
    p = mem;
    if (count != 0) {
        do {
            fn_801A9A70(p);
            p = (char *)p + 12;
        } while (--i != -1);
    }
    arg0->unk0x4 = (s32)mem;
    arg0->unk0x8 = 0;
    arg0->unk0x14 = 0;
    return arg0;
}
