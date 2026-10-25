// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016C890-0x8016C918 (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 CStruct_new(s32 arg0);
extern s32 CStruct_ctor(s32 arg0);
extern s32 AddString(CStruct * arg0, s32 arg1, void * arg2);
extern void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
extern void fn_8016C9B8(Unk_C7387A53 * arg0, Unk_1ECA8143 * arg1);
extern void CStruct_delete(CStruct * arg0, s32 arg1);
bool fn_8016C890(void **arg0) {
    s32 temp_r31;
    void *temp_r28;
    Unk_C7387A53 *temp_r29;

    temp_r28 = *arg0;
    temp_r31 = CStruct_ctor(CStruct_new(8));
    temp_r29 = *arg0;
    AddString(temp_r31, QB_MODELNAME, (s32)temp_r29);
    AddChecksum(temp_r31, QB_SKELETONNAME, temp_r29->unk0x84);
    fn_8016C9B8((s32)temp_r28, temp_r31);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
