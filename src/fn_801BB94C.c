// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BB94C-0x801BBA34 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A38;
extern f32 lbl_802AC3A8;
extern f32 lbl_802AC3AC;
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_800A398C(s32, s32);
void fn_801BF2AC(Unk_5B483C70 *, Unk_6A70655D *);
void fn_801BB94C(Unk_AA4FA7BD *arg0, CStruct *arg1) {
    s32 sp8;
    f32 temp_f0;
    f32 temp_f13;
    Unk_6A70655D *temp_r9;

    temp_f13 = lbl_802AC3A8;
    temp_r9 = arg0->unk0xC;
    *((f32 *)&temp_r9->unk0x78) = temp_f13;
    temp_f0 = lbl_802AC3AC;
    *((f32 *)&temp_r9->unk0x8C) = temp_f13;
    *((f32 *)&temp_r9->unk0x80) = temp_f0;
    *((f32 *)&temp_r9->unk0x84) = temp_f0;
    *((f32 *)&temp_r9->unk0x88) = temp_f0;
    *((f32 *)&temp_r9->unk0x90) = temp_f0;
    *((f32 *)&temp_r9->unk0x94) = temp_f0;
    *((f32 *)&temp_r9->unk0x98) = temp_f0;
    *((f32 *)&temp_r9->unk0x9C) = temp_f0;
    *((f32 *)&temp_r9->unk0xA4) = temp_f0;
    *((f32 *)&temp_r9->unk0x7C) = temp_f0;
    *((f32 *)&temp_r9->unk0xA8) = temp_f0;
    *((f32 *)&temp_r9->unk0xAC) = temp_f0;
    *((f32 *)&temp_r9->unk0xB0) = temp_f0;
    *((f32 *)&temp_r9->unk0xA0) = temp_f13;
    *((f32 *)&temp_r9->unk0xB4) = temp_f13;
    arg0->unk0x48 = *((__ps_t *)&temp_r9->unk0x78);
    arg0->unk0x50 = *((__ps_t *)&temp_r9->unk0x80);
    arg0->unk0x58 = *((__ps_t *)&temp_r9->unk0x88);
    arg0->unk0x60 = *((__ps_t *)&temp_r9->unk0x90);
    arg0->unk0x68 = *((__ps_t *)&temp_r9->unk0x98);
    arg0->unk0x70 = *((__ps_t *)&temp_r9->unk0xA0);
    sp8 = 0;
    fn_80128E34(arg1, QB_CAMERATARGET, &sp8, 1);
    fn_801BF2AC(arg0, fn_800A398C(lbl_80301A38, sp8));
}
