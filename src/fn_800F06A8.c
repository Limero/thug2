// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F06A8-0x800F0740 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum(void *, s32);
void GetArray(s32, s32, void *, s32);
s32 fn_800F0F84(s32, s32);
bool fn_800F06A8(s32 arg0, s32 arg1) {
    void *sp8;
    s32 count;
    s32 i;

    sp8 = NULL;
    GetArray(arg0, QB_LINKS, &sp8, 0);
    if (sp8 == NULL) {
        return false;
    }
    count = ((CStruct *)sp8)->unk0x4;
    for (i = 0; i < count; i++) {
        if (arg1 == fn_800F0F84(GetChecksum(sp8, i), 1)) {
            return true;
        }
    }
    return false;
}
