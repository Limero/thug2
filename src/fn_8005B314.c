// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005B314-0x8005B3C0 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse -fno-rerun-cse-after-loop
#include "types.h"
void *Mem_Alloc(s32);
extern f32 lbl_802935A4;
extern f32 lbl_802935A8;
extern char lbl_802935C0[];
extern u32 lbl_8030047C;

typedef struct S5B314 {
    s32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
    void *unk0x10;
    s32 unk0x14;
    u32 unk0x18;
} S5B314;

void *fn_8005B314(S5B314 *arg0) {
    volatile double _dummy;
    f32 dflt;
    f32 lo;
    f32 fill;
    void *arr;
    u32 count;
    u32 i;

    dflt = lbl_802935A8;
    lo = lbl_802935A4;
    arg0->unk0x18 = (u32)lbl_802935C0;
    arg0->unk0xC = dflt;
    arg0->unk0x8 = lo;
    arg0->unk0x4 = lo;
    arr = Mem_Alloc(lbl_8030047C * 4);
    count = lbl_8030047C;
    i = 0;
    arg0->unk0x10 = arr;
    if (i < count) {
        fill = dflt;
        do {
            ((f32 *)arg0->unk0x10)[i] = fill;
            i++;
        } while (i < count);
    }
    arg0->unk0x0 = 0;
    arg0->unk0x14 = 0;
    return arg0;
}
