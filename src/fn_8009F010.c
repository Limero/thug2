// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F010-0x8009F054 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_802979F8;
extern char lbl_80301A78[];
s32 fn_800A54AC(void *, s32, s32, s32, s32, s32, f32);
void fn_8009F010(CScript *arg0, s32 arg1, s32 arg2) {
    s32 field;

    field = arg0->unk0x18;
    fn_800A54AC(*(s32 *)&lbl_80301A78, arg1, field, field, arg2, 0, lbl_802979F8);
}
