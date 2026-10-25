// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014E1DC-0x8014E2C8 (236B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_800AA0BC(Unk_CFB386B2 *);
s32 fn_800AA1F4(Unk_B8FF8D4C *, Unk_5AA7B5D7 *);
s32 fn_8000C394(Unk_FFAD6788 *);
s32 fn_8012772C(CStruct *, s32, f32);
extern s32 lbl_80305EE4;
bool ScriptGetAnalogueInfo(CStruct *arg0, CScript *arg1) {
    struct {
        char unk0[0x254];
        f32 unk254;
        f32 unk258;
        f32 unk25C;
        f32 unk260;
        char unk264[0x1C];
    } sp8;
    s32 sp288;
    s32 var_r9;
    s32 *tbl;
    register s32 var_r30 __asm__("r30");

    var_r30 = lbl_80305EE4;
    sp288 = 0;
    GetInteger(arg0, QB_CONTROLLER, &sp288, 0);
    var_r9 = sp288;
    tbl = (s32 *)((char *)var_r30 + 0x28);
    var_r30 = tbl[var_r9];
    fn_800AA0BC(&sp8);
    fn_800AA1F4(&sp8, ((CScript *)var_r30)->unk0x1C);
    if ((fn_8000C394((void *)((CScript *)var_r30)->unk0x20) == 0) || (*(s32 *)(((CScript *)var_r30)->unk0x20 + 0x18) == 0)) {
        return false;
    }
    fn_8012772C(arg1->unk0x18, QB_LEFTX, sp8.unk25C);
    fn_8012772C(arg1->unk0x18, QB_LEFTY, sp8.unk260);
    fn_8012772C(arg1->unk0x18, QB_RIGHTX, sp8.unk254);
    fn_8012772C(arg1->unk0x18, QB_RIGHTY, sp8.unk258);
    return true;
}
