// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004DC78-0x8004DD24 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8005DC00(s32, s32, s32, s32);
void fn_8009E274(Unk_31DE137E *, s32);
void fn_8003F360(void);
void CScreenElement_SetJust(Unk_4313CFEA *, f32, f32);
void CScreenElement_SetPos(Unk_4313CFEA *, s32, f32, f32);
void fn_8003F93C(Unk_4313CFEA *, s32, f32, f32);
extern f32 lbl_80292A0C;
extern f32 lbl_80292A10;
extern f32 lbl_80292A14;
extern f32 lbl_80292A18;
extern char lbl_80292A28[];
void *fn_8004DC78(Unk_4313CFEA *arg0) {
    f32 temp_f1;
    f32 temp_f1_2;
    fn_8003F360();
    arg0->unk0x8 = (s32)lbl_80292A28;
    fn_8009E274(arg0, QB_WINDOWELEMENT);
    arg0->unk0x190 = fn_8005DC00(0, 0, 0x280, 0x1C0);
    temp_f1 = lbl_80292A0C;
    CScreenElement_SetJust(arg0, temp_f1, temp_f1);
    temp_f1_2 = lbl_80292A10;
    CScreenElement_SetPos(arg0, 1, temp_f1_2, temp_f1_2);
    fn_8003F93C(arg0, 0, lbl_80292A14, lbl_80292A18);
    return arg0;
}
