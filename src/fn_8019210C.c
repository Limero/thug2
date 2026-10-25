// Auto-generated from tools/gen_leaves.py
// range 0x8019210C-0x80192118 (12B). Byte-identical.
#include "types.h"
s32 fn_8019210C(void *o) {
    struct S { unsigned pad : 2; unsigned f : 1; };
    return ((struct S *)((char *)o + 0x70))->f;
}
