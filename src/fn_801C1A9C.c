// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C1A9C-0x801C1AB8 (28B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AC7C4[];
void fn_801C1A9C(Unk_FFAD6788 *arg0, f32 arg1) {
    register char *page __asm__("r9");
    f32 lim;
    __asm__ volatile("lis %0,%1@ha" : "=r"(page) : "s"(lbl_802AC7C4));
    *((f32 *)&arg0->unk0xF0) = arg1;
    __asm__ volatile("lfs %0,%1@l(%2)" : "=f"(lim) : "s"(lbl_802AC7C4), "r"(page));
    if (arg1 > lim) {
        *((f32 *)&arg0->unk0xF0) = lim;
    }
}
