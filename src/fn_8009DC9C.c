// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DC9C-0x8009DE1C (384B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 fn_8009DC9C(u32 arg0) {
    switch (arg0) {                                 
    case QB_AUTO_BRIGHTNESS:
        return 0;
    case 0x564ACD:
        return 1;
    case QB_AUTO_GAIN:
        return 2;
    case QB_AUTO_WHITE_BALANCE:
        return 3;
    case QB_BACKLIGHT_COMP:
        return 4;
    case QB_BRIGHTNESS:
        return 5;
    case QB_EXPOSURE:
        return 6;
    case QB_GAIN:
        return 7;
    case QB_MIRROR:
        return 8;
    case QB_REDBLUE_GAIN:
        return 9;
    case QB_SATURATION:
        return 0xA;
    case QB_YUV:
        return 0xB;
    case QB_LED:
        return 0xC;
    default:
        return 0xC;
    }
}
