// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80170658-0x80170668 (16B). Byte-identical.
#include "types.h"
struct fn_80170658_rec { char _pad[0x18C]; s32 _arr[0x64]; };
s32 fn_80170658(s32 arg0, s32 arg1) {
    return ((struct fn_80170658_rec *)arg0)->_arr[arg1 * 0x64];
}
