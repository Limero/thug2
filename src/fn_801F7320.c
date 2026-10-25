// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F7320-0x801F7378 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 ContainsFlag(CStruct *, s32);
extern void fn_801F61E8(Unk_F0C166E4 *);
extern void fn_801F6164(Unk_F0C166E4 *);

bool fn_801F7320(Unk_F0C166E4 *arg0, CStruct *arg1) {
    if (ContainsFlag(arg1, QB_ONLYPARKEDITORGOALS) != 0) {
        fn_801F61E8(arg0);
    } else {
        fn_801F6164(arg0);
    }
    return true;
}
