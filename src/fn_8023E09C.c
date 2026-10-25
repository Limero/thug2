// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023E09C-0x8023E0F8 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80242528(s32);
extern void fn_80245500(CStruct *);
void fn_8023E09C(CStruct *arg0, s32 arg1) {
    if (arg0->unk0x48 != 0) {
        fn_80242528(arg0->unk0x48);
    }
    if (arg1 == 0) {
        if (arg0->unk0x64 != 0) {
            fn_80245500(arg0->unk0x64);
        }
    }
    arg0->unk0x5C = 0;
}
