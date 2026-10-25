// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3298-0x800F3334 (156B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80012224(s32, void *);
extern void fn_800F31D8(CStruct *);
void fn_800F3298(CStruct *arg0) {
    s32 temp_r27;
    s32 var_r11;
    void *temp_r30;
    void *temp_r3;
    Unk_9994C3F5 *var_r30;
    Unk_9994C3F5 *var_r31;

    temp_r3 = *((void * *)&arg0->unk0x4);
    if (temp_r3 != NULL) {
        var_r11 = 0;
        var_r31 = temp_r3;
        temp_r27 = 1 << *(s32 *)arg0;
        while ((u32)var_r11 < (u32)temp_r27) {
            var_r30 = *((void * *)&var_r31->unk0x8);
            while (var_r30 != NULL) {
                temp_r30 = *((void * *)&var_r30->unk0x8);
                fn_80012224(0, var_r30);
                var_r30 = temp_r30;
            }
            fn_800F31D8(var_r31);
            var_r31 = (char *)var_r31 + 0xC;
            var_r11 += 1;
        }
        arg0->unk0x8 = 0;
    }
}
