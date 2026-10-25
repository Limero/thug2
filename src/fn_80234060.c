// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234060-0x802340AC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80238970(void);
s32 fn_8022D8A4(Unk_C7387A53 *);
void fn_801276E8(CStruct *, void *, s32);
extern char lbl_802B0998[];

// MATCHED @ 0x80234060
bool ScriptGetParkEditorMaxPlayersPossible(void *arg0, CScript *arg1) {
    s32 temp_r30;

    temp_r30 = arg1->unk0x18;
    fn_801276E8((void *)temp_r30, (s32)lbl_802B0998,
                fn_8022D8A4((void *)(*(s32 *)fn_80238970())));
    return true;
}
