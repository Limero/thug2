// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221930-0x80221A7C (332B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80305F9C;
extern s32 lbl_80305FB4;
#include "qb_constants.h"
#include "structs.h"
void fn_80137CB4(Unk_9F066EC1 *);
s32 NextItem(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8021B55C(s32, s32);
void fn_8013DE78(void *, Unk_C71E6DE1 *);
s32 fn_800145AC(void);
bool ScriptJoinTeam(CStruct *arg0) {
    struct {
        u8 msg[0x11];
        char _p0[0x17];
        s32 sp30;
        u16 cell;
    } fr;
    s32 mgr;
    CScript *plyr;
    s32 var_r11;
    s32 b55cret;
    s32 temp_r9;
    register s32 a0 __asm__("r3");
    mgr = lbl_80305F9C;
    fn_80137CB4(&fr.msg[0]);
    plyr = NextItem(mgr);
    if (plyr == 0 || plyr->unk0x18 == 0) {
        return false;
    }
    GetChecksum_2(arg0, 0, &fr.sp30, 0);
    if (fr.sp30 == QB_BLUE) {
        var_r11 = 1;
    } else if (fr.sp30 == QB_RED) {
        var_r11 = 0;
    } else if (fr.sp30 == QB_GREEN) {
        var_r11 = 2;
    } else {
        var_r11 = 3;
    }
    fr.cell = (fr.cell & 0xFF00) | var_r11;
    fr.cell = (fr.cell & 0xFF) | (*(u8 *)(plyr->unk0x18 + 0x1B) << 8);
    b55cret = fn_8021B55C(mgr, 0);
    if ((u32)(fn_800145AC() - lbl_80305FB4) > 0x95U) {
        lbl_80305FB4 = fn_800145AC();
        a0 = b55cret;
        *(void **)&fr.msg[4] = &fr.cell;
        *(u16 *)&fr.msg[2] = 2;
        fr.msg[0] = 0x67;
        *(s32 *)&fr.msg[0xC] = 2;
        fr.msg[0x10] = 8;
        fn_8013DE78(a0, &fr.msg[0]);
    }
    return true;
}
