// Auto-generated from tools/gen_leaves.py
// range 0x8018E3B8-0x8018E3C4 (12B). Byte-identical.
#include "types.h"
s32 fn_8018E3B8(void *o) {
    struct S { unsigned pad : 4; unsigned f : 1; };
    return ((struct S *)((char *)o + 0x70))->f;
}
