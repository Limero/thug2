// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A2740-0x800A27BC (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800A2A60(Unk_C8FEE62D *);
s32 fn_80125A3C(void *, s32);
extern s32 lbl_80301A40;
extern s32 lbl_80301A44;
extern s32 lbl_80301A48;
extern s32 lbl_80301A50;
extern s32 lbl_80301A54;
void fn_800A2740(s32 arg0, Unk_C8FEE62D *arg1, s32 arg2, s32 arg3) {
    s32 *p48;
    s32 *p50;

    lbl_80301A40 = arg0;
    lbl_80301A44 = arg2;
    p48 = &lbl_80301A48;
    *p48 = fn_80125A3C((void *)QB_COIM_MIN_SCRATCH_BLOCKS, 0);
    p50 = &lbl_80301A50;
    *p50 = fn_80125A3C((void *)QB_COIM_MAX_PEDS_REMOVE_ATONCE, 0);
    lbl_80301A54 = arg3;
    fn_800A2A60(arg1);
}