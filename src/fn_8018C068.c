// range 0x8018C068-0x8018C080 (0x18 = 24B). Byte-identical.
// Identification: self->0x54 += 0x14 + idx * 0x3e8 (an array stride add on
// a pointer field). The 0x14 must be added to the LOADED value first via a
// temp — writing `x + 0x14 + idx*0x3e8` inline makes GCC reassociate and
// pre-add the 0x14 onto the index (1/7).
// Suggested rename: Fn_8018C068_AdvanceFieldByStride.
#include "types.h"
#include "structs.h"
void fn_8018C068(Unk_C7387A53 *arg0, s32 idx) {
    s32 t = arg0->unk0x54 + 0x14;
    arg0->unk0x54 = t + idx * 0x3e8;
}
