// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F1B30-0x800F1B5C (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Elem1B30;

typedef struct {
    char pad0[0x10008];
    s32 count;
    Elem1B30 arr[1];
} S1B30;

s32 fn_800F1B30(S1B30 *arg0) {
    if (arg0->count != 0) {
        return arg0->arr[arg0->count - 1].a;
    }
    return 0;
}
