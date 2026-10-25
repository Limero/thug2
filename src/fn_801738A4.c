// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801738A4-0x80173910 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80173538(Unk_839CD594 * arg0, s32 arg1);

void fn_801738A4(Unk_839CD594 *arg0, Unk_C8FEE62D *arg1, s32 arg2, s32 arg3) {
    s32 var_r3;
    Unk_C6B642AC *temp_r9;

    var_r3 = arg2;
    if ((var_r3 != 0) || (var_r3 = fn_80173538(arg0, arg1->unk0x18), ((var_r3 == 0) == 0))) {
        temp_r9 = arg1->unk0x8;
        ((s32 (*)(void *, void *, void *))temp_r9->unk0x84)((char *)arg1 + temp_r9->unk0x80, var_r3, arg3);
    }
}
