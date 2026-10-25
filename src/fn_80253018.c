// range 0x80253018-0x8025302C (0x14 = 20B). Byte-identical.
// Identification: zeroes self->4 and self->0 (s32 fields), returns self.
// Store order in source is reversed (recipe 249): want emits [4, 0].
// Suggested rename: Fn_80253018_ZeroTwoFields.
#include "types.h"
#include "structs.h"
void *fn_80253018(CStruct *arg0) {
    arg0->unk0x0 = 0;
    arg0->unk0x4 = 0;
    return arg0;
}
