// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024EE00-0x8024EE6C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
// MSL heap block allocation: rounds size up to 4, allocates sz+0x10 via the
// heap fn pointer (lbl_803CA344), and stamps the block header (word count +
// -1 sentinel). Suggested rename: fn_8024EE00_heap_alloc_block.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_803CA344;

typedef s32 (*heap_alloc_t)(s32);

void *fn_8024EE00(CStruct *arg0, s32 arg1) {
    heap_alloc_t fp = (heap_alloc_t)lbl_803CA344;
    u32 sz = (arg1 + 3) & QB_UNKNOWN_0xFFFFFFFC;
    u32 w;
    s32 h;

    w = sz >> 2;
    __asm__("" : "=r"(w) : "0"(w));
    arg0->unk0x4 = 0;
    h = (*fp)(sz + 0x10);
    *(s32 *)arg0 = h;
    *(u32 *)h = (sz >> 2) & 0xFFFFFF;
    ((s32 *)*(s32 *)arg0)[w] = -1;
    return (void *)arg0;
}
