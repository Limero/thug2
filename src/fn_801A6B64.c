// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6B64-0x801A6B80 (28B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801A6B64(Unk_93C2DF4D *arg0, s32 arg1) {
    s32 var_r4;
    s32 scaled;
    s32 *arr;

    var_r4 = arg1;
    if (var_r4 == -1) {
        var_r4 = arg0->unk0x630;
    }
    scaled = var_r4 * 4;
    arr = (s32 *)((char *)arg0 + (s32)0x63C);
    return *(s32 *)((char *)arr + scaled);
}
