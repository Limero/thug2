// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013EBEC-0x8013ED00 (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_8029F3C8[];
void fn_80137FEC(CStruct *arg0, s32 arg1);

void fn_8013EBEC(s32 arg0) {
    s32 sp8;
    double _dummy;
    s32 var_r10;
    void *temp_r9;
    void *temp_r9_2;
    register void *var_r11 __asm__("r11");
    void *var_r11_2;
    register void *var_r11_3 __asm__("r11");
    void *var_r30;
    void *var_r31;

    *(s32 *)((char *)&sp8 + 0x4) = NULL;
    *(s32 *)((char *)&sp8 + 0x8) = (s32)lbl_8029F3C8;
    var_r10 = 0;
    do {
        temp_r9 = (var_r10 * 0x18) + arg0 + 0x884;
        *(s32 *)((char *)&sp8 + 0x4) = temp_r9;
        var_r11 = *(s32 *)((char *)temp_r9 + (s32)0xC);
        if ((s32) *(s32 *)((char *)var_r11 + (s32)0x4) == -1) {
            var_r11 = NULL;
        }
        *(s32 *)((char *)&sp8 + 0x4) = var_r11;
        if (var_r11 == NULL) {
            __asm__("li %0,0" : "=r"(var_r11));
        } else {
            var_r11 = *(s32 *)((char *)var_r11 + (s32)0x4);
        }
        var_r11_2 = var_r11;
        var_r31 = var_r11_2;
        if (var_r31 != NULL) {
            do {
                temp_r9 = *(s32 *)((char *)&sp8 + 0x4);
                var_r11_3 = *(s32 *)((char *)temp_r9 + (s32)0xC);
                if ((s32) *(s32 *)((char *)var_r11_3 + (s32)0x4) == -1) {
                    var_r11_3 = NULL;
                }
                *(s32 *)((char *)&sp8 + 0x4) = (s32)var_r11_3;
                if (var_r11_3 != NULL) {
                    var_r30 = *(s32 *)((char *)var_r11_3 + (s32)0x4);
                } else {
                    var_r30 = NULL;
                }
                if ((s32) *(s32 *)((char *)var_r31 + (s32)0x2C) != 0) {
                    fn_80137FEC(*(s32 *)((char *)var_r31 + (s32)0x2C), 3);
                }
                if (var_r31 != NULL) {
                    temp_r9_2 = *(s32 *)((char *)var_r31 + (s32)0x14);
                    ((s32 (*)(void *, s32))*(s32 *)((char *)temp_r9_2 + (s32)0xC))((void *)((char *)var_r31 + *(s16 *)((char *)temp_r9_2 + (s32)0x8)), 3);
                }
                var_r31 = var_r30;
            } while (var_r31 != NULL);
        }
        var_r10 += 1;
    } while (var_r10 <= 0xFF);
    *(s32 *)((char *)&sp8 + 0x8) = (s32)lbl_8029F3C8;
    __asm__("" : : "m"(_dummy));
}
