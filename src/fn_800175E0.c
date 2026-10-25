// range 0x800175E0-0x80017604 (0x24). Byte-identical.
// Identification: aspect/scene-scale initializer — stashes f1/f2 at
// +0xac/+0xb0 and precomputes the reciprocals 1/f1 and 1/f2 at
// +0xb4/+0xb8 (const 1.0f from lbl_80290C90). Likely a camera/scale
// struct.
//
// Matching key: source order [ac=f1, b0=f2, b4=1/f1, b8=1/f2] — the
// store order of the two reciprocals (which fdivs result goes where)
// and the load scheduling match only with this exact source (9/9).
#include "types.h"
#include "structs.h"
void fn_800175E0(Unk_FFAD6788 *self, f32 f1, f32 f2) {
    *((f32 *)&self->unk0xAC) = f1;
    *((f32 *)&self->unk0xB0) = f2;
    *((f32 *)&self->unk0xB4) = 1.0f / f1;
    *((f32 *)&self->unk0xB8) = 1.0f / f2;
}