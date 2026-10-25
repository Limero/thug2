// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D5624-0x800D56BC (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80299B4C;
extern f32 lbl_80299B50;
s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);
s16 fn_801270B4(CStruct * arg0, s16 arg1);
void *fn_800DA6AC(Unk_6A70655D * arg0, f32 farg0);
s32 AddChecksum(CStruct * arg0, s16 arg1, s32 arg2);
bool fn_800D5624(Unk_6A70655D *arg0, CStruct *arg1, CScript *arg2) {
    f32 sp8;
    CScript *ret;

    sp8 = lbl_80299B4C;
    GetFloat(arg1, QB_RANGE, &sp8, 0);
    sp8 = sp8 * lbl_80299B50;
    fn_801270B4(arg2->unk0x18, -0x65E4);
    ret = fn_800DA6AC((void *)arg0, sp8);
    if (ret != NULL) {
        AddChecksum(arg2->unk0x18, -0x65E4, ret->unk0x18);
    }
    return true;
}
