// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80145BB4-0x80145C14 (96B). Byte-identical.
#include "types.h"
extern bool lbl_8037B7A4;
void fn_80017C14(void);
void fn_8001033C(void);
// This is the C entry point `main`, called from `__start` after CRT setup.
// (Cannot be named `main` in C: ngccc injects a `bl __main` ctor call.)
void fn_80145BB4(void) {
    lbl_8037B7A4 = 1;
    __asm__ volatile(
        "li 3, 4\n\toris 3, 3, 4\n\tmtspr 0x392, 3\n\t"
        "li 3, 5\n\toris 3, 3, 5\n\tmtspr 0x393, 3\n\t"
        "li 3, 6\n\toris 3, 3, 6\n\tmtspr 0x394, 3\n\t"
        "li 3, 7\n\toris 3, 3, 7\n\tmtspr 0x395, 3\n\t"
        ::: "r3");
    fn_80017C14();
    fn_8001033C();
}
