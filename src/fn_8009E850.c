// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E850-0x8009E8A0 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009E63C(Unk_C7387A53 *, CStruct *, CStruct *);
void GetArray(CStruct *, s32, s32 *, s32);
void fn_8009E850(Unk_C7387A53 *arg0, CStruct *arg1, CScript *arg2) {
    s32 sp8;

    GetArray(arg1, 0, &sp8, 1);
    fn_8009E63C(arg0, sp8, arg2->unk0x18);
}
