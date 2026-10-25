// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800035FC-0x800036C8 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8028FB9C;
extern f32 lbl_8028FBA0;
extern f32 lbl_8028FBA4;
extern f32 lbl_8028FBA8;
extern f32 lbl_8028FBAC;
extern f32 lbl_8028FBB0;
extern f32 lbl_8028FBB4;
f32 sqrtf(f32);
// Kenacosf @ 0x800035FC
f32 Kenacosf(f32 farg0) {
    volatile double _dummy;
    f32 root;

    if (farg0 < lbl_8028FB9C) {
        farg0 = -farg0;
        root = sqrtf(lbl_8028FBA0 - farg0);
        return lbl_8028FBB4 - (((((farg0 * lbl_8028FBA4 + lbl_8028FBA8) * farg0 - lbl_8028FBAC) * farg0) + lbl_8028FBB0) * root);
    } else {
        root = sqrtf(lbl_8028FBA0 - farg0);
        return ((((farg0 * lbl_8028FBA4 + lbl_8028FBA8) * farg0 - lbl_8028FBAC) * farg0) + lbl_8028FBB0) * root;
    }
}
