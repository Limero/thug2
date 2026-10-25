// range 0x800120EC-0x80012110 (36B). Byte-identical.
// Identification: bounds / containment test — returns arg1 in [obj[0], obj[4]).
// Used by fn_8006FBCC to range-check a freshly-allocated object against a
// double-buffered object pool before relinking it. The want shape is the
// branchy form (blt->return 0, speculative li r3,1 + bltlr->return 1); the
// naive `A && B` boolean compiles branchless (subfc/subfe/neg), so the two
// comparisons must be written as nested ifs with the inner `return 1`.
#include "types.h"
#include "structs.h"
bool fn_800120EC(CStruct *arg0, u32 arg1) {
    if (arg1 >= *(u32 *)arg0) {
        if (arg1 < *((u32 *)&arg0->unk0x4)) {
            return true;
        }
    }
    return false;
}