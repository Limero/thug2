// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006EC98-0x8006ED14 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8006EC68(void *);
void *fn_8006EC98(Unk_DB0E2BAB *arg0, s32 arg1) {
    s32 n;
    s32 cnt;
    s32 *p;
    s32 *w;

    n = 1 << arg1;
    arg0->unk0x0 = arg1;
    cnt = n - 1;
    p = (s32 *)Mem_Alloc(n * 0xC);
    w = p;
    if (n != 0) {
        do {
            fn_8006EC68(w);
            w += 3;
        } while (--cnt != -1);
    }
    arg0->unk0x4 = (s32)p;
    arg0->unk0x8 = 0;
    arg0->unk0x14 = 0;
    return arg0;
}