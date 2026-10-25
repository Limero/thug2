// range 0x80124FDC-0x80125000 (0x24). Byte-identical.
// Identification: float/path init — a 0.0f (lbl_8029E468 pool const) into
// +0x4/+0x8/+0xc and a 0 byte at +1, returning the object.
//
// Matching key: `return self` for the base copy + brute-forced float store
// order — source [0xc,8,4] emits want's [4,0xc,8] (recipe 265/249
// rotation on the float const stores).
#include "types.h"
#include "structs.h"
void *fn_80124FDC(Unk_C71E6DE1 *self) {
    self->unk0x1 = 0;
    *((f32 *)&self->unk0xC) = 0.0f;
    *((f32 *)&self->unk0x8) = 0.0f;
    *((f32 *)&self->unk0x4) = 0.0f;
    return self;
}