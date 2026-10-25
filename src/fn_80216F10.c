// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80216F10-0x80216FDC (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
extern s32 lbl_803A3148;
extern s32 fn_800145AC(void);
extern s32 fn_80198F7C(s32);
extern s32 fn_8021B574(s32);
extern void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80216F10(Unk_C7387A53 *arg0) {
    CScript *temp_r31 = arg0->unk0x20;
    s32 lim = 0x7D0;
    if ((u32)(fn_800145AC() - lbl_803A3148) >= (u32)lim) {
        if (fn_80198F7C(lbl_80305EC0) == QB_NETLOBBY) {
            if (fn_8021B574(temp_r31) > 1) {
                if (temp_r31->unk0x1E0 == 0) {
                    if ((u32)(fn_800145AC() - *((u32 *)&temp_r31->unk0x1D8)) > 0x1388U) {
                        Script_RunScript(QB_LOADPENDINGPLAYERS, 0, 0, 0, 0);
                        Script_RunScript(QB_STARTNETWORKGAME, 0, 0, 0, 0);
                        *((u32 *)&temp_r31->unk0x1E0) = 1;
                    }
                }
            }
        }
    }
}
