// range 0x8007B918-0x8007B938 (0x20). Byte-identical.
// Identification: conditional global pointer store — sets lbl_80301840 to
// self->8 when arg is non-zero, else to zero. The ternary is what emits
// want's `or. r4,r4,r4; beq` + branch-select (the if/else form lays the
// paths out differently, 2/8).
#include "types.h"
#include "structs.h"
extern char lbl_80301840[];
void fn_8007B918(Unk_9994C3F5 *self, s32 arg) {
    *(s32 *)lbl_80301840 = arg ? self->unk0x8 : 0;
}