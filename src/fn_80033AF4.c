// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033AF4-0x80033B98 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Object setup: stores pointers/floats into arg0 fields (0x14=lbl_80291D60,
// 0x8 from fn_800335E0/arg2, 0x1C=fn_8005525C(), 0x18=fn_8006FB50(result,0),
// 0x20=fn_800CBDE0(), then 0x18=0 and 0x24=lbl_80291C54) and binds an
// anim-blender. Returns arg0. Suggested rename: InitAnimBlenderObj
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800335E0(CStruct *);
s32 GetChecksum_3(Unk_6A70655D *, void *);
s32 fn_8006FB50(Unk_5E1C040A *, s32);
extern f32 lbl_80291C54;
extern char lbl_80291D60[];
void *fn_80033AF4(Unk_DB0E2BAB *arg0, s32 arg1, s32 arg2) {
    fn_80033538();
    arg0->unk0x14 = (s32)lbl_80291D60;
    if (arg1 != 0) {
        arg0->unk0x8 = fn_800335E0(arg0);
    } else {
        arg0->unk0x8 = arg2;
    }
    arg0->unk0x1C = fn_8005525C();
    arg0->unk0x18 = fn_8006FB50(arg0->unk0x1C, 0);
    GetChecksum_3(arg0->unk0x8, QB_ANIMBLENDER);
    arg0->unk0x20 = fn_800CBDE0();
    arg0->unk0x18 = 0;
    *((f32 *)&arg0->unk0x24) = lbl_80291C54;
    return arg0;
}
