// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026B5B8-0x8026B614 (92B). Byte-identical.
#include "types.h"

s32 fn_8026B5B8(char *arg0, s32 arg1) {
    if (arg1 > 0) {
        arg1--;
        if (arg0[arg1] > '4') {
            do {
                arg0[arg1] = '0';
            } while (--arg1 > 0 && arg0[arg1] == '9');
            if (arg0[arg1] == '9')
                return 0;
            arg0[arg1] = arg0[arg1] + 1;
        }
    }
    return 1;
}
