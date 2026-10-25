// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80191618-0x801916B4 (156B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80301B48;
extern char lbl_802A984C[];
void fn_801916B4(CStruct *);
s32 sprintf(s32, ...);
s32 fn_800F2F90(Unk_C7387A53 *);
s32 fn_800F2EDC(CScript *, s32 *, s32, s32, s32, s32);
s32 Script_GenerateCRC(s32 *);
void fn_800F2F88(Unk_C7387A53 *, s32);
void fn_80191618(CStruct * arg0, s32 arg1, s32 arg2) {
    volatile s32 sp8;
    s32 pad[5];
    s32 temp_r28;
    s32 temp_r31;

    fn_801916B4(arg0);
    sprintf((s32)&sp8, (s32)lbl_802A984C, arg1);
    temp_r31 = lbl_80301B48;
    temp_r28 = fn_800F2F90(temp_r31);
    if (fn_800F2EDC(temp_r31, (s32 *)&sp8, arg1, arg2, 0, 0) != 0) {
        arg0->unk0x8 = Script_GenerateCRC(&sp8);
    }
    fn_800F2F88(temp_r31, temp_r28);
    (void)pad;
}
