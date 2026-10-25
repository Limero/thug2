// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198C20-0x80198CD0 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80199850(Unk_9994C3F5 *);
s32 fn_80198C20(s32 arg0) {
    register s32 base __asm__("r8");
    register s32 p __asm__("r9");
    register u32 best __asm__("r10");
    register s32 n __asm__("r11");
    s32 t;

    base = (s32)arg0 + 0xC;
    best = 0U;
outer:
    p = ((Unk_1D62F22E_2 *)base)->unk0xC;
    n = 0;
    for (;;) {
        if (((Unk_4C649A8C *)p)->unk0x4 == -1) {
            p = 0;
        }
        if (p == 0) {
            break;
        }
        p = ((Unk_41EA2015 *)p)->unk0xC;
        n++;
    }
    __asm__("" : "+r"(p));
    if (best < n) {
        p = ((Unk_1D62F22E_2 *)base)->unk0xC;
        n = best;
        goto check;
        for (;;) {
            if (--n == -1) {
                goto found;
            }
            p = ((Unk_41EA2015 *)p)->unk0xC;
        check:;
            if (((Unk_4C649A8C *)p)->unk0x4 == -1) {
                p = 0;
            }
            if (p != 0) {
                continue;
            }
            break;
        }
        __asm__("" : "+r"(p));
        p = 0;
found:
        t = ((Unk_4C649A8C *)p)->unk0x4;
        if (t != 0) {
            return fn_80199850(t);
        }
        best++;
        goto outer;
    }
    return 0;
}
