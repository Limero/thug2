// range 0x801B0144-0x801B0168 (0x24 = 36B). Byte-identical.
// Identification: byte copy — self[1..3] = src[0..2], self[4] = 0 (a
// 3-byte copy plus a terminator/flag byte). NOTE self[4] is a BYTE store
// (`stb r11, 4(r3)`), not a word. No return-arg (want uses r3 directly).
// Suggested rename: Fn_801B0144_CopyBytesAndTerminate.
#include "types.h"
#include "structs.h"
void fn_801B0144(Unk_F96D0DC8 *arg0, Unk_1D62F22E *arg1) {
    arg0->unk0x1 = *(u8 *)arg1;
    arg0->unk0x2 = arg1->unk0x1;
    arg0->unk0x3 = arg1->unk0x2;
    arg0->unk0x4 = 0;
}
