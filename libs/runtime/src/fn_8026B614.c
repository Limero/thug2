// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026B614-0x8026B660 (76B). Byte-identical.
#include "types.h"

void fn_8026B614(char *arg0) {
    s32 i;
    s32 j;
    char a;
    char b;

    i = 0;
    while (arg0[i] != '\0')
        i++;
    j = 0;
    i--;
    while (j < i) {
        a = arg0[i];
        b = arg0[j];
        arg0[j] = a;
        arg0[i] = b;
        j++;
        i--;
    }
}
