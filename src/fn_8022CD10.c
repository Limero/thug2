// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CD10-0x8022CD70 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80012098(s32, s32);
void fn_8022CD10(Unk_C8FEE62D *arg0) {
    s32 field;

    field = arg0->unk0x14;
    if (field != 0) {
        fn_80012098(field, 3);
        arg0->unk0x14 = 0;
    }
    field = arg0->unk0x10;
    if (field != 0) {
        fn_80012098(field, 3);
        arg0->unk0x10 = 0;
    }
}
