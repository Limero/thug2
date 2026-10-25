// Carved from the 0x8025D010-0x8025DF74 gap.
// range 0x8025DAD4-0x8025DAF4 (32B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Clamp: 0x52100 when arg0 > 0x5705FFFF, else 0. The if/return form (not
// the ternary) is what emits want's cmpw/lis/ori/bgtlr/li/blr sequence.
// ProDG-compiled (stock game flags).
#include "types.h"

s32 fn_8025DAD4(s32 arg0) {
    if (arg0 > 0x5705FFFF) {
        return 0x52100;
    }
    return 0;
}
