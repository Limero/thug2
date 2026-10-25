// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D208-0x8009D29C (148B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
void fn_8009D3D8(Unk_33696503 *);
void fn_8009D208(Unk_C7387A53 *arg0) {
    s32 zero = 0;
    s32 temp_r28;
    s32 temp_r11;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 var_r27;
    s32 var_r29;
    s32 var_r30;
    void *var_r31;

    temp_r28 = arg0->unk0x20;
    var_r29 = 0;
    var_r27 = 4;
    var_r30 = temp_r28 + 8;
    var_r31 = temp_r28 + 0x98;
    do {
        temp_r9 = *(s32 *)((char *)var_r31 - 0xC);
        if ((temp_r9 != 0) && ((u32) temp_r9 >= (u32) *(u32 *)((char *)var_r31 - 0x8))) {
            *(s32 *)((char *)var_r31 - 0xC) = zero;
        }
        temp_r11 = temp_r28 + 0x94;
        temp_r9_2 = *(s32 *)((char *)temp_r11 + (s32)var_r29);
        if ((temp_r9_2 != 0) && ((u32) temp_r9_2 >= (u32) *((u32 *)&((CStruct *)var_r31)->unk0x0))) {
            *(s32 *)((char *)temp_r11 + (s32)var_r29) = zero;
        }
        var_r31 += 0x94;
        fn_8009D3D8(var_r30);
        var_r30 += 0x94;
        var_r29 += 0x94;
        var_r27 -= 1;
    } while (var_r27 != 0);
}
