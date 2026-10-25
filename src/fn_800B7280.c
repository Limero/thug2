// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B7280-0x800B7354 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: skater float-property setter. Reads a script f32 property
// (default lbl_80298A8C, stored via the float->u32 cast), writes it to the
// skater +0x24 field, and stamps +0x1C with the current time
// (lbl_80303150 + Tmr_GetTime). The (u32)f32 conversion is the 2^30-magic
// idiom — the pool constant was retargeted to the DOL lbl_ by fix_fp_pool.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80298A8C;
extern f32 lbl_80298A90;
extern char lbl_80298A98[];
extern s32 lbl_80303150;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 Tmr_GetTime(void);
void fn_800B7280(CScript *arg0, CStruct *arg1) {
    f32 sp8;
    f32 temp_f0;

    sp8 = lbl_80298A8C;
    if (GetChecksum_2(arg1, QB_WAIT_OBJ, (char *)arg0 + 0x28, 0) == 0) {
        GetFloat(arg1, QB_LIFETIME, &sp8, 1);
    }
    temp_f0 = sp8 * lbl_80298A90;
    arg0->unk0x24 = (u32) temp_f0;
    arg0->unk0x1C = (s32) (lbl_80303150 + Tmr_GetTime());
}
