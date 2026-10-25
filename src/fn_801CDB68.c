// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CDB68-0x801CDBCC (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 lbl_80303150;
s32 Tmr_GetTime(void);

typedef struct S_801CDB68 {
    char pad0x0[0x3F8];
    s32 unk0x3F8;
    s32 unk0x3FC;
    char pad0x400[0x11BC];
    s32 unk0x15BC;
} S_801CDB68;

s32 fn_801CDB68(S_801CDB68 *arg0) {
    register s32 a __asm__("r9");
    s32 temp_r0;
    register s32 temp_r30 __asm__("r30");
    temp_r0 = *((s32 *)((char *)*(s32 *)((char *)arg0 + 0x15BC)) + 7);
    if (temp_r0 == 1) {
        temp_r30 = arg0->unk0x3F8;
        return (lbl_80303150 + Tmr_GetTime()) - temp_r30;
    }
    if (temp_r0 != 2) {
        register s32 b __asm__("r0");
        b = arg0->unk0x3FC;
        a = arg0->unk0x3F8;
        return b - a;
    }
    temp_r30 = arg0->unk0x3F8;
    return (lbl_80303150 + Tmr_GetTime()) - temp_r30;
}
