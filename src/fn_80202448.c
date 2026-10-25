// range 0x80202448-0x80202464 (0x1C = 28B). Byte-identical.
// Identification: array setter with special case — self+0x30[idx*0x24] = v;
// if (v == 1) self->0xa00 = v (sibling of fn_80202438's getter). The
// cmpwi r5,1 is hoisted before the stwx by the scheduler; the base/offset
// temps (recipe 66 + 249) keep `stwx v, r9, r4` in want's operand order.
// Suggested rename: Fn_80202448_TableSetOrFlag.
#include "types.h"
#include "structs.h"
void fn_80202448(Unk_09AB3653 *self, s32 idx, s32 v) {
    char *base = (char *)self + 0x30;
    s32 off = idx * 0x24;
    *(s32 *)(base + off) = v;
    if (v == 1)
        self->unk0xA00 = v;
}
