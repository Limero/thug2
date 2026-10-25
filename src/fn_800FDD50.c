// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FDD50-0x800FDD90 (64B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_800FDD50(Unk_7A62D47E *arg0, void *arg1) {
    register char *base __asm__ ("r9");
    Unk_C1F9F519 *mid;
    arg0->unk0x8 = (s32)arg1;
    if ((s32)arg1 != 0) {
        *(s32 *)arg0 = *(s32 *)arg1;
    }
    base = *((volatile char * *)&arg0->unk0x8);
    __asm__("" : "=r"(mid) : "r"(base + 0x10));
    arg0->unk0xA8 = ((Unk_C1F9F519 *)base)->unk0x10;
    arg0->unk0xB0 = ((Unk_C1F9F519 *)base)->unk0x18;
    arg0->unk0xB8 = mid->unk0x10;
    arg0->unk0xC0 = mid->unk0x18;
}