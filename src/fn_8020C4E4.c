// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020C4E4-0x8020C500 (28B). Byte-identical.
#include "types.h"
void fn_8020C4E4(s32 arg0, s32 arg1, f32 farg1) {
    s32 *ptra = (s32 *)((char *)arg0 + 0xA04);
    f32 *ptrb = (f32 *)((char *)arg0 + 0x9AC);
    s32 idx = arg1 * 4;
    *(s32 *)((char *)ptra + idx) = 0;
    *(f32 *)((char *)ptrb + idx) = farg1;
}
