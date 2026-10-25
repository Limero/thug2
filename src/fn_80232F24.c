// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80232F24-0x8023308C (360B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80238970();
s32 fn_80238964();
void fn_80235D70(Unk_673C6403 *, s32, s32);
s32 fn_80235CB4(Unk_D0A98DF2 *);
s32 fn_8023C598(s32);
void fn_8023C7A4(CStruct *);
void fn_8023C808(Unk_31DE137E *);
s32 CStruct_ctor(s32 *);
void AddChecksum(CStruct *, u32, u32);
void Script_RunScript(u32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_80235FA8(Unk_9DBD21F4 *, s32);
void fn_8023E0F8(CStruct *, s32);
void fn_802394F8(Unk_673C6403 *, s32, Unk_C7387A53 *);
void fn_80232F24(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    volatile s32 sp8;
    s32 obj;
    s32 t;

    obj = fn_80238970();
    if (arg1 != 0) {
        fn_80235D70(obj, 1, arg2);
        return;
    }
    t = fn_80235CB4(fn_80238964());
    if ((arg0->unk0x44 != QB_OFF) && (arg3 == 0)) {
        if (fn_8023C598(0) != 0) {
            fn_8023C7A4(fn_8023C598(1));
        }
    }
    if (fn_8023C598(0) != 0) {
        fn_8023C808(fn_8023C598(1));
    }
    fn_80235D70(obj, 0, arg2);
    if ((arg0->unk0x44 != QB_OFF) && (arg3 == 0)) {
        if (fn_80235CB4(obj) != t) {
            CStruct_ctor((s32 *)&sp8);
            AddChecksum((s32 *)&sp8, QB_LEVEL, QB_LOAD_SK5ED);
            Script_RunScript(QB_CHANGE_LEVEL, (s32 *)&sp8, 0, 0, 0);
            CStruct_delete((s32 *)&sp8, 2);
        } else {
            fn_80235FA8(obj, 0);
            fn_8023E0F8(fn_8023C598(1), 0);
            fn_802394F8(obj, 0, 0);
        }
    }
}
