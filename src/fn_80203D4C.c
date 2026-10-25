// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80203D4C-0x80203E10 (196B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void CStruct_new(s32);
s32 CStruct_ctor(void);
void fn_8009E574(Unk_C7387A53 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_80203D4C(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r3;
    void *temp_r11;
    Unk_C6B642AC *temp_r9;

    temp_r29 = arg1 * 4;
    temp_r30 = arg0 + 0x1C;
    if (*(s32 *)((char *)temp_r30 + (s32)temp_r29) != 0) {
        CStruct_new(8);
        temp_r3 = CStruct_ctor();
        fn_8009E574(*(s32 *)((char *)temp_r30 + (s32)temp_r29), temp_r3);
        if (GetChecksum_2(temp_r3, QB_CLEANUPSCRIPT, &sp8, 0) != 0) {
            Script_RunScript(sp8, 0, *(s32 *)((char *)temp_r30 + (s32)temp_r29), 0, 0);
        }
        if (temp_r3 != 0) {
            CStruct_delete(temp_r3, 3);
        }
        temp_r11 = *(s32 *)((char *)temp_r30 + (s32)temp_r29);
        temp_r9 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
        ((s32 (*)(void *))temp_r9->unk0x3C)(temp_r11 + temp_r9->unk0x38);
        *(s32 *)((char *)temp_r30 + (s32)temp_r29) = 0;
    }
}
