// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B33EC-0x800B34C0 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80305F9C;
s32 fn_8021D358(s32, u16);
s32 fn_8022986C(void *);
void fn_80137CB4(void *);
s32 fn_8022A9D0(void *);
s32 fn_8021B55C(s32, s32);
void fn_8013DE78(s32, void *);
void fn_80062250(s32, s32, s32);
bool fn_800B33EC(void *arg0, s32 arg1, s8 arg2, s32 arg3) {
    s32 sp8[12];
    u8 *tb;
    void *p;
    s32 r29;
    s32 idx;
    s32 f18;
    register s32 k8 __asm__("r8");
    register s32 k3e __asm__("r10");
    if (arg3 != 0) {
        r29 = lbl_80305F9C;
        p = fn_8021D358(r29, *(u16 *)((char *)*(s32 *)((char *)arg0 + 0xC) + 0x1A));
        if (p != 0) {
            if (fn_8022986C(p) != 0) {
                fn_80137CB4(sp8);
                idx = fn_8021B55C(r29, fn_8022A9D0(p));
                tb = (u8 *)((char *)sp8 + 0x28);
                tb[5] = arg2;
                *(s32 *)((char *)sp8 + 0x28) = arg1;
                f18 = *(s32 *)((char *)*(s32 *)((char *)arg0 + 0xC) + 0x18);
                tb[4] = (u8)f18;
                k8 = 8;
                *(void **)((char *)sp8 + 4) = tb;
                *(u16 *)((char *)sp8 + 2) = (u16)k8;
                k3e = 0x3E;
                *(u8 *)((char *)sp8 + 0) = (u8)k3e;
                fn_8013DE78(idx, sp8);
            }
        }
    }
    if (*(s32 *)((char *)arg0 + 0x210) != 0) {
        fn_80062250(*(s32 *)((char *)arg0 + 0x210), arg1, arg2);
    }
    return true;
}
