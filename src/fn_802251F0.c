// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802251F0-0x8022527C (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
void CStruct_delete(CStruct *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void AddChecksum(CStruct *, s32, s32);
s32 CStruct_ctor(s32);
void NextItem(s32);
bool fn_802251F0(Unk_DB0E2BAB *arg0) {
    s32 *temp_r29;
    s32 temp_r30;

    NextItem(arg0->unk0x18);
    temp_r29 = arg0->unk0x0;
    fn_80229B74();
    temp_r30 = CStruct_ctor(CStruct_new(8));
    AddChecksum(temp_r30, QB_CHECKSUM, *((s32 *)temp_r29));
    Script_RunScript(QB_LAUNCH_FCFS_NOTIFICATION, temp_r30, 0, 0, 0);
    if (temp_r30 != 0) {
        CStruct_delete(temp_r30, 3);
    }
    return true;
}
