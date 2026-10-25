// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022A860-0x8022A8E0 (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8013F764(void *);

void fn_8022A860(CScript *arg0, s32 arg1) {
    volatile s32 sp8;
    register s32 p9 __asm__("r9");
    register s32 two __asm__("r11");

    if ((arg0->unk0x1C != NULL) && (fn_8013F764((void *)(arg0->unk0x1C)) != 0)) {
        if (arg1 != 0) {
            arg0->unk0x1DC = arg1;
        }
        p9 = arg0->unk0x1C;
        sp8 = 1;
        two = 2;
        *(s32 *)((char *)(void *)p9 + (s32)0x68) = (s32) (*(s32 *)((char *)(void *)p9 + (s32)0x68) & QB_UNKNOWN_0xFFFFFFFE);
        sp8 = two;
        p9 = arg0->unk0x1C;
        *(s32 *)((char *)(void *)p9 + (s32)0x68) = (s32) (*(s32 *)((char *)(void *)p9 + (s32)0x68) | 2);
    }
}
