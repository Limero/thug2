// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000C868-0x8000C938 (208B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void PADControlMotor(void *, void *);
void fn_8000C868(Unk_A0A7249E *arg0) {
    s32 var_r4;
    s32 temp_r0;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 var_r0;
    s32 var_r9;
    s32 var_r9_2;
    s32 var_r9_3;
    CStruct *temp_r11;
    u8 *var_r10;
    u8 *var_r11_2;
    void *temp_r3;

    temp_r11 = (char *)arg0 + 0xC0;
    var_r0 = 1;
    temp_r9 = temp_r11->unk0x4;
    if (temp_r9 == 0) {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        temp_r0 = temp_r9 - 1;
        var_r9 = 1;
        temp_r11->unk0x4 = temp_r0;
        if (temp_r0 == 0) {
            var_r9 = 0;
        }
        if ((var_r9 == 0) && ((s32) arg0->unk0xDC == 2)) {
            var_r9_2 = 1;
            if (!(arg0->unk0xCC & 2)) {
                var_r9_2 = 0;
            }
            if (var_r9_2 != 0) {
                var_r9_3 = 0;
                if (var_r9_3 < (s32) arg0->unk0xD4) {
                    var_r10 = (u8 *)arg0 + (s32)0x60;
                    var_r11_2 = (u8 *)arg0 + (s32)0xA0;
                    do {
                        var_r10[var_r9_3] = var_r11_2[var_r9_3];
                        var_r9_3 += 1;
                    } while (var_r9_3 < (s32) arg0->unk0xD4);
                }
                temp_r3 = *((s32 *)&arg0->unk0x10);
                var_r4 = 1;
                temp_r9_2 = arg0->unk0x60 & QB_UNKNOWN_0xFFFF0000;
                if (temp_r9_2 == 0) {
                    var_r4 = 0;
                }
                PADControlMotor(temp_r3, var_r4);
            }
        }
    }
}
