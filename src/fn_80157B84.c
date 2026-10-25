// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80157B84-0x80157CB0 (300B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80301A38;
extern void *fn_800A200C(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_80061F2C(Unk_EFE13F4E * arg0);
extern s32 fn_80061EC0(CStruct * arg0, s32 arg1);
bool ScriptReplaceCarTextures(s32 arg0, s32 arg1) {
    s32 sp8[31];
    s32 *var_r30;
    register s32 *var_r9 __asm__("r9");
    s32 temp_r0;
    s32 temp_r28;
    s32 temp_r3;
    s32 var_ctr;
    s32 var_r11;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    s32 var_r31;
    Unk_A3DE1534 *var_r29;
    Unk_E71E4713 *temp_r9;

    var_r27 = 0;
    var_r29 = fn_800A200C(lbl_80301A38, QB_MODEL);
    if (var_r29 != NULL) {
        s32 *var_r23 = sp8;
        s32 car_type = QB_OBJECT_TYPE_CAR;
        var_r26 = 0;
        do {
            if (*(s32 *)(var_r29->unk0xC + 0x1C) == car_type) {
                temp_r28 = var_r29->unk0x210;
                var_r25 = 0;
                var_r31 = 0;
                var_r30 = (s32 *)((char *)var_r23 + var_r26);
                while (var_r31 < fn_80061F2C((void *)temp_r28)) {
                    temp_r3 = fn_80061EC0(temp_r28, var_r31);
                    var_r11 = 0;
                    __asm__("" : "+r"(var_r11));
                    if (var_r11 < var_r27) {
                        var_ctr = var_r27;
                        var_r9 = sp8;
                        do {
                            temp_r0 = *var_r9++;
                            if (temp_r3 == temp_r0) {
                                var_r11 = 1;
                            }
                            var_ctr -= 1;
                        } while (var_ctr != 0);
                    }
                    if (var_r11 == 0) {
                        *var_r30 = temp_r3;
                        var_r26 += 4;
                        var_r30 += 1;
                        var_r27 += 1;
                        var_r25 = 1;
                    }
                    var_r31 += 1;
                }
                if (var_r25 != 0) {
                    temp_r9 = var_r29->unk0x18;
                    ((s32 (*)(void *, s32, s32, s32)) *((void * *)&temp_r9->unk0x64))(
                        (char *)var_r29 + temp_r9->unk0x60,
                        QB_OBJ_REPLACETEXTURE, arg0, arg1);
                }
            }
            var_r29 = var_r29->unk0x14;
        } while (var_r29 != NULL);
    }
    return true;
}
