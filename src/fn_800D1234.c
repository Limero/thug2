// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D1234-0x800D128C (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800D1234(CScript *arg0, s32 arg1, s32 arg2) {
    Unk_4E705049 *temp_r9;

    if (arg1 == QB_OBJ_LOCKTOOBJECT) {
        temp_r9 = *((void * *)&arg0->unk0x18);
        ((s32 (*)(void *, s32))temp_r9->unk0x1C)((char *)arg0 + temp_r9->unk0x18, arg2);
        return 1;
    }
    return 2;
}
