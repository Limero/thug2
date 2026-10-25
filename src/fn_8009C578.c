// range=0x8009C578-0x8009C58C size=20B
// Leaf: loads *(float*)(*(arg0+0x34) + arg1*8 + 4).
// Table at arg0+0x34, stride 8 bytes, offset 4 within entry.
// Suggested rename: GetTableFloat_0x34
#include "types.h"
#include "structs.h"

f32 fn_8009C578(Unk_C7387A53 *arg0, s32 arg1) {
    s32 base = arg0->unk0x34;
    return *(f32 *)(base + arg1 * 8 + 4);
}
