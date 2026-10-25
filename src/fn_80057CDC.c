// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057CDC-0x80057D30 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80057CDC(void *arg0, CStruct *arg1) {
    register s32 r4 asm("r4");
    volatile u8 *b3 = (volatile u8 *)((char *)arg0 + 3);
    volatile u8 *b0 = (volatile u8 *)((char *)arg0 + 0);
    volatile u8 *b1 = (volatile u8 *)((char *)arg0 + 1);
    volatile u8 *b2 = (volatile u8 *)((char *)arg0 + 2);
    r4 = arg1->unk0x10;
    if (r4 != 0) {
        fn_8005F100(arg0);
    } else {
        *b3 = (u8) r4;
        *b0 = (u8) r4;
        *b1 = (u8) r4;
        *b2 = (u8) r4;
    }
    return arg0;
}
