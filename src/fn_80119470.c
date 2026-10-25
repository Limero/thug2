// range 0x80119470-0x80119498 (0x28). Byte-identical.
// Identification: global state test — reads lbl_802FFE50; returns 1 if it
// equals 2, otherwise booleanizes whether it equals 6 (xor/subfic/adde
// idiom, recipe 250).
#include "types.h"
extern char lbl_802FFE50[];
s32 fn_80119470(void) {
    s32 x = *(s32 *)lbl_802FFE50;
    if (x == 2)
        return 1;
    return x == 6;
}
