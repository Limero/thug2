// Auto-generated from tools/gen_leaves.py
// range 0x8018EDA4-0x8018EDB0 (12B). Byte-identical.
#include "types.h"
s32 fn_8018EDA4(void *o) {
    struct S { unsigned pad : 7; unsigned f : 1; };
    return ((struct S *)((char *)o + 0x70))->f;
}
