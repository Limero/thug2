// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CB624-0x801CB6B8 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AD0B0[];
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_801CB624(CScript *arg0, s32 arg1) {
    s32 temp_r31;

    arg0->unk0x18 = (s32)lbl_802AD0B0;
    temp_r31 = CStruct_ctor(CStruct_new(8));
    AddChecksum(temp_r31, QB_ID, arg0->unk0x1C);
    Script_RunScript(QB_DESTROY_OBJECT_LABEL, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    fn_8009F558(arg0, arg1);
}
