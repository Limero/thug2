// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EF9C0-0x800EFA5C (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_8029B234[];
extern s32 lbl_80301B48;
void fn_800EFA5C(Unk_31DE137E *);
s32 fn_800F2F90(s32);
s32 fn_800F2EDC(s32, void *, s32, s32, s32, s32);
void fn_800F2F88(s32, s32);
s32 Script_GenerateCRC(void *);
s32 sprintf();

void fn_800EF9C0(Unk_31DE137E *arg0, s32 arg1, s32 arg2) {
    char sp8[32];
    s32 temp_r28;
    s32 temp_r31;

    fn_800EFA5C(arg0);
    sprintf(sp8, (s32) lbl_8029B234, arg1);
    temp_r31 = lbl_80301B48;
    temp_r28 = fn_800F2F90(temp_r31);
    if (fn_800F2EDC(temp_r31, sp8, arg1, arg2, 0, 0) != 0) {
        arg0->unk0x1C = Script_GenerateCRC(sp8);
    }
    fn_800F2F88(temp_r31, temp_r28);
}
