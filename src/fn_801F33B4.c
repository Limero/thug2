// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F33B4-0x801F340C (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_801F34F4(void);
typedef struct Buf {
    char pad0x0[0x32C];
    u8 unk0x32C[10];
    u8 unk0x336;
} Buf;
void fn_801F33B4(Buf *arg0, s8 arg1) {
    s32 temp_r9;

    if (fn_801F34F4() == 0) {
        temp_r9 = arg0->unk0x336;
        if ((u8)temp_r9 <= 9) {
            arg0->unk0x336 = temp_r9 + 1;
            arg0->unk0x32C[(u8)temp_r9] = arg1;
        }
    }
}
