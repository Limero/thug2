// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D374-0x8009D384 (16B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: array-slot writer — stores arg2 into the s32 array at
// offset 0x260 of arg0, indexed by arg1. Generic per-object array setter.
// Suggested rename: ObjectArray_Set32 or similar.
#include "types.h"
typedef struct {
    char _pad[0x260];
    s32 arr[1];
} T9D374;
void fn_8009D374(T9D374 *arg0, s32 arg1, s32 arg2) {
    arg0->arr[arg1] = arg2;
}
