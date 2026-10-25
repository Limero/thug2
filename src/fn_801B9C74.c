// Auto-generated from tools/gen_leaves.py
// range 0x801B9C74-0x801B9C80 (12B). Byte-identical.
#include "types.h"
s32 fn_801B9C74(void *o) {
    struct S { unsigned pad : 30; unsigned f : 1; };
    return ((struct S *)((char *)o + 0x24))->f;
}
