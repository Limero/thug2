// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80059318-0x8005934C (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad[0x4C40];
    s32 *table;
} Page;

extern char lbl_80364C40[];
void fn_8007C39C(s32);

void fn_80059318(s32 arg0, s32 *arg1) {
    register s32 page __asm__("r10");
    register s32 value __asm__("r0");
    register s32 table __asm__("r9");

    __asm__ volatile("lis %0,%1@ha" : "=r"(page) : "s"(lbl_80364C40));
    value = *arg1;
    table = (s32)((Page *)page)->table;
    __asm__ volatile("" : "+r"(table));
    ((s32 *)table)[arg0] = value;
    fn_8007C39C(arg0);
}
