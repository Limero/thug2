// range 0x8002428C-0x800242B8 (0x2C). Byte-identical.
// Identification: ownership/claim check — if self->0x18 equals arg, sets
// the 0x1 flag in self->0x14 and returns 1, else returns 0. The equality-
// first form (flag body inside `if (== arg)`) is what lands the beq to
// the shared set path (a !=-first form inverts the branch selection).
// Suggested rename: Fn_8002428C_ClaimById.
#include "types.h"
#include "structs.h"
bool fn_8002428C(Unk_C8FEE62D *self, s32 arg) {
    if (self->unk0x18 == arg) {
        self->unk0x14 |= 1;
        return true;
    }
    return false;
}