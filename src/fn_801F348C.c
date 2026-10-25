// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F348C-0x801F34F4 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char pad0x0[0x32C];
    u8 unk0x32C[0xA];
    u8 unk0x336;
} Rec_801F348C;
void fn_801F340C(void);
void fn_801F348C(Rec_801F348C *arg0, u32 arg1) {
    s32 i;
    fn_801F340C();
    for (i = 0; i < (s32) arg0->unk0x336; i++) {
        if (arg0->unk0x32C[i] > arg1) {
            arg0->unk0x32C[i] = arg0->unk0x32C[i] - 1;
        }
    }
}
