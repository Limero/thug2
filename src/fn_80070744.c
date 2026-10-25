// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070744-0x80070788 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_80294D84;
void GetFloat(CStruct *, s32, f32 *, s32);
bool fn_80070744(Unk_C7387A53 *arg0, CStruct *arg1) {
    *((f32 *)&arg0->unk0x30) = lbl_80294D84;
    GetFloat(arg1, 0, (s32)((char *)arg0 + 0x30), 0);
    return true;
}
