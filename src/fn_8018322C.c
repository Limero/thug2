// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018322C-0x801832D4 (168B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8018322C(Unk_C8FEE62D *arg0, s32 *arg1, s32 *arg2) {
    register s32 temp_r0 __asm__("r0");
    s32 temp_r9;
    s32 var_r9;
    s32 var_ctr;
    s32 var_r10;
    register void *var_r11 __asm__("r11");

    if (arg0->unk0x10 != NULL) {
        var_r10 = arg0->unk0x14;
        temp_r0 = *arg1;
        if (var_r10 != temp_r0) {
            if (var_r10 < temp_r0) {
                do {
                    temp_r9 = var_r10 + 1;
                    arg0->unk0x14 = temp_r9;
                    var_r10 = temp_r9;
                    arg0->unk0x10 =
                        *(s32 *)(arg0->unk0x10 + (s32)0x8);
                } while (var_r10 < *arg1);
            } else {
                arg0->unk0x10 = NULL;
            }
        }
    }
    if (arg0->unk0x10 == NULL) {
        temp_r0 = *arg1;
        var_r9 = temp_r0;
        __asm__("" : "+r"(var_r9));
        var_r11 = arg0->unk0x8;
        if (temp_r0 > 0) {
            var_ctr = var_r9;
            do {
                var_r11 = ((Unk_9994C3F5 *)var_r11)->unk0x8;
                var_ctr -= 1;
            } while (var_ctr != 0);
        }
        arg0->unk0x14 = var_r9;
        arg0->unk0x10 = var_r11;
    }
    if (arg2 != NULL) {
        *arg2 = *(s32 *)(arg0->unk0x10 + (s32)0x0);
    }
    return *(s32 *)(arg0->unk0x10 + (s32)0x4);
}
