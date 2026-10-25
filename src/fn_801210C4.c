// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801210C4-0x80121178 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8038F0C0[];
extern s32 lbl_80302F04;
extern s32 lbl_8039B8C0[];
extern s32 OSDisableInterrupts(void);
extern void AXFreeVoice(s32);
extern void OSRestoreInterrupts(s32);

void fn_801210C4(s32 arg0, s32 arg1) {
    char *base;
    char *p1;
    char *p2;
    char *p3;
    s32 temp;
    s32 irq;

    base = lbl_8038F0C0;
    temp = arg0 * 0x21C;
    p1 = base + 0x20C;
    p2 = base + 0x218;
    lbl_8039B8C0[arg0] = 0;
    *(s32 *)(p2 + temp) = 0;
    if (*(s32 *)(p1 + temp) != 0) {
        irq = OSDisableInterrupts();
        AXFreeVoice(*(s32 *)(p1 + temp));
        *(s32 *)(p1 + temp) = 0;
        p3 = base + 0x28;
        *(s32 *)(p3 + temp) = (*(s32 *)(p3 + temp) + 1) & 7;
        OSRestoreInterrupts(irq);
        lbl_80302F04 = lbl_80302F04 & ~(0x2000 << arg0);
        lbl_80302F04 = lbl_80302F04 & ~(0x200 << arg0);
    }
}
