// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801417B8-0x80141834 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80301A38;
static s32 fn_800A398C(s32 arg0, s32 arg1);
static s32 fn_80140164(s32 arg0);
static s32 GetStructure_2(s32 arg0, s32 arg1, void *arg2, s32 arg3);
static s32 GetStructure(s32 arg0, s32 arg1);
static f32 fn_80141570(void *arg0, s32 arg1);
void fn_801417B8(CScript *arg0, s32 arg1) {
    s32 sp8;

    sp8 = 0;
    if (GetStructure_2(fn_80140164(fn_800A398C(lbl_80301A38, arg0->unk0x18)), arg1, &sp8, 0) == 0) {
        sp8 = GetStructure(arg1, 0);
    }
    fn_80141570(arg0, sp8);
}
