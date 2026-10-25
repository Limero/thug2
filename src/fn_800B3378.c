// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B3378-0x800B33EC (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

// File-local layout (trap #1): CScript's shared unk0x20/unk0x24 are `s32`
// and it has no unk0x0/unk0x4/unk0x8/unk0xC members at all, so a 16-byte
// copy through it is unspellable. Only the true offsets used here matter.
// The 16-byte payload is a paired-single V4 (2 x __ps_t): a struct of plain
// f32s copies as four lwz/lwz/stw/stw pairs instead of psq_l/psq_st.
typedef struct { __ps_t p[2]; } B3378V4;

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    void *unk0x8;
    void *unk0xC;
    char pad0x10[0x10];
    B3378V4 unk0x20;
    char pad0x30[0x1E0];
    void *unk0x210;
} B3378Script;

void fn_800B61F4(void *);
s32 fn_800626E8(void *, void *);

void fn_800B3378(B3378Script *arg0, void *arg1) {
    B3378V4 sp8;
    s32 temp_r9;
    s32 var_r11;

    var_r11 = 1;
    arg0->unk0x210 = arg1;
    temp_r9 = *(s32 *)(*(s32 *)((char *)arg0 + 0xC) + 0x114) & 0x20;
    if (temp_r9 == 0) {
        var_r11 = 0;
    }
    if (var_r11 != 0) {
        fn_800B61F4(arg0);
    }
    fn_800626E8(&sp8, arg1);
    arg0->unk0x20.p[0] = sp8.p[0];
    arg0->unk0x20.p[1] = sp8.p[1];
}
