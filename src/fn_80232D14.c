// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80232D14-0x80232DFC (232B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80232CDC(Unk_C7387A53 *, s32, s32);
s32 fn_8023EFC8();
void fn_8023F6D0(CStruct *);
void fn_8023F5E0(CStruct *);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80233450(s32);
s32 fn_8023C598(s32);
void fn_8023E09C(CStruct *, s32);
void fn_8023EE14(Unk_C7387A53 *);
void fn_802334D4(Unk_C7387A53 *);
void fn_80232D14(Unk_C7387A53 *arg0, s32 arg1) {
    fn_80232CDC(arg0, 1, arg1);
    if (fn_8023EFC8() != 0) {
        if (arg1 != 0) {
            Script_RunScript(QB_PARKED_KILL_WAIT_MESSAGE, 0, 0, 0, 0);
            fn_8023F6D0(fn_8023EFC8());
        } else {
            fn_8023F5E0(fn_8023EFC8());
            fn_80233450(arg0);
        }
    }
    if (fn_8023C598(0) != 0) {
        if ((*(s32 *)((char *)fn_8023C598(1) + 0x74) == 6) || (arg1 != 0)) {
            fn_8023E09C(fn_8023C598(1), 0);
        } else {
            fn_8023E09C(fn_8023C598(1), 1);
        }
        fn_8023EE14(fn_8023C598(1));
    }
    fn_802334D4(arg0);
}
