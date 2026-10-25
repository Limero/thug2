// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004F210-0x8004F2C4 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80292C54;
extern f32 lbl_80292C58;
extern f32 lbl_80292C5C;
void fn_8003F360(Unk_2B0B333E *);
void fn_8009E274(Unk_31DE137E *, s32);
void fn_800A3C24(Unk_DB0E2BAB *);
void fn_800A3CC4(s32 *, CStruct *);
extern char lbl_80292DC0[];
extern char lbl_80292DE0[];
void *fn_8004F210(Unk_AA22CA08 *arg0) {
    f32 temp_f12;
    f32 temp_f0;
    f32 temp_f13;
    s32 temp_r29;

    temp_r29 = (char *)arg0 + 0x190;
    fn_8003F360(arg0);
    fn_800A3C24(temp_r29);
    arg0->unk0x1A8 = (s32)lbl_80292DC0;
    arg0->unk0x8 = (s32)lbl_80292DE0;
    fn_800A3CC4(temp_r29, arg0);
    temp_f12 = lbl_80292C54;
    temp_f0 = lbl_80292C58;
    temp_f13 = lbl_80292C5C;
    arg0->unk0x1AC = 0;
    arg0->unk0x1B0 = 0;
    arg0->unk0x1BC = 0;
    arg0->unk0x1C0 = 0;
    arg0->unk0x1C4 = temp_f12;
    arg0->unk0x1C8 = temp_f0;
    arg0->unk0x1CC = -1;
    arg0->unk0x1D0 = temp_f12;
    arg0->unk0x1D4 = temp_f13;
    fn_8009E274(arg0, QB_VSCROLLINGMENU);
    return arg0;
}
