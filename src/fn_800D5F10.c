// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D5F10-0x800D6030 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800D51E0(s32);
s32 ContainsFlag(CStruct *, void *);
extern f32 lbl_80299B70;
extern f32 lbl_80299B74;
extern f32 lbl_80299B78;
s32 Mth_Rnd(s32 scale);
s32 GetFloat(CStruct *, s32, f32 *, s32);
bool fn_800D5F10(CScript *arg0, CStruct *arg1) {
    f32 sp8;
    s32 temp_r9;
    s32 temp_r9_2;
    if (ContainsFlag(arg1, QB_OFF) != 0) {
        fn_800D51E0(arg0);
        arg0->unk0x1C = (s32) (arg0->unk0x1C & QB_UNKNOWN_0xFFFFFF7F);
    } else {
        *((f32 *)&arg0->unk0x1EC) = lbl_80299B70;
        GetFloat(arg1, QB_AMP, (f32 *)((char *)arg0 + 0x1F0), 0);
        sp8 = lbl_80299B74;
        GetFloat(arg1, QB_FREQ, &sp8, 0);
        temp_r9 = (s32) (lbl_80299B78 / sp8);
        arg0->unk0x1F4 = temp_r9;
        temp_r9_2 = arg0->unk0x1F4 + (Mth_Rnd(temp_r9 * 2) - (arg0->unk0x1F4 / 10));
        arg0->unk0x1F4 = temp_r9_2;
        if (temp_r9_2 <= 0) {
            arg0->unk0x1F4 = 1;
        }
        *((f32 *)&arg0->unk0x1E8) = *(f32 *)((char *)(*(void * *)((char *)arg0 + 0xC)) + 0x5C);
        arg0->unk0x1C = (s32) (arg0->unk0x1C | 0x80);
    }
    return true;
}
