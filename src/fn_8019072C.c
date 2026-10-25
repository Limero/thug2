// Auto-generated from tools/gen_leaves.py
// range 0x8019072C-0x80190738 (12B). Byte-identical.
#include "types.h"
s32 fn_8019072C(void *o) {
    struct S { unsigned pad : 12; unsigned f : 1; };
    return ((struct S *)((char *)o + 0x70))->f;
}
