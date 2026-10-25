// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80250E6C-0x80250EAC (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80250E6C(CStruct *arg0, s32 arg1) {
    register s32 total __asm__("r5");
    s32 lim;
    register s32 w_a __asm__("r10");
    register s32 pp __asm__("r11");
    register s32 w_b __asm__("r12");

    total = *((volatile s32 *)&arg0->unk0x8) + arg1;
    lim = 0x20;
    if (total < lim) {
        *((volatile s32 *)&arg0->unk0x8) = total;
        return;
    }
    w_a = *((volatile s32 *)&arg0->unk0x4);
    *((volatile s32 *)&arg0->unk0x0) = w_a;
    pp = *((volatile s32 *)&arg0->unk0xC);
    w_b = *((volatile s32 *)&((Unk_9994C3F5 *)pp)->unk0x8);
    *((volatile s32 *)&arg0->unk0x4) = w_b;
    *((volatile s32 *)&arg0->unk0xC) = pp + 4;
    *((volatile s32 *)&arg0->unk0x8) = total - 0x20;
}
