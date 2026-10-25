// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020CA04-0x8020CA70 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A38[];
extern s32 GetChecksum_2(CStruct *, u32, s32 *, s32);
extern s32 fn_800A398C(s32, s32);
extern void fn_8020CDAC(Unk_85C3B1D9 *, Unk_6A70655D *);
void fn_8020CA04(Unk_298A0A9D *arg0, CStruct *arg1) {
    s32 sp8;
    if (GetChecksum_2(arg1, QB_CAMERA, &sp8, 0) != 0) {
        fn_8020CDAC(arg0, fn_800A398C(*(s32 *)lbl_80301A38, sp8));
    }
    arg0->unk0x7C8 = 0;
}
