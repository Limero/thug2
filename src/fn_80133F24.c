// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80133F24-0x80133F8C (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029EF00[];
void fn_801323D4(CScript *, s32);
void fn_80133F24(CScript *arg0, s32 arg1) {
    s32 temp_r0;
    s32 *var_r9;
    s32 *var_r10;

    temp_r0 = arg0->unk0x1E8 + 1;
    arg0->unk0x1E8 = temp_r0;
    if (temp_r0 > 0x13) {
        fn_801323D4(arg0, (s32)lbl_8029EF00);
        return;
    }
    var_r9 = (s32 *)((char *)arg0 + 0x148);
    var_r10 = (s32 *)((char *)arg0 + 0x14C);
    *(s32 *)((char *)var_r9 + (temp_r0 * 8)) = arg1;
    *(s32 *)((char *)var_r10 + (arg0->unk0x1E8 * 8)) = 0;
    arg0->unk0x1EC = 1;
}
