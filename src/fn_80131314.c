// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131314-0x80131334 (32B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80131314(Unk_FFAD6788 *arg0) {
    s32 temp_r0;

    if (arg0 != NULL) {
        temp_r0 = arg0->unk0xCC;
        if (temp_r0 < 0) {
            arg0->unk0xCC = (s32) (temp_r0 & QB_UNKNOWN_0xDFFFFFFF);
        }
    }
}
