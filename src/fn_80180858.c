// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80180858-0x801808C8 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802A9370;
void fn_80182C50(Unk_6A3B48DF *);
void fn_8018337C(CStruct *, s32);
void fn_80183390(s32 *);
void fn_80180858(Unk_C8FEE62D *arg0) {
    s32 sp8;
    f32 fv;
    s32 m1;

    arg0->unk0x18 = 0;
    fn_8018337C(&sp8, (char *)arg0 + 0x54);
    fn_80183390(&sp8);
    fv = lbl_802A9370;
    m1 = -1;
    arg0->unk0x68 = 0;
    *((f32 *)&arg0->unk0x6C) = fv;
    arg0->unk0x74 = m1;
    arg0->unk0x78 = m1;
    fn_80182C50(arg0);
    arg0->unk0x2C = 0;
}
