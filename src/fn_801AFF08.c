// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AFF08-0x801AFF7C (116B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void fn_800092B0(Unk_9994C3F5 *, s32);
extern char lbl_802ABD38[];

void fn_801AFF08(Unk_C8FEE62D *arg0, s32 arg1) {
    fn_800092B0((char *)arg0 + 0x18, 2);
    arg0->unk0x14 = (s32)lbl_802ABD38;
    *(s32 *)(arg0->unk0x10 + 0xC) = arg0->unk0xC;
    *(s32 *)(arg0->unk0xC + 0x10) = arg0->unk0x10;
    arg0->unk0xC = (s32)arg0;
    arg0->unk0x10 = (s32)arg0;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
