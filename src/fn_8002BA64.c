// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002BA64-0x8002BAC8 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8002BA5C(CStruct *, s32);
s32 fn_8002BA64(CStruct *arg0, s32 arg1) {
    s32 var_r3;
    Unk_4E705049 *temp_r9;

    var_r3 = 0;
    if ((s32) arg0->unk0x4 != 0) {
        fn_8002BA5C(arg0, 0);
        temp_r9 = arg0->unk0x8;
        var_r3 = ((s32 (*)(void *, void *))temp_r9->unk0x1C)((char *)arg0 + temp_r9->unk0x18, arg1);
    }
    return var_r3;
}