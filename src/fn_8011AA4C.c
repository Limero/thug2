// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011AA4C-0x8011AACC (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { char _pad0[0x10]; f32 fld_10; } S_8011AA4C;
extern s32 fn_80119470(void);
extern s32 fn_80119B24(void *, s32);
extern f32 lbl_80302C3C;
extern f32 lbl_8029D51C;
f32 fn_8011AA4C(void *arg0, s32 arg1) {
    S_8011AA4C *r;
    f32 v;

    if (fn_80119470() != 0) {
        return lbl_80302C3C;
    }
    r = (void *)fn_80119B24(arg0, arg1);
    if (r == NULL) {
        return lbl_8029D51C;
    }
    v = *((f32 *)&r->fld_10);
    if (v == lbl_8029D51C) {
        return *(volatile f32 *)&lbl_80302C3C;
    }
    return v;
}
