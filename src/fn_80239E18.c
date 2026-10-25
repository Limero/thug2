// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80239E18-0x80239ECC (180B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80240B2C(void *, s32);
s32 fn_80237604(Unk_673C6403 *, Unk_F5317C5D *, s32);
typedef struct {
    s32 a;
    u16 b;
} __attribute__((packed)) Unk6;
void fn_80239E18(Unk_C8FEE62D *arg0, Unk_1D62F22E *arg1) {
    Unk6 sp8;
    Unk6 sp10;
    u32 ret;
    s32 v;
    Unk6 *p8;

    p8 = &sp8;
    *p8 = *(Unk6 *)arg1;
    *(s8 *)fn_80240B2C(p8, 1) = (s8)(v = (s32)(s8)(arg1->unk0x1) - 1);
    *(u8 *)fn_80240B2C(p8, 4) = 1;
    sp10 = sp8;
    ret = fn_80237604(arg0, &sp10, 4);
    arg0->unk0x10 += ret >> 16;
    arg0->unk0x14 += ret & 0xFFFF;
}
