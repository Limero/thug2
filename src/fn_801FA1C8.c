// range 0x801FA1C8-0x801FA1EC (0x24 = 36B). Byte-identical.
// Identification: zero-fills the 0x1132-byte buffer at self+0x38 (a large
// constant-count clear, mtctr/bdnz loop). Matching key: the index must be
// **u32** — with `s32 i` ngccc strength-reduces to a backward walking
// pointer (`addi r3,r3,-1; stb`) while want is the forward indexed form
// (`stbx r0,r3,r9; addi r9,r9,1; bdnz`). The explicit `u8 *buf` base
// (recipe 247) is also required.
// Suggested rename: Fn_801FA1C8_ClearBuffer1132.
#include "types.h"
void fn_801FA1C8(void *self) {
    u32 i;
    u8 *buf = (u8 *)((char *)self + 0x38);
    for (i = 0; i < 0x1132; i++)
        buf[i] = 0;
}
