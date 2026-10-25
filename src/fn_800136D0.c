// range 0x800136D0-0x800136FC (0x2C). Byte-identical.
// Identification: reset + notify — zeroes lbl_802FFF0C, then calls
// fn_800150EC (unmatched).
#include "types.h"
extern char lbl_802FFF0C[];
extern void fn_800150EC(void);
void fn_800136D0(void) {
    *(s32 *)lbl_802FFF0C = 0;
    fn_800150EC();
}
