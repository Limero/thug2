// Auto-generated from tools/gen_leaves.py
// range 0x8018D0EC-0x8018D0F8 (12B). Byte-identical.
#include "types.h"
s32 fn_8018D0EC(void *o) {
    struct S { unsigned pad : 1; unsigned f : 1; };
    return ((struct S *)((char *)o + 0x70))->f;
}
