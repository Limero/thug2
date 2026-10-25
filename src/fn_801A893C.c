// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A893C-0x801A8998 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801A87F8(Unk_C8FEE62D *, s32);
void fn_801A893C(CScript *arg0, CStruct *arg1) {
    if (fn_801A87F8(arg0, *(s32 *)arg1) != 0) {
        s32 *arr = (s32 *)((char *)arg1 + 8);
        arr[arg1->unk0x4] = arg0->unk0x18;
        (arg1->unk0x4)++;
    }
}
