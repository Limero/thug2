// range 0x80026A84-0x80026AA8 (0x24). Byte-identical.
// Identification: array element getter with per-state stride — reads the
// self->4 flag bit 0x400000 to pick the element width: set → s16 element
// at stride 4 (lhax), clear → u8 element at stride 2 (lbzx). Likely a
// packed animation/vertex data accessor.
#include "types.h"
#include "structs.h"
s32 fn_80026A84(CStruct *self, u8 *arr, s32 idx) {
    if (self->unk0x4 & 0x400000)
        return *(s16 *)(arr + idx * 4);
    return *(u8 *)(arr + idx * 2);
}