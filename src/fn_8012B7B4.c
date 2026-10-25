// range 0x8012B7B4-0x8012B7C8 (0x14 = 20B). Byte-identical.
// Identification: returns 1 if the u8 at self[0] <= 2, else 0 — a
// state/index bound check. Compiled via the subfc/adde carry idiom.
// Suggested rename: Fn_8012B7B4_IndexLeq2.
#include "types.h"
s32 fn_8012B7B4(void *self) {
    return *(u8 *)self <= 2;
}
