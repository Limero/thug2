// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A450-0x8011A4E4 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8029D4F4;
extern f32 lbl_8029D4F8;
extern f32 lbl_8029D4FC;
typedef struct { char _0[8]; f32 f8; f32 fC; } X;
s32 fn_80119470(s32);
void fn_80119668(void *, f32);
void fn_8011A450(s32 arg0, void *arg1, f32 *arg2, X *arg3) {
    volatile double _dummy;
    f32 lim;
    if (fn_80119470(arg0) != 0) {
        return;
    }
    fn_80119668(arg1, lbl_8029D4F4);
    lim = lbl_8029D4F8;
    if (arg3->fC != lim) {
        fn_80119668(arg1, arg3->fC);
    }
    if (arg3->f8 != lim) {
        arg2[0] = arg2[0] * arg3->f8 * lbl_8029D4FC;
    }
}
