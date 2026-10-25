// Auto-generated from tools/gen_leaves.py
// range 0x800D68AC-0x800D68B8 (12B). Byte-identical.
#include "types.h"
s32 fn_800D68AC(void *o) {
    struct S { unsigned pad : 22; unsigned f : 1; };
    return ((struct S *)((char *)o + 0x20))->f;
}
