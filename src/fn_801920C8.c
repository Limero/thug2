// Auto-generated from tools/gen_leaves.py
// range 0x801920C8-0x801920D4 (12B). Byte-identical.
#include "types.h"
s32 fn_801920C8(void *o) {
    struct S { unsigned pad : 8; unsigned f : 1; };
    return ((struct S *)((char *)o + 0x70))->f;
}
