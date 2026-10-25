// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FAED8-0x801FAFD4 (252B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80238964(void);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_8022F3FC(void *arg0);
void fn_801FA6B8(Unk_C7387A53 * arg0);
void fn_801FB50C(Unk_C7387A53 * arg0);
void fn_8022F1F0(Unk_C8FEE62D * arg0, void *arg1);
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
void AddInteger(CStruct *, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_800AAB54(void *arg0);
void fn_801FAED8(Unk_31DE137E *arg0, s32 arg1) {
    s32 temp_r30;
    CStruct *temp_r31;
    void *temp_r3;
    Unk_4E705049 *temp_r9;

    temp_r31 = (void *)fn_80238964();
    if (arg1 != 0) {
        Script_RunScript(QB_RAIL_EDITOR_DESTROY_CURSOR, 0, 0, 0, 0);
        fn_8022F3FC(temp_r31->unk0x0);
        fn_801FA6B8(arg0);
        fn_801FB50C(arg0);
        return;
    }
    Script_RunScript(QB_RAIL_EDITOR_CREATE_CURSOR, 0, 0, 0, 0);
    fn_8022F1F0(temp_r31->unk0x0, temp_r31->unk0x80);
    temp_r30 = CStruct_ctor(CStruct_new(8));
    AddInteger(temp_r30, QB_PLAYER, 0);
    temp_r3 = arg0->unk0x1C;
    temp_r9 = ((CScript *)temp_r3)->unk0x18;
    ((s32 (*)(void *, s32))temp_r9->unk0x1C)(temp_r3 + temp_r9->unk0x18, temp_r30);
    if (temp_r30 != 0) {
        CStruct_delete(temp_r30, 3);
    }
    fn_800AAB54(arg0->unk0x1C + 0x24);
}
