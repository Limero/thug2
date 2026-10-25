// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80230FA8-0x80231000 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8023C608(void);
s32 fn_8023F038(void);
s32 fn_80238970(void);
s32 fn_802357B0(Unk_673C6403 *, s32);
s32 fn_802392AC(Unk_673C6403 *);
s32 fn_8022F184(s32);
void fn_80230FA8(Unk_C7387A53 *arg0) {
    s32 *temp_r30;

    arg0->unk0x44 = QB_OFF;
    fn_8023C608();
    fn_8023F038();
    temp_r30 = fn_80238970();
    fn_802357B0(temp_r30, 0);
    fn_802392AC(temp_r30);
    fn_8022F184(*((s32 *)temp_r30));
}
