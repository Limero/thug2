// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127438-0x80127568 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_801266EC(void *);
void fn_80117E28(void *);
void fn_80127438(CStruct *arg0, CStruct *arg1) {
    register s32 temp_r0 __asm__("r0");
    register s32 temp_r11 __asm__("r11");
    register s32 temp_r9 __asm__("r9");
    register s32 var_r10 __asm__("r10");
    register s32 c2 __asm__("r11");
    register Unk_C7387A53 *var_r30 __asm__("r30");
    CStruct *var_r31;
    var_r31 = arg0->unk0x4;
    var_r30 = NULL;
    if (var_r31 != NULL) {
        do {
            temp_r11 = var_r31->unk0x4;
            if (temp_r11 == (s32) arg1->unk0x4) {
                var_r10 = 0;
                temp_r9 = var_r31->unk0x0 & 0x7F0000;
                temp_r0 = arg1->unk0x0 & 0x7F0000;
                __asm__("" : "+r"(temp_r9), "+r"(temp_r0));
                if (temp_r9 == temp_r0) {
                    if (temp_r0 != 0xD0000) {
                        goto block_12;
                    }
                    if (temp_r11 != 0) {
                        goto block_12;
                    }
                    temp_r9 = var_r31->unk0x8;
                    temp_r0 = arg1->unk0x8;
                    if (temp_r9 != temp_r0) {
                        goto block_14;
                    }
                    goto block_12;
                }
                __asm__("lis %0,2" : "=r"(c2) : "r"(temp_r9));
                if (temp_r9 == c2) {
                    if (temp_r0 == 0x10000) {
                        goto block_12;
                    }
                }
                if (temp_r9 != 0x10000) {
                    goto block_14;
                }
                if (temp_r0 != c2) {
                    goto block_14;
                }
block_12:
                var_r10 = 1;
            } else {
                goto block_17;
            }
block_14:
            if (var_r10 != 0) {
                if (var_r30 != NULL) {
                    var_r30->unk0xC =  var_r31->unk0xC;
                    fn_801266EC(var_r31);
                    fn_80117E28(var_r31);
                    goto block_18;
                }
                arg0->unk0x4 =  var_r31->unk0xC;
                fn_801266EC(var_r31);
                fn_80117E28(var_r31);
                var_r31 = arg0->unk0x4;
                goto block_19;
            } else {
                goto block_17;
            }
block_17:
            var_r30 = var_r31;
block_18:
            var_r31 = var_r30->unk0xC;
block_19:
        } while (var_r31 != NULL);
    }
    if (var_r30 != NULL) {
        var_r30->unk0xC = arg1;
    } else {
        arg0->unk0x4 = arg1;
    }
    arg1->unk0xC = 0;
}
