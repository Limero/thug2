// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165B44-0x80165B88 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80127C14(CStruct *, s32, CStruct *);
void s_insert_story_info(CStruct *arg0) {
    Game_GetGoalManager();
    fn_80127C14(arg0, QB_GOALMANAGERPARAMS, fn_801869E4());
}
