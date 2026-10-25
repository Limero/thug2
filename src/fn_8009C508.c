// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C508-0x8009C520 (24B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct S_8009C508 {
    char pad0x0[0x2C];
    f32 *unk0x2C;
} S_8009C508;
f32 fn_8009C508(S_8009C508 *arg0, s32 arg1) {
    s32 i;

    i = arg1 * 3;
    return arg0->unk0x2C[i];
}
