// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801917FC-0x80191884 (136B). Byte-identical.
#include "types.h"
extern char lbl_80301A38[];
extern char lbl_80305EAC[];
#include "qb_constants.h"
#include "structs.h"
s32 fn_801745B4(s32);
s32 fn_800A398C(s32);
void fn_80131BAC(Unk_15EF4A35 *, s32);
void fn_8011BEFC(s32);
void fn_801917FC(CStruct *arg0) {
    register s32 temp_r4 __asm__("r4");
    s32 var_r3;

    if (arg0->unk0x10 != 0) {
        temp_r4 = arg0->unk0xC;
        if (temp_r4 != 0) {
            if (temp_r4 == QB_SKATER) {
                var_r3 = fn_801745B4(*(s32 *)&lbl_80305EAC);
            } else {
                var_r3 = fn_800A398C(*(s32 *)&lbl_80301A38);
            }
            fn_80131BAC(var_r3, QB_GOAL_PLAY_STREAM);
        }
        fn_8011BEFC(arg0->unk0x10);
        arg0->unk0x10 = 0;
    }
}
