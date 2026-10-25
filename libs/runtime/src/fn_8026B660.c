// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026B660-0x8026B6DC (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_8030B1C4[];
void fn_8026B614(char *);

void fn_8026B660(u32 arg0, char *arg1, u32 arg2) {
    u32 value;
    s32 index;
    s32 negative;

    value = arg0;
    negative = (s32)value < 0;
    if (negative && arg2 == 10)
        value = -(s32)value;
    index = 0;
    do {
        arg1[index] = lbl_8030B1C4[value % arg2];
        index++;
    } while ((value /= arg2) != 0);
    if (negative)
        arg1[index++] = '-';
    arg1[index] = 0;
    fn_8026B614(arg1);
}
