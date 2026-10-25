// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801921C0-0x80192230 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801921C0(Unk_756F5292 *arg0) {
    s32 var_r3;
    s32 zero;
    Unk_5BE2D2B7 *temp_r9;

    zero = 0;
    arg0->unk0x80 = zero;
    arg0->unk0x7C = zero;
    arg0->unk0x70 = (s32) (arg0->unk0x70 & QB_UNKNOWN_0xDFFFFFFF);
    temp_r9 = arg0->unk0x14;
    if (temp_r9->unk0xAC((char *)arg0 + temp_r9->unk0xA8) == 0) {
        var_r3 = 0;
    } else {
        arg0->unk0x78 = zero;
        var_r3 = 1;
    }
    return var_r3;
}
