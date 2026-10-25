// range 0x80240B0C-0x80240B2C (0x20 = 32B). Byte-identical.
// Identification: writes six byte args into self[0..5] (an RGBA/XYZW-style
// byte packet fill), returns self (recipe 249 — the mr r11 base copy).
// Suggested rename: Fn_80240B0C_StoreSixBytes.
#include "types.h"
#include "structs.h"
void *fn_80240B0C(Unk_F96D0DC8 *arg0, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    arg0->unk0x0 = a;
    arg0->unk0x1 = b;
    arg0->unk0x2 = c;
    arg0->unk0x3 = d;
    arg0->unk0x4 = e;
    arg0->unk0x5 = f;
    return arg0;
}
