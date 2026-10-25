// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6C34-0x801F6C8C (88B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_802AE380[];
extern void fn_801F62D8(Unk_F0C166E4 * arg0);
extern s32 fn_801F2184(s32 arg0);
extern void fn_80127848(CStruct * arg0, void * arg1, s32 arg2);

bool fn_801F6C34(Unk_F0C166E4 *arg0, s32 arg1, CScript *arg2) {
    s32 temp_r28;

    fn_801F62D8((s32)arg0);
    temp_r28 = arg2->unk0x18;
    fn_80127848(temp_r28, (s32)lbl_802AE380, fn_801F2184(arg0->unk0xAC00));
    return true;
}
