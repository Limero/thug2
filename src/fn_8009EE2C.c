// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009EE2C-0x8009EEAC (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
typedef struct Sub {
    u8 pad0x0[0x10];
    s16 unk0x10;
    s16 pad0x12;
    void (*unk0x14)(u8 *, s32);
    u8 pad0x18[0x20];
    s16 unk0x38;
    s16 pad0x3a;
    void (*unk0x3c)(u8 *, s32);
} Sub;
typedef struct Obj {
    u8 pad0x0[8];
    Sub *unk0x8;
} Obj;
bool fn_8009EE2C(Obj *arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 cmd __asm__("r9") = arg1;
    Sub *temp_r9;

    if (cmd != QB_SETPROPS) {
        if (cmd == QB_DIE) {
            temp_r9 = arg0->unk0x8;
            temp_r9->unk0x3c((u8 *)arg0 + temp_r9->unk0x38, arg2);
        }
    } else {
        temp_r9 = arg0->unk0x8;
        temp_r9->unk0x14((u8 *)arg0 + temp_r9->unk0x10, arg2);
    }
    return true;
}
