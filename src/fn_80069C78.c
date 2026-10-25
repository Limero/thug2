// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80069C78-0x80069D24 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8013183C(s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void Script_SpawnScript(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_80069C78(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    s32 temp_r30;

    if (arg0->unk0x58 != 0) {
        fn_8013183C(arg0->unk0x58);
    }
    arg0->unk0x58 = arg1;
    arg0->unk0x5C = arg2;
    temp_r30 = CStruct_ctor(CStruct_new(8));
    AddChecksum((CStruct *)temp_r30, QB_ID, arg0->unk0x5C);
    Script_SpawnScript(arg0->unk0x58, temp_r30, 0, 0, 0, 0, 0, 0, 0, 0);
    if (temp_r30 != 0) {
        CStruct_delete((CStruct *)temp_r30, 3);
    }
}
