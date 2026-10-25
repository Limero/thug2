// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80253FB8-0x80253FF4 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80253FB8(Unk_C8FEE62D *arg0, s32 arg1) {
    if ((arg1 != 0) && ((s32) (arg0->unk0x18 + arg1) > (s32) arg0->unk0x14)) {
        return -0x83;
    }
    arg0->unk0x18 = (s32) (arg0->unk0x18 + arg1);
    return 0;
}
