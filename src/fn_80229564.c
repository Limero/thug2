// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80229564-0x80229644 (224B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void CStruct_delete(CStruct *, s32);
extern void fn_8003A7A4(CStruct *, s32);
extern char lbl_802B0060[];
extern char lbl_802B0330[];
void fn_80229564(Unk_9D868A15 *arg0, s32 arg1) {
    void *temp_r11;
    void *temp_r30;
    Unk_4E705049 *temp_r9;

    temp_r30 = arg0->unk0x50;
    arg0->unk0x14 = (s32)lbl_802B0330;
    if (temp_r30 != NULL) {
        CStruct_delete(temp_r30 + 0x6C, 2);
        fn_8003A7A4(temp_r30 + 4, 2);
        Mem_Free(temp_r30);
    }
    temp_r11 = arg0->unk0x1F4;
    if (temp_r11 != NULL) {
        temp_r9 = ((CScript *)temp_r11)->unk0x18;
        ((s32 (*)(void *, s32))temp_r9->unk0x1C)(temp_r11 + temp_r9->unk0x18, 3);
    }
    if ((s32) arg0->unk0x1F0 != 0) {
        Mem_Free2(arg0->unk0x1F0);
        arg0->unk0x1F0 = 0;
    }
    arg0->unk0x14 = (s32)lbl_802B0060;
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x10) + 0xC) =  arg0->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x10) =  arg0->unk0x10;
    arg0->unk0xC = arg0;
    arg0->unk0x10 = arg0;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
