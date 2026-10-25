// range 0x8018B6B8-0x8018B6D0 (0x18 = 24B). Byte-identical.
// Identification: zeroes self->8, self->0, self->4 (s32 fields), returns self.
// Matching key (recipe 249): with `return arg0;` ngccc emits the zero stores
// ROTATED — source [a,b,c] comes out [c,a,b] — so the source order must be
// [0,4,8] to get want's [8,0,4].
// Suggested rename: Fn_8018B6B8_ZeroThreeFields.
#include "types.h"
#include "structs.h"
void *fn_8018B6B8(CStruct *arg0) {
    arg0->unk0x0 = 0;
    arg0->unk0x4 = 0;
    arg0->unk0x8 = 0;
    return arg0;
}
