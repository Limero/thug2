// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024C5A0-0x8024C5D4 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
// MSL printf-family arg-table builder: records (arg0, arg1) into the
// format base/size tables (lbl_803CA240, lbl_803CA330/34) and bumps the
// entry count. Suggested rename: fn_8024C5A0_printf_arg_record.
#include "types.h"
extern s32 lbl_803CA330;
extern s32 lbl_803CA334;
extern char lbl_803CA240[];
void fn_8024C5A0(s32 arg0, s32 arg1) {
    register s32 n __asm__("r9");
    register s32 basereg __asm__("r11");
    register s32 szreg __asm__("r10");
    char *base;
    char *sizes;
    s32 n1;
    s32 total;
    n = lbl_803CA334;
    basereg = (s32)lbl_803CA240;
    total = lbl_803CA330;
    base = (char *)basereg;
    szreg = basereg + 4;
    sizes = (char *)szreg;
    n1 = n + 1;
    lbl_803CA330 = total + arg1;
    n = n * 8;
    *(s32 *)(sizes + n) = arg1;
    *(s32 *)(base + n) = arg0;
    lbl_803CA334 = n1;
}
