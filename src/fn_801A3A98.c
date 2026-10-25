// range 0x801A3A98-0x801A3ABC (0x24 = 36B). Byte-identical.
// Identification: clamp-and-reset — if self->0x28 > self->0x30, copy
// self->0x28 into self->0x30, then overwrite self->0x28 with the float
// constant at lbl_802AB740. The constant must be loaded INLINE at the
// final store (a materialized temp gets hoisted before the compare and
// diverges). Suggested rename: Fn_801A3A98_ClampAndReset.
#include "types.h"
#include "structs.h"
extern char lbl_802AB740[];
void fn_801A3A98(Unk_C7387A53 *self) {
    f32 x = *((f32 *)&self->unk0x28);
    f32 y = *((f32 *)&self->unk0x30);
    if (x > y)
        *((f32 *)&self->unk0x30) = x;
    *((f32 *)&self->unk0x28) = *(f32 *)lbl_802AB740;
}
