// range 0x8006EB68-0x8006EB90 (0x28). Byte-identical.
// Identification: global setter + forward — stores arg0 to lbl_80301470,
// then calls fn_80087240(arg0) (matched).
#include "types.h"
extern char lbl_80301470[];
extern void fn_80087240(s32);
void fn_8006EB68(s32 arg0) {
    *(s32 *)lbl_80301470 = arg0;
    fn_80087240(arg0);
}
