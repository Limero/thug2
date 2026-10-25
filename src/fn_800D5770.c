// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D5770-0x800D5804 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80299B54;
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_800D6490(CScript *, s32);
s32 fn_800D64DC(CScript *);
bool fn_800D5770(Unk_C7387A53 *arg0, CStruct *arg1) {
    f32 sp8;
    if (GetFloat(arg1, 0, &sp8, 0) != 0) {
        if (ContainsFlag(arg1, QB_UNKNOWN_0xF915B4F3) == 0) {
            sp8 *= lbl_80299B54;
        }
        fn_800D6490(arg0, arg0->unk0xC);
        *(f32 *)((char *)fn_800D64DC(arg0) + 0xA0) = sp8;
    }
    return true;
}
