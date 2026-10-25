// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801879F0-0x80187A44 (84B). Byte-identical.
#include "types.h"
#include "structs.h"

extern void fn_801270B4(CStruct * arg0, s32 arg1);
extern void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);

void fn_801879F0(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 != 0) {
        fn_801270B4(arg0->unk0x5C, arg1);
        return;
    }
    if (arg3 != 0) {
        AddInteger(arg0->unk0x5C, arg1, 1);
        return;
    }
    AddInteger(arg0->unk0x5C, arg1, 0);
}
