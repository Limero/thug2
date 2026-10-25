// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9080-0x801B90FC (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_801B90FC(Unk_C7387A53 *);
extern s32 fn_801B8018(void *, Unk_80577C09 *);
extern void fn_801B3220(Unk_C7387A53 *, s32 *, s32 *, Unk_C8FEE62D *);
extern void CStruct_delete(CStruct *, s32);
void fn_801B9080(Unk_C7387A53 *arg0, Unk_80577C09 *arg1) {
    s32 var_r29;

    fn_801B90FC(arg0);
    arg0->unk0x24 |= 0x1000;
    var_r29 = fn_801B8018(arg0, arg1);
    fn_801B3220(arg0, QB_STATE_STOP, QB_SKATERPED_STATETABLE, var_r29);
    if (var_r29 != 0) {
        CStruct_delete(var_r29, 3);
    }
}
