// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80102C54-0x80102CB8 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern void *fn_80105B44(CStruct *arg0);
extern void *fn_80105B90(CStruct *arg0);

s32 fn_80102C54(Unk_1D62F22E *arg0) {
    s32 count;
    s32 right_count;
    void *kids;

    if ((arg0->unk0x3 & 3) == 3) {
        return 1;
    }
    kids = (char *)arg0 + 4;
    count = fn_80102C54(fn_80105B44(kids));
    right_count = fn_80102C54(fn_80105B90(kids));
    right_count++;
    return count + right_count;
}
