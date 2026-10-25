// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022335C-0x80223394 (56B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_8013F65C(Unk_C7387A53 *, s32);

bool fn_8022335C(CStruct *arg0) {
    void *tbl = *(void **)arg0;
    fn_8013F65C(arg0->unk0x10, *(s8 *)tbl * 1000);
    return true;
}
