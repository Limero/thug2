// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80069998-0x800699A8 (16B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: float-array slot writer — stores farg0 into the f32 array
// at offset 0x18 of arg0, indexed by arg1. Generic per-object float-array
// setter.
#include "types.h"
typedef struct { char _pad[0x18]; f32 arr[1]; } T69998;
void fn_80069998(T69998 *arg0, s32 arg1, f32 farg0) {
    arg0->arr[arg1] = farg0;
}
