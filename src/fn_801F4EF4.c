// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4EF4-0x801F4F88 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AE3B8[];
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_801F2014(void *, s32);
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_801F4EF4(CScript *arg0, s32 arg1) {
    register s32 a0 __asm__("r30");
    void *temp_r0;
    void *temp_r29;
    void *var_r31;

    a0 = (s32)arg0;
    arg0->unk0x18 = (s32)lbl_802AE3B8;
    Script_RunScript(QB_GOAL_EDITOR_DESTROY_CURSOR, 0, 0, 0, 0);
    temp_r0 = (char *)a0 + 0x20;
    if (temp_r0 != NULL) {
        var_r31 = (char *)a0 + 0xAC00;
        if (temp_r0 != var_r31) {
            temp_r29 = temp_r0;
            __asm__("" : "+r"(temp_r29));
            do {
                var_r31 -= 0x370;
                fn_801F2014(var_r31, 0);
            } while (temp_r29 != var_r31);
        }
    }
    fn_8009F558((void *)a0, arg1);
}
