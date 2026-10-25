// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020531C-0x80205374 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802052C4(Unk_C7387A53 *);
void fn_80205084(Unk_C8FEE62D *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
bool fn_8020531C(Unk_C8FEE62D * arg0, CStruct *arg1) {
    GetChecksum_2(arg1, 0, (char *)arg0 + 0xC4, 0);
    fn_802052C4(arg0);
    fn_80205084(arg0);
    arg0->unk0xC8 = 0;
    return true;
}
