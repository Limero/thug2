// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80103198-0x80103234 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80105B44(s32 *arg0);
s32 fn_80105B90(s32 *arg0);
bool fn_80103198(Unk_5AA7B5D7 *arg0, s32 arg1, s32 arg2) {
    s32 *p;
    s32 t;

    if (((*(u8 *)((char *)arg0 + 3)) & 3) == 3) {
        arg0->unk0x4 = arg2 + arg0->unk0x4 * 2;
    } else {
        p = (s32 *)arg0;
        t = *++p;
        arg0->unk0x4 = ((t & ~3) + arg1) | (t & 3);
        fn_80103198((Unk_5AA7B5D7 *)fn_80105B44(p), arg1, arg2);
        fn_80103198((Unk_5AA7B5D7 *)fn_80105B90(p), arg1, arg2);
    }
    return true;
}
