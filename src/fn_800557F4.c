// range 0x800557F4-0x8005581C (0x28). Byte-identical.
// Identification: global setter + notify — stores arg0 to lbl_803CAF3C,
// then calls fn_80077790 (matched).
#include "types.h"
extern char lbl_803CAF3C[];
extern void fn_80077790(void);
void fn_800557F4(s32 arg0) {
    *(s32 *)lbl_803CAF3C = arg0;
    fn_80077790();
}
