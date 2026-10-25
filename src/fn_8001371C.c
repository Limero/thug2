// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001371C-0x80013788 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8001371C(Unk_C8FEE62D *arg0, s32 arg1, s32 arg2) {
    s32 temp_r3;

    extern s32 fn_80013860(void);
    extern s32 fn_800134AC(Unk_DB0E2BAB *, Unk_C8FEE62D *, s32, s32);
    extern void fn_80013978(s32);
    temp_r3 = fn_80013860();
    if (temp_r3 != 0) {
        if (fn_800134AC(temp_r3, arg0, arg1, arg2) == 0) {
            fn_80013978(temp_r3);
            return 0;
        }
        return temp_r3;
    }
    return 0;
}
