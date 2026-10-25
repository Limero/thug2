// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800448D0-0x80044960 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800447B4(void);
s32 fn_80044614(Unk_31DE137E *, u8 *, s32);
void fn_800445E8(void *);
bool fn_800448D0(Unk_31DE137E *arg0) {
    char buf[0x200];
    s32 n;
    s32 j;
    register s32 b __asm__("r4");
    register s32 i __asm__("r9");

    n = fn_800447B4();
    if (n == 0)
        return false;
    fn_80044614(arg0, buf, 0x200);
    __asm__("addi %0,1,8\n\taddi %1,%2,-1"
            : "=&r"(b), "=&r"(i)
            : "r"(n));
    if (n > 1 && ((u8 *)b)[i] == 0x5C) {
        j = n - 2;
        if (((u8 *)b)[j] == 0x5C)
            ((u8 *)b)[j] = 0;
    }
    ((u8 *)b)[i] = 0;
    fn_800445E8(arg0);
    return true;
}
