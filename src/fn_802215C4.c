// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802215C4-0x80221618 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_80305F9C;
extern char lbl_802AFE9C[];
extern void *NextItem(s32);
void fn_801276E8(CStruct *, void *, s32);
bool ScriptGetMyTeam(s32 arg0, CScript *arg1) {
    void *team = NextItem((s32)lbl_80305F9C);

    if (team != NULL) {
        fn_801276E8(arg1->unk0x18, (s32)lbl_802AFE9C,
                    ((Unk_C7387A53 *)team)->unk0x34);
    }
    return true;
}
