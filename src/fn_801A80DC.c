// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A80DC-0x801A8148 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
extern bool lbl_802FFE58;
extern char lbl_802AB93C[];
s32 fn_800546A0(s32);
void fn_80057CB0(CStruct *);
s32 fn_80125A6C(void *, s32);
s32 fn_801A8148(CScript *, s32);
// remove_orphan_cluster @ 0x801A80DC
bool remove_orphan_cluster(CScript *arg0) {
    fn_80057CB0(fn_800546A0(arg0->unk0x18));
    if ((lbl_802FFE58 == 0) && (fn_80125A6C((s32)lbl_802AB93C, 0) != 0)) {
        fn_801A8148(arg0, 2);
    }
    return true;
}
