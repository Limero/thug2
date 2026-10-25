// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F5AD0-0x800F5BB0 (224B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800F3A1C(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);

void fn_800F5AD0(Unk_C7387A53 *arg0, void *arg1, CStruct *arg2) {
    s32 *temp_r3;
    char *var_r9;
    char *var_r4;
    s32 var_r11;
    s32 temp_r0;

    temp_r3 = (s32 *)fn_800F3A1C(0x44);
    arg0->unk0x54 = (s32)temp_r3;
    *(s32 *)temp_r3 = 0;
    if (arg1 != NULL) {
        var_r9 = *((char * *)&arg0->unk0x54);
        var_r4 = (char *)arg1;
        var_r11 = 0x30;
        do {
            var_r11 -= 0x18;
            temp_r0 = ((Unk_41EA2015 *)var_r4)->unk0x0;
            ((Unk_41EA2015 *)var_r9)->unk0x0 = temp_r0;
            temp_r0 = ((Unk_41EA2015 *)var_r4)->unk0x4;
            ((Unk_41EA2015 *)var_r9)->unk0x4 = temp_r0;
            temp_r0 = ((Unk_59AB5482_2 *)var_r4)->unk0x8;
            ((Unk_59AB5482_2 *)var_r9)->unk0x8 = temp_r0;
            temp_r0 = ((Unk_41EA2015 *)var_r4)->unk0xC;
            ((Unk_41EA2015 *)var_r9)->unk0xC = temp_r0;
            temp_r0 = ((Unk_41EA2015 *)var_r4)->unk0x10;
            ((Unk_41EA2015 *)var_r9)->unk0x10 = temp_r0;
            temp_r0 = ((Unk_41EA2015 *)var_r4)->unk0x14;
            var_r4 += 0x18;
            ((Unk_41EA2015 *)var_r9)->unk0x14 = temp_r0;
            var_r9 += 0x18;
        } while (var_r11 != 0);
        temp_r0 = ((Unk_41EA2015 *)var_r4)->unk0x0;
        ((Unk_41EA2015 *)var_r9)->unk0x0 = temp_r0;
        temp_r0 = ((Unk_41EA2015 *)var_r4)->unk0x4;
        ((Unk_41EA2015 *)var_r9)->unk0x4 = temp_r0;
        temp_r0 = ((Unk_59AB5482_2 *)var_r4)->unk0x8;
        ((Unk_59AB5482_2 *)var_r9)->unk0x8 = temp_r0;
        temp_r0 = ((Unk_41EA2015 *)var_r4)->unk0xC;
        ((Unk_41EA2015 *)var_r9)->unk0xC = temp_r0;
        temp_r0 = ((Unk_41EA2015 *)var_r4)->unk0x10;
        ((Unk_41EA2015 *)var_r9)->unk0x10 = temp_r0;
    }
    if (arg2 != 0) {
        GetChecksum_2(arg2, QB_SKIN, arg0->unk0x54, 0);
    }
}
