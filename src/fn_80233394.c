// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233394-0x80233404 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A78;
extern f32 lbl_802B090C;
s32 fn_8023C598(s32);
void fn_8023E290(CStruct *);
void fn_80233450(s32);
void fn_800A54AC(Unk_AD65BA9A *, void *, s32, s32, s32, s32, f32);
void fn_80233394(s32 arg0) {
    s32 o = arg0;
    fn_8023E290(fn_8023C598(1));
    fn_80233450(o);
    fn_800A54AC(lbl_80301A78, QB_PARKED_MENU_UP, QB_SET_MENU_CONTAINER, QB_SYSTEM, 0, 0, lbl_802B090C);
}
