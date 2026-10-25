// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFF44-0x800EFF9C (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 fn_800F13F4(s32 arg0, void *arg1, s32 arg2);
extern s32 fn_800EFD38(Unk_5B449B03 * arg0, u16 * arg1);

s32 fn_800EFF44(CStruct *arg0, s32 arg1, s16 *arg2) {
    s32 sp8;
    s32 r;

    sp8 = arg1;
    r = fn_800F13F4(arg0->unk0x4, &sp8, 1);
    if (r != 0) {
        return fn_800EFD38(r, arg2);
    }
    *arg2 = (s16)r;
    return 0;
}
