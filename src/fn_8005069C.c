// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005069C-0x80050720 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void memset(s32, s32, s32);
s32 fn_800532B4(CStruct *, s32 *, s32);
extern char lbl_80364620[];
void fn_8005069C(CStruct *arg0, s32 arg1) {
    register s32 n __asm__("r3");
    s32 sp8;

    *(volatile s32 *)&arg0->unk0x0 = 0;
    sp8 = arg1;
    n = arg1;
    *(volatile s32 *)&arg0->unk0x8 = arg0->unk0x8 + 1;
    *(volatile s32 *)&arg0->unk0x4 = n;
    if (n != 0) {
        arg0->unk0x0 = (s32)Mem_Alloc(n * 4);
        memset(arg0->unk0x0, 0, arg0->unk0x4 * 4);
    }
    fn_800532B4(lbl_80364620, &sp8, arg0);
}
