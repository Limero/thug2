// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011065C-0x801106B0 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void CStruct_new(s32);
s32 fn_800558C0(void);
s32 CStruct_ctor(void);
void fn_80127C14(CStruct *, s32, CStruct *);
bool ScriptGetMetrics(void *arg0, CScript *arg1) {
    s32 temp_r30;

    CStruct_new(8);
    temp_r30 = CStruct_ctor();
    fn_800558C0();
    fn_80127C14(arg1->unk0x18, QB_METRICS, temp_r30);
    return true;
}
