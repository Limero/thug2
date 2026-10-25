// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016CEC4-0x8016CFDC (280B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A8B40[];
extern s32 lbl_80305E9C;
void fn_8009C8A8(Unk_C8FEE62D * arg0, s32 arg1);
void fn_8016CEC4(Unk_9AA07378 *arg0, s32 arg1) {
    void *temp_r11;
    Unk_4E705049 *temp_r9;

    temp_r11 = *((void * *)&arg0->unk0x54);
    arg0->unk0x14 = (s32)lbl_802A8B40;
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_82779A3F *)temp_r11)->unk0x2300;
        ((void (*)(void *, s32)) *((void * *)&temp_r9->unk0xC))(temp_r11 + temp_r9->unk0x8, 3);
    }
    temp_r11 = *((void * *)&arg0->unk0x18);
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_82779A3F *)temp_r11)->unk0x18;
        ((void (*)(void *, s32)) *((void * *)&temp_r9->unk0x1C))(temp_r11 + temp_r9->unk0x18, 3);
    }
    temp_r11 = *((void * *)&arg0->unk0x20);
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_82779A3F *)temp_r11)->unk0x18;
        ((void (*)(void *, s32)) *((void * *)&temp_r9->unk0x1C))(temp_r11 + temp_r9->unk0x18, 3);
    }
    temp_r11 = *((void * *)&arg0->unk0x24);
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_82779A3F *)temp_r11)->unk0x18;
        ((void (*)(void *, s32)) *((void * *)&temp_r9->unk0x1C))(temp_r11 + temp_r9->unk0x18, 3);
    }
    temp_r11 = *((void * *)&arg0->unk0x1C);
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_82779A3F *)temp_r11)->unk0x18;
        ((void (*)(void *, s32)) *((void * *)&temp_r9->unk0x1C))(temp_r11 + temp_r9->unk0x18, 3);
    }
    lbl_80305E9C = 0;
    fn_8009C8A8(arg0, arg1);
}
