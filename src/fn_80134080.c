// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134080-0x8013409C (28B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80134080(CScript *arg0) {
    s32 temp_r0;
    void *temp_r3;

    temp_r3 = (char *)arg0 + 0x14C;
    temp_r0 = arg0->unk0x1E8 * 8;
    *(s32 *)((char *)temp_r3 + temp_r0) = *(s32 *)((char *)temp_r3 + temp_r0) + 1;
}
