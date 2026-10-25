// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034300-0x80034364 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { u8 _0[4]; void *unk4; u8 _8[0x28]; s32 unk30; s32 unk34; } S;
f32 fn_800340C4(void *);
s32 fn_8006FB50(s32, s32);
void fn_80034300(S *arg0) {
    volatile double _dummy;
    f32 old;
    old = *(f32 *)((char *)arg0->unk4 + 0x20);
    *(f32 *)((char *)arg0->unk4 + 0x20) = fn_800340C4(arg0);
    if (*(f32 *)((char *)arg0->unk4 + 0x20) < old) {
        arg0->unk34 = fn_8006FB50(arg0->unk30, 0);
    }
}
