// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80274B4C-0x80274B80 (52B). Byte-identical.
#include "types.h"
extern s32 lbl_8030B860;
extern void fn_80274B80(void);

void fn_80274B4C(void) {
    register s32 fp __asm__("r3");
    fp = (s32)fn_80274B80;
    lbl_8030B860 = fp;
    ((void (*)(void))fp)();
}
