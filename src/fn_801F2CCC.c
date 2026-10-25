// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F2CCC-0x801F2D48 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 CStruct_ctor(void *);
extern s32 fn_801F2A18(s32, s32);
extern void AddChecksum(CStruct *, s32, s32);
extern void Script_RunScript(s32, void *, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);

void fn_801F2CCC(s32 arg0, s32 arg1) {
    volatile s32 sp8;

    CStruct_ctor(&sp8);
    AddChecksum(&sp8, QB_NAME, fn_801F2A18(arg0, arg1));
    Script_RunScript(QB_GOAL_EDITOR_DELETE_MARKER_OBJECT, &sp8, 0, 0, 0);
    CStruct_delete(&sp8, 2);
}
