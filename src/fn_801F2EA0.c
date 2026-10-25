// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F2EA0-0x801F2F58 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void *lbl_80305EAC;
extern f32 lbl_802AE324;

extern s32 fn_801F2D48(Unk_13D0EFB0 *, void *);
extern s32 fn_802337CC(CStruct *, f32);

s32 fn_801F2EA0(Unk_13D0EFB0 *arg0, s32 arg1, f32 farg0) {
    volatile __ps_t sp8[2];
    __ps_t *pv = sp8;
    f32 temp_f31;

    temp_f31 = farg0;
    if (((Unk_71062261 *)lbl_80305EAC)->unk0x388 == -QB_UNKNOWN_0x174B47CA) {
        sp8[0] = ((__ps_t *)arg1)[0];
        pv[1] = ((__ps_t *)arg1)[1];
        if (fn_802337CC(pv, lbl_802AE324) != 1) {
            return 0;
        }
    }
    sp8[0] = ((__ps_t *)arg1)[0];
    pv[1] = ((__ps_t *)arg1)[1];
    *((f32 *)&((CStruct *)sp8)->unk0x4) += temp_f31;
    return fn_801F2D48(arg0, pv) == 0;
}
