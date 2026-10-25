// range=0x8009C4A4-0x8009C4B8 size=20B
// Leaf: stores farg0 to *(float*)(*(arg0+0x34) + arg1*8 + 4).
// Table at arg0+0x34, stride 8 bytes, offset 4 within entry.
// Suggested rename: SetTableFloat_0x34
#include "types.h"
#include "structs.h"

void fn_8009C4A4(Unk_C7387A53 *arg0, s32 arg1, f32 farg0) {
    s32 base = arg0->unk0x34;
    *(f32 *)(base + arg1 * 8 + 4) = farg0;
}
