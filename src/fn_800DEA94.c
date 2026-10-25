// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DEA94-0x800DEB04 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8000C6A0(s32);
s32 fn_8000C938(void);
typedef struct {
    char pad0x0[0x40];
    s16 unk0x40;
    char pad0x42[0x2];
    s32 unk0x44;
} Unk_800DEA94_vt;
void fn_800DEA94(CScript *arg0) {
    Unk_800DEA94_vt *temp_r9;
    register s32 t3 __asm__("r3");

    if (arg0->unk0x1C != 0) {
        temp_r9 = (Unk_800DEA94_vt *)arg0->unk0x18;
        arg0->unk0x1C = 0;
        ((s32 (*)(void *, s32))temp_r9->unk0x44)((char *)arg0 + temp_r9->unk0x40, 1);
        t3 = arg0->unk0x38;
        if (t3 != 0) {
            fn_8000C938();
            fn_8000C6A0(arg0->unk0x38);
        }
    }
}
