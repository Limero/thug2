// Auto-generated from tools/gen_leaves.py
// range 0x800E9D30-0x800E9D50 (32B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_800E9D30(Unk_C7387A53 *o, s32 i) {
    u32 m = 1u << i;
    if (*((u32 *)&o->unk0x50) & m) return true;
    return false;
}
