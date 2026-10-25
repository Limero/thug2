// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233E84-0x80233F00 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80128A90(CStruct *, void *);
void fn_80232D14(Unk_C7387A53 *, s32);
extern char lbl_80305FF8[];
extern char lbl_802B0960[];
extern char lbl_802B0968[];

// MATCHED @ 0x80233E84
bool ScriptSetParkEditorPauseMode(CStruct *pParams, CScript *pScript) {
    s32 temp_r30;

    temp_r30 = *(s32 *)&lbl_80305FF8;
    if (fn_80128A90(pParams, (s32)lbl_802B0960) != 0) {
        fn_80232D14(temp_r30, 1);
    } else if (fn_80128A90(pParams, (s32)lbl_802B0968) != 0) {
        fn_80232D14(temp_r30, 0);
    }
    return true;
}
