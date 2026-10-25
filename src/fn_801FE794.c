// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FE794-0x801FE804 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AE890[];
extern void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
extern void fn_8012772C(CStruct * arg0, s32 arg1, f32 arg2);
extern void fn_8009F674(void *arg0, s32 arg1);
void fn_801FE794(CScript *arg0, CStruct *arg1) {
    s32 *tbl = (s32 *)lbl_802AE890;

    AddChecksum(arg1, QB_M_STATE, tbl[arg0->unk0x1C]);
    fn_8012772C(arg1, QB_M_TIMER, *((f32 *)&arg0->unk0x20));
    fn_8009F674(arg0, arg1);
}
