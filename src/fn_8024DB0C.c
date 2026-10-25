// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024DB0C-0x8024DC14 (264B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8024DB0C(Unk_5B449B03 *arg0, void *arg1, Unk_5B449B03 *arg2, s32 arg3, s32 arg4) {
    s32 s;
    s32 t;
    char *base;
    u8 *tp;
    u8 type;
    s32 i;
    s32 n;
    s16 s2;
    s32 j;
    register s32 dp __asm__("r8");
    register s32 sp __asm__("r10");
    register s32 d3p __asm__("r10");
    register s32 s3p __asm__("r11");
    register s32 i3 __asm__("r9");

    s = arg2->unk0x0 + arg0->unk0x0;
    arg2->unk0x0 = s;
    t = arg3 * 0x1E + 0x28;
    *(s16 *)((char *)arg1 + t) = (s16)s * arg4;
    base = (char *)arg1 + t;
    tp = (u8 *)arg1 + 2;
    type = *(u8 *)(tp + arg3);
    if (type == 1) {
        dp = (s32)base + 0x10;
        sp = (s32)(arg2) + 0x10;
        i = 2;
        n = 7;
        do {
            s2 = (s16)(*(u16 *)(i + (s32)arg2) + *(u16 *)(i + (s32)arg0));
            *(u16 *)(i + (s32)arg2) = s2;
            *(u16 *)(i + (s32)base) = s2;
            i += 2;
            *(u16 *)dp = *(u16 *)sp;
            sp += 0x10;
            dp += 2;
        } while (--n != 0);
        return;
    }
    if (type == 2) {
        dp = (s32)base + 0x10;
        i = 2;
        j = 0x10;
        n = 7;
        do {
            s2 = (s16)(*(u16 *)(j + (s32)arg2) + *(u16 *)(i + (s32)arg0));
            *(u16 *)(j + (s32)arg2) = s2;
            *(u16 *)dp = s2;
            j += 0x10;
            dp += 2;
            *(u16 *)(i + (s32)base) = *(u16 *)(i + (s32)arg2);
            i += 2;
        } while (--n != 0);
        return;
    }
    d3p = (s32)base + 0x10;
    s3p = (s32)(arg2) + 0x10;
    i3 = 2;
    n = 7;
    do {
        *(u16 *)(i3 + (s32)base) = *(u16 *)(i3 + (s32)arg2);
        i3 += 2;
        *(u16 *)d3p = *(u16 *)s3p;
        s3p += 0x10;
        d3p += 2;
    } while (--n != 0);
}
