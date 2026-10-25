// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2010-0x800F206C (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern u8 lbl_8029B370;
void fn_800F1F74(s32, u8 *);
void Script_GenerateCRC(u8 *);
void *memset(void *, s32, s32, ...);
void fn_800F2010(s32 arg0) {
    register s32 d __asm__("r3");
    register s32 n __asm__("r5");
    register s32 z __asm__("r4");
    u8 buf[0x100];

    buf[0] = lbl_8029B370;
    d = (s32)&buf[1];
    n = 0xff;
    z = 0;
    __asm__("" : "+r"(d), "+r"(n), "+r"(z));
    memset((void *)d, z, n);
    fn_800F1F74(arg0, buf);
    Script_GenerateCRC(buf);
}
