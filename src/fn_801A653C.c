// range 0x801A653C-0x801A6554 (0x18 = 24B). Byte-identical.
// Identification: zeroes self->0x10, self->4, self->8 (s32 fields), returns
// self. Store order in source is the recipe-249 rotation (source [4,8,0x10]
// comes out want's [0x10,4,8]).
// Suggested rename: Fn_801A653C_ZeroThreeFields.
#include "types.h"
#include "structs.h"
void *fn_801A653C(CStruct *arg0) {
    arg0->unk0x4 = 0;
    arg0->unk0x8 = 0;
    arg0->unk0x10 = 0;
    return arg0;
}
