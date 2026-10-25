// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005C868-0x8005C8D0 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
typedef struct { s32 unk0x0; u16 unk0x4; char pad0x6[2]; s32 unk0x8; char pad0xC[4]; s32 unk0x10; } Unk_C868;
s32 fn_8005D07C(void *, s32);
extern char lbl_802936E8[];
void *fn_8005C868(Unk_C868 *arg0, s32 arg1, s32 arg2) {
    void *m;
    arg0->unk0x10 = (s32)lbl_802936E8;
    arg0->unk0x0 = arg1;
    arg0->unk0x4 = 1;
    if (arg2 != 0) {
        m = Mem_Alloc2(0x18);
        arg0->unk0x8 = fn_8005D07C(m, 5);
    } else {
        arg0->unk0x8 = arg2;
    }
    return arg0;
}
