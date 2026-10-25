// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034A28-0x80034A90 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { u8 _0[0x18]; void *unk18; u8 _1C[4]; s32 unk20; } S;
f32 fn_8002DB10(void *);
s32 fn_8006FB50(s32, s32);
void fn_80034A28(S *arg0) {
    volatile double _dummy;
    f32 old;
    old = *(f32 *)((char *)arg0->unk18 + 0x1C);
    *(f32 *)((char *)arg0->unk18 + 0x1C) = fn_8002DB10(arg0->unk18);
    if (*(f32 *)((char *)arg0->unk18 + 0x1C) < old) {
        arg0->unk20 = fn_8006FB50(*(s32 *)((char *)arg0 + 0x1C), 0);
    }
}
