// Auto-generated from tools/gen_leaves.py
// range 0x8018E514-0x8018E520 (12B). Byte-identical.
#include "types.h"
s32 fn_8018E514(void *o) {
    struct S { unsigned pad : 9; unsigned f : 1; };
    return ((struct S *)((char *)o + 0x70))->f;
}
