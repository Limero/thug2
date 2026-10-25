// range 0x8006FAC8-0x8006FB1C (84B). Byte-identical.
// Identification: C++ constructor for the item object whose vtable is
// lbl_80294C50 (same object as fn_8006FB1C / fn_8006FB8C). Sets the vtable,
// zero-fills the +8 payload (0x20C bytes, via memset), clears the +4 / +0x208
// fields and returns `this` — the canonical `new`-style ctor shape. Called
// from fn_800AE250 / fn_800777F0 as `obj = fn_8006FAC8();`.
#include "types.h"
#include "structs.h"
extern char lbl_80294C50[];
void memset(s32, s32, s32);

void *fn_8006FAC8(void *arg0) {
    Unk_5E1C040A *self = arg0;
    self->unk0x214 = (s32)lbl_80294C50;
    memset((s32)((char *)self + 8), 0, 0x20C);
    self->unk0x208 = 0;
    self->unk0x4 = 0;
    return self;
}
