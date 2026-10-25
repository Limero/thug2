// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802569D8-0x80256A54 (124B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80256458(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 (*arg4)(s32, s32, s32, s32));
extern s32 fn_802584C0(CStruct * arg0, Unk_D42E3F3A * arg1, s32 arg2, s32 arg3);

// MATCHED @ 0x802569D8 size=0x7C (byte-exact, reloc-masked)
s32 Vtable0x8030804C_m4(s32 arg0, void *arg1, s32 *arg2, s32 *arg3, s32 arg4) {
    register s32 count __asm__("r10");
    s32 off;
    s32 ctr;
    s32 *walker;

    count = 0;
    if (count < arg4) {
        ctr = arg4;
        off = 0;
        walker = arg2;
        do {
            if (*(s32 *)((char *)(off + (s32)arg3)) != 0) {
                count += 1;
                *walker = *(s32 *)((char *)(off + (s32)arg2));
                walker += 1;
            }
            off += 4;
        } while (--ctr != 0);
    }
    return count != 0 ? fn_80256458(arg0, (void *)arg1, arg2, count, fn_802584C0) : 0;
}
