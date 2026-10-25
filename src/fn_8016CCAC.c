// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016CCAC-0x8016CD30 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80009C00(CStruct * arg0);
void fn_801396A4(void *arg0);
void fn_8016CCAC(Unk_A9157FE7 *arg0) {
    void *temp_r11;
    Unk_F5317C5D *temp_r9;

    temp_r11 = *((void * *)&arg0->unk0x58);
    if (temp_r11 != NULL) {
        temp_r9 = *((void * *)&((Unk_9994C3F5 *)temp_r11)->unk0x8);
        ((void (*)(void *, s32)) *((void * *)&temp_r9->unk0xC))(temp_r11 + temp_r9->unk0x8, 3);
        arg0->unk0x58 = 0;
    }
    fn_80009C00(*((void * *)&arg0->unk0x18));
    fn_80009C00(*((void * *)&arg0->unk0x20));
    fn_80009C00(*((void * *)&arg0->unk0x24));
    fn_80009C00(*((void * *)&arg0->unk0x1C));
    fn_801396A4(arg0->unk0x54 + 4);
}
