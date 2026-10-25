// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80160928-0x80160998 (112B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 GetChecksum(CStruct *, s32);

bool fn_80160928(CStruct *arg0, s32 arg1) {
    u32 count;
    u32 i;

    if (arg0 == NULL) {
        return false;
    }
    count = *((u32 *)&arg0->unk0x4);
    for (i = 0; i < count; i++) {
        if (arg1 == GetChecksum((s32)arg0, i)) {
            return true;
        }
    }
    return false;
}
