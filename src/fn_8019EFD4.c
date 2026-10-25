// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019EFD4-0x8019F090 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "qb_constants.h"
#include "types.h"

extern f32 lbl_802AAFBC;
extern f32 lbl_802AAFC0;
extern f32 lbl_802AAFC4;

void *GetChecksum_3(void *arg0, s32 arg1);
s32 fn_800CBE7C(void *arg0, void *arg1);
f32 fn_800CBE30(void *arg0, void *arg1);
void fn_800CBFF4(void *arg0, f32 a1, void *a2, f32 a3, f32 a4, f32 a5, s32 a6, s32 a7);

void fn_8019EFD4(void *arg0, void *arg1) {
    void *r30;
    f32 res, k1, k2, k3;
    if (GetChecksum_3(arg0, QB_ANIMBLENDER) != NULL) {
        if (fn_800CBE7C(GetChecksum_3(arg0, QB_ANIMBLENDER), arg1) != 0) {
            r30 = GetChecksum_3(arg0, QB_ANIMBLENDER);
            res = fn_800CBE30(GetChecksum_3(arg0, QB_ANIMBLENDER), arg1);
            k1 = lbl_802AAFBC;
            k2 = lbl_802AAFC0;
            k3 = lbl_802AAFC4;
            fn_800CBFF4(r30, k1, arg1, res, k2, k3, 0, 1);
        }
    }
}
