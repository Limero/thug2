// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013E098-0x8013E0EC (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8013EA38(Unk_C7387A53 *, s32);

void fn_8013E098(s32 arg0, s32 arg1) {
    s32 temp_r9;

    arg0 = arg1;
    temp_r9 = arg0 + 0x4910;
    *(s32 *)(((Unk_1D62F22E_2 *)temp_r9)->unk0x10 + 0xC) = ((Unk_1D62F22E_2 *)temp_r9)->unk0xC;
    *(s32 *)(((Unk_1D62F22E_2 *)temp_r9)->unk0xC + 0x10) = ((Unk_1D62F22E_2 *)temp_r9)->unk0x10;
    ((Unk_1D62F22E_2 *)temp_r9)->unk0xC = temp_r9;
    ((Unk_1D62F22E_2 *)temp_r9)->unk0x10 = temp_r9;
    if (arg0 != 0) {
        fn_8013EA38(arg0, 3);
    }
}
