// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80108158-0x801081D8 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void fn_80006C60(void);
extern s32 fn_801081D8(Unk_F98363B0 *);
s32 fn_80108158(Unk_F98363B0 *arg0, s32 unused) {
    s32 outer;
    s32 next_outer;
    s32 inner;

    fn_80006C60();
    outer = 31;
    do {
        next_outer = outer - 1;
        inner = 1;
delay_1:
        if (inner != 0) {
            inner -= 1;
            goto delay_1;
        }
        outer = next_outer;
        __asm__("" : "+r"(outer));
    } while (outer != -1);
    outer = 31;
    do {
        next_outer = outer - 1;
        inner = 1;
delay_2:
        if (inner != 0) {
            inner -= 1;
            goto delay_2;
        }
        outer = next_outer;
        __asm__("" : "+r"(outer));
    } while (outer != -1);
    fn_801081D8(arg0);
    return arg0;
}
