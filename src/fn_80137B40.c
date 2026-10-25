// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137B40-0x80137B4C (12B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: byte-array slot writer — stores arg2 into the s8 array at
// offset 0x2034 of arg0, indexed by arg1. Generic per-object byte-array
// setter (flag/state table).
#include "types.h"
typedef struct {
    char _pad[0x2034];
    s8 arr[1];
} T37B40;
void fn_80137B40(T37B40 *arg0, s32 arg1, s8 arg2) {
    arg0->arr[arg1] = arg2;
}
