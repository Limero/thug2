// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013AC98-0x8013AD0C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 memset(s32, s32, s32);
s32 fn_80137AD4(s32);
typedef struct {
    u8 f0;
    u8 f1;
    u16 f2;
    s32 f4;
} Sp8_8013AC98;
bool fn_8013AC98(Unk_BEFC8A8F *arg0, s32 arg1, s32 arg2) {
    Sp8_8013AC98 sp8;

    memset(&sp8, 0, 8);
    sp8.f1 = 2;
    sp8.f2 = 0;
    if (fn_80137AD4(arg0->unk0x1830) != 1) {
        sp8.f4 = arg1;
    }
    arg0->unk0x1824 = 8;
    sp8.f0 = 8;
    return true;
}
