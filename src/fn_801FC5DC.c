// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC5DC-0x801FC678 (156B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F80;
s32 fn_800F0F84(s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_801FC55C(void);
s32 fn_801FC760(s32);
void fn_801FC5DC(Unk_6BB06288 *arg0) {
    s32 sp8;
    s32 flag;
    s32 obj;
    u8 temp_r0;

    temp_r0 = arg0->unk0x75;
    flag = 1;
    if (temp_r0 == 0) {
        flag = 0;
    }
    if (flag != 0) {
        obj = arg0->unk0x60;
        if (obj != 0) {
            obj = fn_800F0F84(obj, 0);
            if (obj != 0) {
                sp8 = 0;
                GetChecksum_2(obj, QB_TRIGGERSCRIPT, &sp8, 0);
                if (sp8 != 0) {
                    fn_801FC55C();
                    if (fn_801FC760(sp8) != 0) {
                        lbl_80305F80 = 1;
                    }
                }
            }
        }
    }
}
