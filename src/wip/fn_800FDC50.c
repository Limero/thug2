// WIP draft - PARKED. See notes below.
// extra_cflags: -mps-float
// family=m2c range=0x800FDC50-0x800FDD20 size=208B
// PARKED: float-constant/store weave scheduling artifact (59.6%). Structure matches
// (both addi bases r11/r9, single li r0 zero, calls/vtbl/epilogue exact); remaining
// 21-word diff is independent lfs/stfs ordering + FPR temp numbering (f13-first vs
// f0-first). Resists assignment orders, named-zero var, pointer pins, schedule flags.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 63.5% ([0]asc->63.5%).
#include "types.h"
#include "structs.h"
extern char lbl_8029C490[];
extern f32 lbl_8029C18C[1], lbl_8029C190[1], lbl_8029C194[1], lbl_8029C198[1],
    lbl_8029C19C[1], lbl_8029C1A0[1], lbl_8029C1A4[1];
extern void fn_800FCF18(Unk_132A52FF *);
extern void fn_800071D4(s32);

void *fn_800FDC50(Unk_132A52FF *arg0) {
    f32 t[8];
    f32 *lo, *hi;
    s32 z;
    Unk_7A62D47E *ret = arg0;
    fn_800FCF18((s32)arg0);
    ret->unk0xC = (s32)lbl_8029C490;
    fn_800071D4((s32)((char *)ret + 0xA8));
    t[0] = lbl_8029C18C[0];
    lo = &t[0];
    lo[2] = lbl_8029C194[0];
    lo[3] = lbl_8029C198[0];
    lo[1] = lbl_8029C190[0];
    hi = &t[4];
    hi[0] = lbl_8029C19C[0];
    hi[3] = lbl_8029C198[0];
    hi[1] = lbl_8029C1A0[0];
    hi[2] = lbl_8029C1A4[0];
    z = 0;
    ret->unk0xA8 = *(__ps_t *)&lo[0];
    ret->unk0xB0 = *(__ps_t *)&lo[2];
    ret->unk0xB8 = *(__ps_t *)&hi[0];
    ret->unk0xC0 = *(__ps_t *)&hi[2];
    ret->unk0xC8 = z;
    ret->unk0xCC = z;
    return ret;
}
