// Auto-generated from tools/gen_leaves.py
// range 0x8018E6A4-0x8018E6C4 (32B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_8018E6A4(Unk_C7387A53 *o, s32 i) {
    u32 m = 1u << i;
    if (*((u32 *)&o->unk0x44) & m) return true;
    return false;
}
