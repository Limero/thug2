// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004195C-0x800419C0 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -O2
#include "types.h"
#include "structs.h"
extern const f32 lbl_80292380;
extern const f32 lbl_80292384;
void fn_8004195C(Unk_31DE137E *arg0, Unk_DB0E2BAB *arg1) {
    f32 temp_f13;
    f32 temp_f0;

    temp_f13 = *((f32 *)&arg1->unk0x2C) * *((f32 *)&arg0->unk0x178) * (*((f32 *)&arg0->unk0x170) + lbl_80292380) * lbl_80292384;
    temp_f0 = *((f32 *)&arg1->unk0x30) * *((f32 *)&arg0->unk0x17C) * (*((f32 *)&arg0->unk0x174) + lbl_80292380) * lbl_80292384;
    *((f32 *)&arg1->unk0x24) = *((f32 *)&arg1->unk0x18) - temp_f13;
    *((f32 *)&arg1->unk0x28) = *((f32 *)&arg1->unk0x1C) - temp_f0;
}
