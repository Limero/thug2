// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E300-0x8005E3F4 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 fn_80128E34(s32, s32, void *, s32);
void fn_8005E08C(s32);
bool fn_8005E300(s32 arg0) {
    u32 sp8;
    fn_80128E34(arg0, 0, &sp8, 1);
    switch (sp8) {
    case QB_ONE_CAMERA:
        fn_8005E08C(0);
        break;
    case QB_SPLIT_VERTICAL:
        fn_8005E08C(1);
        break;
    case QB_SPLIT_HORIZONTAL:
        fn_8005E08C(2);
        break;
    case QB_SPLIT_QUARTERS:
        fn_8005E08C(3);
        break;
    case QB_HORSE1:
        fn_8005E08C(4);
        break;
    case QB_HORSE2:
        fn_8005E08C(5);
        break;
    }
    return true;
}
