// range 0x8004E710-0x8004E734 (0x24). Byte-identical.
// Identification: magnitude/flag snap — writes self->0x1ac into *dst and
// returns whether it exceeds the small epsilon 0.0001f (lbl_80292AD4).
//
// Matching key: the comparison must be `> 0.0001f` (not `<` or `>=`).
// want's `fcmpu cr7` + `rlwinm r3,r3,0x1e,0x1f,0x1f` is the GREATER-than
// flag extraction (the same >-vs-< rlwinm SH=0x1e wall as fn_8000C5D8);
// `<` emits rlwinm SH=0x1f (8/9). The self->0x1ac value is intentionally
// loaded twice (once for the store, once for the compare).
#include "types.h"
#include "structs.h"
s32 fn_8004E710(Unk_C7387A53 *self, void *dst) {
    *(f32 *)dst = *((f32 *)&self->unk0x1AC);
    return *((f32 *)&self->unk0x1AC) > 0.0001f;
}