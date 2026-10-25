// Auto-generated from tools/gen_leaves.py
// range 0x8018ECE8-0x8018ECF4 (12B). Byte-identical.
#include "types.h"
s32 fn_8018ECE8(void *o) {
    struct S { unsigned pad : 10; unsigned f : 1; };
    return ((struct S *)((char *)o + 0x70))->f;
}
