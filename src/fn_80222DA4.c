// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80222DA4-0x80222DF4 (80B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 fn_801F672C(void);
s32 fn_801F5188(s32, s32, void *, s32);

void fn_80222DA4(Unk_B8D659B7 *arg0, s32 arg1) {
    arg0->unk0x1978 = arg1;
    arg0->unk0x204 = arg1;
    arg0->unk0x1974 =
        fn_801F5188(fn_801F672C(), arg1, (char *)arg0 + 0x208, 0x1770) + 4;
}
