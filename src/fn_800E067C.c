// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E067C-0x800E0710 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8029A5F8[];
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_800E067C(CScript *arg0, s32 arg1) {
    s32 temp_r31;

    arg0->unk0x18 = (s32)lbl_8029A5F8;
    temp_r31 = CStruct_ctor(CStruct_new(8));
    AddChecksum(temp_r31, QB_ID, *(s32 *)((char *)arg0 + 0x64));
    Script_RunScript(QB_DESTROY_OBJECT_LABEL, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    fn_8009F558(arg0, arg1);
}
