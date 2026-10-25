// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B826C-0x801B82F0 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void fn_801B90FC(Unk_C7387A53 * arg0);
extern void fn_801B82F0(void *arg0);
extern s32 fn_801B8018(void *arg0, Unk_80577C09 * arg1);
extern void fn_801B3220(Unk_C7387A53 * arg0, s32 * arg1, s32 * arg2, Unk_C8FEE62D * arg3);
extern void CStruct_delete(CStruct * arg0, s32 arg1);

void fn_801B826C(Unk_C7387A53 *arg0, Unk_80577C09 *arg1) {
    s32 temp_r3;

    fn_801B90FC(arg0);
    arg0->unk0x24 = (s32)(arg0->unk0x24 & ~2);
    fn_801B82F0(arg0);
    temp_r3 = fn_801B8018(arg0, arg1);
    fn_801B3220(arg0, QB_STATE_TRICKLIP, QB_SKATERPED_STATETABLE, temp_r3);
    if (temp_r3 != 0) {
        CStruct_delete(temp_r3, 3);
    }
}
