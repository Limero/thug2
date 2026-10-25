// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80130CB8-0x80130D24 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: small object/UI field setter — writes +0xA4=4, +0xA8=now,
// +0xA0=(f32)arg1.
#include "types.h"
#include "structs.h"
s32 Tmr_GetTime(void);
extern s32 lbl_80303150;
void fn_80130CB8(Unk_C7387A53 *arg0, u32 arg1) {
    arg0->unk0xA4 = 4;
    arg0->unk0xA8 = lbl_80303150 + Tmr_GetTime();
    *((f32 *)&arg0->unk0xA0) = (f32)arg1;
}