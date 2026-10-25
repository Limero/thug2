// range 0x80059380-0x80059394 (0x14 = 20B). Byte-identical.
// Identification: writes a float pair into the bss globals at 0x80364C44
// and 0x80364C48 (f1, f2) via the base lbl_80364C38. Needs an explicit
// `char *b = lbl_80364C38` base (single lis/addi) and the store order
// REVERSED in source (recipe 249: got emits [0xc, 0x10] from [0x10, 0xc]).
// Suggested rename: Fn_80059380_SetFloatPair.
#include "types.h"
#include "structs.h"
extern char lbl_80364C38[];
void fn_80059380(f32 f1, f32 f2) {
    char *b = lbl_80364C38;
    ((Unk_2307D821_2 *)b)->unk0xC = f1;
    ((Unk_2307D821_2 *)b)->unk0x10 = f2;
}
