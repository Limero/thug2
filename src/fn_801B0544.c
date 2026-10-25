// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0544-0x801B05B8 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80009950(s32);
void fn_801B0170(CStruct *);
void *fn_801B0544(CStruct *arg0, s32 arg1) {
    void *base;
    void *walker;
    s32 i;
    s32 sz;

    sz = arg1 * 0x14;
    arg0->unk0x4 = arg1;
    i = arg1 - 1;
    base = (void *)(fn_80009950(sz + 8) + 8);
    *(s32 *)((char *)base - 8) = arg1;
    walker = base;
    if (arg1 != 0) {
        do {
            fn_801B0170(walker);
            walker = (void *)((char *)walker + 0x14);
        } while (--i != -1);
    }
    arg0->unk0x8 = (s32)base;
    return arg0;
}
