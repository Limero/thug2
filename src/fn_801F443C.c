// range 0x801F443C-0x801F4454 (0x18 = 24B). Byte-identical.
// Identification: returns 1 if the u8 at self+0x2ba >= the u8 at self+0x2b9,
// else 0 (unsigned byte compare via the subfc/adde carry idiom).
// Suggested rename: Fn_801F443C_ByteFieldGe.
#include "types.h"
#include "structs.h"
s32 fn_801F443C(Unk_AF33B3CC *self) {
    return self->unk0x2BA >= self->unk0x2B9;
}
