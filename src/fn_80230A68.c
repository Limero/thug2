// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80230A68-0x80230B18 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802309C8(s32, s32, s32 *, s32 *);
void fn_80230A68(s32 arg0, void *arg1, s32 arg2) {
    s32 sp8;
    s32 spC;
    s32 i;
    s32 end;
    s32 t0;
    s32 zero;
    s32 off;
    char *p;

    sp8 = 0;
    spC = 0;
    fn_802309C8(arg0, arg2, &sp8, &spC);
    t0 = spC;
    i = sp8;
    if (i <= t0) {
        __asm__("mr %0,%1" : "=&r"(end) : "r"(t0));
        zero = 0;
        __asm__("" : "=r"(off) : "r"(i * 0x28 + 0xB4));
        p = (char *)(off + arg0);
        do {
            if (((*(u8 *)p == ((u8 *)arg1)[0]) &&
                 (((Unk_1D62F22E_2 *)p)->unk0x1 == ((u8 *)arg1)[1])) &&
                (((Unk_1D62F22E_2 *)p)->unk0x2 == ((u8 *)arg1)[2])) {
                ((Unk_1D62F22E_2 *)p)->unk0x8 = zero;
            }
            i += 1;
            p += 0x28;
        } while (i <= end);
    }
}
