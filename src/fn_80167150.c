// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80167150-0x801671A0 (80B). Byte-identical.
#include "types.h"
extern s32 s_get_platforms_block_size(void);
s32 s_round_up_to_platforms_block_size(s32 arg0) {
    s32 x = s_get_platforms_block_size();
    s32 q = arg0 / x;
    if (arg0 != q * x) {
        return (q + 1) * x;
    }
    return arg0;
}

