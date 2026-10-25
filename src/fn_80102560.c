// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80102560-0x80102578 (24B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80102560(CStruct *arg0, s32 *arg1) {
    arg0->unk0x8 = arg1;
    if (arg1 != NULL) {
        arg0->unk0x0 = (s32) *arg1;
    }
}
