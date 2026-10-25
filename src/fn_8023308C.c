// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023308C-0x802331B8 (300B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8023C598(s32);
void fn_8023C7A4(CStruct *);
s32 fn_80238970();
s32 fn_80238964();
void fn_8023590C(Unk_673C6403 *, void *, s32);
s32 fn_80235CB4(Unk_D0A98DF2 *);
s32 CStruct_ctor(s32 *);
void AddChecksum(CStruct *, u32, u32);
void Script_RunScript(u32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_80235FA8(Unk_9DBD21F4 *, s32);
void fn_8023E0F8(CStruct *, s32);
void fn_802394F8(Unk_673C6403 *, s32, Unk_C7387A53 *);
void fn_8023308C(Unk_C7387A53 *arg0, void *arg1, s32 arg2) {
    volatile s32 sp8;
    s32 flag;
    s32 temp_r31;

    flag = (arg0->unk0x44 == QB_EDIT) ||
           (arg0->unk0x44 == QB_TEST_PLAY);
    if (flag != 0) {
        if (fn_8023C598(0) != 0) {
            fn_8023C7A4(fn_8023C598(1));
        }
    }
    fn_8023590C((temp_r31 = fn_80238970()), arg1, 0);
    if (flag != 0) {
        if (fn_80235CB4(fn_80238964()) != arg2) {
            CStruct_ctor((s32 *)&sp8);
            AddChecksum((s32 *)&sp8, QB_LEVEL, QB_LOAD_SK5ED);
            Script_RunScript(QB_CHANGE_LEVEL, (s32 *)&sp8, 0, 0, 0);
            CStruct_delete((s32 *)&sp8, 2);
        } else {
            fn_80235FA8(temp_r31, 0);
            fn_8023E0F8(fn_8023C598(1), 0);
            fn_802394F8(temp_r31, 0, 0);
        }
    }
}
