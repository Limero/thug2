// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005C8D0-0x8005C944 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
typedef struct { u32 unk0x0; u16 unk0x4; char pad0x6[2]; s32 unk0x8; char pad0xC[4]; s32 unk0x10; } Unk_C8D0;
unsigned int fn_8000A778(const char *);
void *fn_8005D07C(void *, s32);
extern char lbl_802936E8[];
void *fn_8005C8D0(Unk_C8D0 *arg0, const char *arg1, s32 arg2) {
    void *m;

    arg0->unk0x10 = (s32)lbl_802936E8;
    arg0->unk0x0 = fn_8000A778(arg1);
    arg0->unk0x4 = 1;
    if (arg2 != 0) {
        m = Mem_Alloc2(0x18);
        arg0->unk0x8 = (s32)fn_8005D07C(m, 5);
    } else {
        arg0->unk0x8 = arg2;
    }
    return arg0;
}
