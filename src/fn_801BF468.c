// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BF468-0x801BF520 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A38;
extern f32 lbl_802AC5EC;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800A398C(s32, s32);
void fn_801C0B34(Unk_FFAD6788 *, Unk_6A70655D *);
void fn_801BF468(Unk_AA4FA7BD *arg0, CStruct *arg1) {
    s32 sp8;
    f32 temp_f0;
    Unk_130D31C8 *temp_r9;

    sp8 = 0;
    GetChecksum_2(arg1, QB_CAMERATARGET, &sp8, 1);
    fn_801C0B34(arg0, fn_800A398C(lbl_80301A38, sp8));
    temp_r9 = arg0->unk0xC;
    temp_f0 = lbl_802AC5EC;
    arg0->unk0x80 = temp_f0;
    arg0->unk0x28 = temp_f0;
    arg0->unk0x40 = temp_r9->unk0x78;
    arg0->unk0x48 = temp_r9->unk0x80;
    arg0->unk0x50 = temp_r9->unk0x88;
    arg0->unk0x58 = temp_r9->unk0x90;
    arg0->unk0x60 = temp_r9->unk0x98;
    arg0->unk0x68 = temp_r9->unk0xA0;
    arg0->unk0x70 = temp_r9->unk0xA8;
    arg0->unk0x78 = temp_r9->unk0xB0;
}
