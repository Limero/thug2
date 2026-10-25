// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3B44-0x800A3B90 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80301A78[];
void fn_800A5A60(s32, CStruct *, s32, s32);
void fn_800A3B44(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    fn_800A5A60(*(s32 *)&lbl_80301A78, arg0, arg1, arg2);
    arg0->unk0xC = (s32) (arg0->unk0xC | 1);
}
