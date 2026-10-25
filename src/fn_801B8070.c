// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B8070-0x801B8120 (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_801B90FC(Unk_C7387A53 *);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern u8 fn_8010BA84(s32);
extern void fn_801B7F60(Unk_C7387A53 *, u8);
extern s32 fn_801B8018(void *, Unk_80577C09 *);
extern void fn_801B3220(Unk_C7387A53 *, s32 *, s32 *, Unk_C8FEE62D *);
extern void CStruct_delete(CStruct *, s32);

void fn_801B8070(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 temp_r30;
    u8 temp_r4;

    fn_801B90FC(arg0);
    arg0->unk0x24 = (arg0->unk0x24 | 4);
    if (GetChecksum_2(arg1, QB_TERRAINTYPE, &sp8, 0) != 0) {
        temp_r4 = fn_8010BA84(sp8);
        fn_801B7F60(arg0, temp_r4);
    }
    temp_r30 = fn_801B8018(arg0, arg1);
    fn_801B3220(arg0, QB_STATE_GRIND, QB_SKATERPED_STATETABLE, 0);
    if (temp_r30 != 0) {
        CStruct_delete(temp_r30, 3);
    }
}
