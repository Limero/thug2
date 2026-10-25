// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CE460-0x800CE4C4 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009F558(Unk_C8FEE62D *, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
extern char lbl_80299890[];
void fn_800CE460(CScript *arg0, s32 arg1) {
    void *temp_r0;
    temp_r0 = (char *)arg0 + 0x1C;
    arg0->unk0x18 = (s32)lbl_80299890;
    if ((s32) *(s32 *)((char *)temp_r0) != 0) {
        CObject_RemoveRefLink(*(s32 *)((char *)temp_r0), temp_r0);
        *(s32 *)((char *)temp_r0) = 0;
    }
    fn_8009F558(arg0, arg1);
}
