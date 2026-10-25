// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80024250-0x8002428C (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0[0xC];
    f32 unk0xC;
    f32 unk0x10;
} S24250;

f32 fn_8005E1C4(void);

f32 fn_80024250(S24250 *arg0) {
    return fn_8005E1C4() * arg0->unk0xC / arg0->unk0x10;
}
