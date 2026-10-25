// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E660-0x8005E6C8 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8005C5F0(s32);
s32 fn_8005C5BC(s32);
void fn_8005E660(Unk_838B6CE3 *arg0, s32 arg1) {
    Unk_89391A04 *temp_r9;

    arg0->unk0x0 = arg1;
    if (arg1 != 0) {
        arg0->unk0x2C = fn_8005C5BC(arg1);
        arg0->unk0x2E = fn_8005C5F0(arg1);
    }
    temp_r9 = arg0->unk0x4C;
    temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20);
}
