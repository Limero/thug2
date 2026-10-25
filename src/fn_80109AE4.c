// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80109AE4-0x80109C40 (348B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_80302BE8;
extern f32 lbl_80302BEC;
extern f32 lbl_80302BF0;
extern f32 lbl_80302BF4;
extern s32 lbl_80302C08;
extern char lbl_80302C10[];
extern char lbl_80302C14[];
extern s32 lbl_80366478;
extern char lbl_803830B0[];
extern s32 fn_8005CF80(Unk_9994C3F5 *, s32);
void fn_80109AE4(Unk_69F3F3BE *arg0, s32 arg1) {
    Unk_9994C3F5 *temp_r11;
    Unk_3AC3BC42 *temp_r9;
    s32 var_r3;
    s32 var_r4;
    s32 zero;

    if (arg1 & 1) {
        lbl_80302BE8 = *((f32 *)&arg0->unk0x0);
    }
    if (arg1 & 2) {
        lbl_80302BEC = *((f32 *)&arg0->unk0x4);
    }
    if (arg1 & 4) {
        lbl_80302BF0 = arg0->unk0x8;
    }
    if (arg1 & 8) {
        lbl_80302BF4 = arg0->unk0xC;
    }
    if (arg1 & 0x10) {
        temp_r9 = &lbl_803830B0;
        temp_r9->unk0x0 = arg0->unk0x18;
        *((__ps_t *)&((Unk_B0F7076A_2 *)temp_r9)->unk0x8) = arg0->unk0x20;
    }
    if (arg1 & 0x80) {
        lbl_80302C08 = arg0->unk0x40;
    }
    if (arg1 & 0x20) {
        temp_r11 = *(void **)&lbl_80302C10;
        if (temp_r11 != NULL) {
            temp_r9 = *((void * *)&temp_r11->unk0x8);
            temp_r9->unk0xC((char *)temp_r11 + ((Unk_B0F7076A_2 *)temp_r9)->unk0x8, 3);
        }
        var_r3 = lbl_80366478;
        zero = 0;
        __asm__("" : "+r"(zero));
        var_r4 = arg0->unk0x10;
        *(void **)&lbl_80302C10 = (void *)zero;
        *(void **)&lbl_80302C10 = (void *)fn_8005CF80(var_r3, var_r4);
    }
    if (arg1 & 0x40) {
        if (*(void **)&lbl_80302C14 != NULL) {
            temp_r11 = *(void **)&lbl_80302C10;
            if (temp_r11 != NULL) {
                temp_r9 = *((void * *)&temp_r11->unk0x8);
                temp_r9->unk0xC((char *)temp_r11 + ((Unk_B0F7076A_2 *)temp_r9)->unk0x8, 3);
            }
        }
        *(void **)&lbl_80302C14 = (void *)fn_8005CF80(lbl_80366478, arg0->unk0x14);
    }
}
