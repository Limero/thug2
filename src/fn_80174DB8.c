// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80174DB8-0x80174ED8 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void CStruct_delete(s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80127E70(s32, s32, s32, s32);
void fn_8000F2F8(void *, s32);
extern char lbl_802FFE98[];
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
void fn_8000F320(Unk_F12C5E01 *self);
s32 CStruct_ctor(void);
void CStruct_dtor(void);
bool ScriptCleanup(s32, s32);
void fn_80199490(s32, s32);
void fn_80174DB8(Unk_6BAF5070 *arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r31;
    s32 temp_r31_2;
    Unk_B0F19D72 *temp_r3;

    temp_r3 = *(void **)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x5F8);
    CStruct_new(8);
    temp_r31 = CStruct_ctor();
    CStruct_dtor();
    fn_80127E70(temp_r31, QB_LEVEL, 0xD, arg1);
    Script_RunScript(QB_REQUEST_LEVEL, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    temp_r0 = arg0->unk0x388;
    arg0->unk0x388 = arg1;
    arg0->unk0x38C = temp_r0;
    CStruct_new(8);
    temp_r31_2 = CStruct_ctor();
    CStruct_dtor();
    if (arg1 != -QB_UNKNOWN_0x16D13502) {
        fn_80127E70(temp_r31_2, 0, 0xD, QB_PRESERVE_SKATERS);
    }
    ScriptCleanup(temp_r31_2, 0);
    if (temp_r31_2 != 0) {
        CStruct_delete(temp_r31_2, 3);
    }
    arg0->unk0x6C = 1;
    fn_80199490(arg0->unk0x398, QB_CHANGELEVELGAMEFLOW);
    fn_8000F320(*(void **)&lbl_802FFE98);
}
