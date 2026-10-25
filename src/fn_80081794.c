// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80081794-0x80081920 (396B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 fn_80081794(s32 arg0) {
    u32 swv1;
    s32 var_r9;

    var_r9 = 0;
    switch (swv1 = arg0) {                                 
    case QB_BLEND:
        var_r9 = 5;
        break;
    case 0x2E58C18:
        var_r9 = 1;
        break;
    case QB_SUB:
    case QB_SUBTRACT:
        var_r9 = 3;
        break;
    case QB_MODULATE:
        var_r9 = 7;
        break;
    case QB_BRIGHTEN:
        var_r9 = 9;
        break;
    case QB_FIXBLEND:
        var_r9 = 6;
        break;
    case QB_FIXADD:
        var_r9 = 2;
        break;
    case 0xEEA99FF:
    case 0xD7A749A:
        var_r9 = 4;
        break;
    case QB_FIXMODULATE:
        var_r9 = 8;
        break;
    case QB_FIXBRIGHTEN:
        var_r9 = 0xA;
        break;
    case QB_NONE:
    case QB_DIFFUSE:
        var_r9 = 0;
        break;
    }
    return var_r9;
}
