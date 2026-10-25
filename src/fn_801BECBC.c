// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BECBC-0x801BED44 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801BECBC(Unk_C7387A53 *arg0) {
    register void *temp_r9 __asm__("r9");
    register void *temp_r11 __asm__("r11");
    s32 var_r10;

    if (arg0->unk0x17C == 0) {
        return 0;
    }
    temp_r9 = *((void * *)&arg0->unk0x180);
    var_r10 = 1;
    {
        s32 t = ((Unk_C7387A53 *)temp_r9)->unk0x20;
        temp_r11 = temp_r9;
        __asm__("" : "+r"(temp_r11));
        if (t == 0) {
            var_r10 = 0;
        }
    }
    if (var_r10 == 1) {
        return 0;
    }
    if (((Unk_D5CF5D48 *)temp_r11)->unk0x1C == 3) {
        return 1;
    }
    if ((((Unk_D5CF5D48 *)temp_r11)->unk0x40 != 0) && (((Unk_D5CF5D48 *)temp_r11)->unk0x64 == 0)) {
        if (((Unk_D5CF5D48 *)temp_r11)->unk0xAC == 0) {
            return 1;
        }
    }
    return ((Unk_D5CF5D48 *)temp_r11)->unk0x160 != 0;
}
