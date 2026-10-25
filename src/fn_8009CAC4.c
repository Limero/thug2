// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009CAC4-0x8009CB5C (152B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80297868[];
void fn_8009CAC4(CStruct *arg0, s32 arg1) {
    void *temp_r11;
    Unk_4E705049 *temp_r9;
    Unk_C8FEE62D *temp_r9_2;

    fn_8009CD60();
    temp_r11 = arg0->unk0x4;
    if (temp_r11 != NULL) {
        temp_r9 = ((CScript *)temp_r11)->unk0x18;
        ((s32 (*)(void *, s32))temp_r9->unk0x1C)(temp_r11 + temp_r9->unk0x18, 3);
    }
    temp_r9_2 = (char *)arg0 + 8;
    temp_r9_2->unk0x14 = (s32)lbl_80297868;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9_2) + 0x10) + 0xC) =  temp_r9_2->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9_2) + 0xC) + 0x10) =  temp_r9_2->unk0x10;
    temp_r9_2->unk0xC = temp_r9_2;
    temp_r9_2->unk0x10 = temp_r9_2;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
