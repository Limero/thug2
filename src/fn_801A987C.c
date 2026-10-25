// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A987C-0x801A98F0 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_801A9C1C(void *, void (*)(void *, s32), s32);
extern void fn_801A96FC(Unk_C8FEE62D *, CStruct *);
s32 fn_801A987C(s32 arg0, s32 arg1) {
    s32 sp[4];
    u32 i;
    sp[2] = arg1;
    sp[1] = 0;
    i = 0;
    sp[3] = arg0;
    do {
        ((u8 *)sp[2])[i] = 0;
        sp[0] = i;
        fn_801A9C1C((void *)(arg0 + 8), fn_801A96FC, &sp[0]);
        i++;
    } while (i <= 7U);
    return sp[1] + 8;
}
