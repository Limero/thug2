// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F1838-0x801F1940 (264B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
s32 fn_801F1838(s32 arg0, s32 arg1) {
    register s32 var_r3 __asm__("r3");

    var_r3 = 0;

    if (arg0 != QB_COMBO) {
        if (arg0 == QB_SKATE) {
            switch (arg1) {
            case 0:
                return QB_LETTER_S;
            case 1:
                return QB_LETTER_K;
            case 2:
                return QB_LETTER_A;
            case 3:
                return QB_LETTER_T;
            case 4:
                return QB_LETTER_E;
            }
        }
    } else {
        switch (arg1) {
        case 0:
            return QB_COMBO_C;
        case 1:
            return QB_COMBO_O;
        case 2:
            return QB_COMBO_M;
        case 3:
            return QB_COMBO_B;
        case 4: {
            s32 t4;

            __asm__("" : "=r"(t4) : "r"(QB_COMBO_O));
            return t4;
        }
        }
    }
    return var_r3;
}
