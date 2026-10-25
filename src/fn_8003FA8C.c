// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FA8C-0x8003FB80 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8004195C(void *, void *);
typedef struct SP { char _00[0x2C]; f32 f2C; f32 f30; f32 f34; f32 f38; } SP;
typedef struct SQ { char _00[0x2C]; f32 f2C; f32 f30; } SQ;
typedef struct SA { char _00[0xC]; s32 f_0C; } SA;
// CScreenElement_SetScale @ 0x8003FA8C
void CScreenElement_SetScale(SA *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1) {
    volatile double _dummy;
    volatile double _dummy2;
    f32 var_f30;
    register f32 var_f31 __asm__("fr31");
    SP *temp_r9;
    SP *temp_r9_2;
    SP *temp_r9_3;
    SP *var_r11;
    SQ *temp_r9_4;

    var_f30 = farg0;
    temp_r9 = (SP *) ((char *)arg0 + 0xD0);
    var_f31 = farg1;
    __asm__("" : "+f"(var_f30));
    __asm__("" : "+f"(var_f31));
    if ((temp_r9->f2C != var_f30) || (temp_r9->f30 != var_f31) || (arg1 != 0)) {
        if (arg1 == 0) {
            temp_r9_2 = (SP *) ((char *)arg0 + 0xD0);
            __asm__("" : "+r"(temp_r9_2));
            temp_r9_2->f34 = var_f30;
            temp_r9_2->f38 = var_f31;
            var_r11 = temp_r9_2;
            __asm__("" : "+r"(var_r11));
        } else {
            temp_r9_3 = (SP *) ((char *)arg0 + 0xD0);
            var_f30 = var_f30 * temp_r9_3->f34;
            var_f31 = var_f31 * temp_r9_3->f38;
            var_r11 = temp_r9_3;
            __asm__("" : "+r"(var_r11));
        }
        var_r11->f2C = var_f30;
        var_r11->f30 = var_f31;
        fn_8004195C((void *)arg0, (void *)var_r11);
        arg0->f_0C = (s32) (arg0->f_0C | 0x400);
    }
    if ((arg2 != 0) && ((temp_r9_4 = (SQ *) ((char *)arg0 + 0x88), ((temp_r9_4->f2C != var_f30) || (temp_r9_4->f30 != var_f31))))) {
        temp_r9_4->f2C = var_f30;
        temp_r9_4->f30 = var_f31;
        arg0->f_0C = (s32) (arg0->f_0C | 0x400);
    }
}
