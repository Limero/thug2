// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192B9C-0x80192C10 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A9BB0[];
extern s32 fn_8018B6F8(void *);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_80128978(s32, s32);
void *fn_80192B9C(Unk_EE3DE78A *arg0, CStruct *arg1) {
    fn_8018B6F8(arg0);
    arg0->unk0x14 = (s32)lbl_802A9BB0;
    arg0->unk0x74 = 1;
    GetInteger(arg1, QB_RACE_TOTAL_LAPS, (char *)arg0 + (s32)0x74, 0);
    arg0->unk0x7C = fn_80128978(arg1, QB_USE_WAYPOINT_TIME);
    return arg0;
}
