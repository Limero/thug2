// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E0B0-0x8009E1A0 (240B). Byte-identical.
#include "types.h"
#include "structs.h"
void CObject_dtor(Unk_9994C3F5 *, s32);
void CStruct_delete(CStruct *, s32);
void fn_8012EE64(Unk_069CE08E *, s32);
void fn_80131AF4(Unk_15EF4A35 *);
void fn_80132104(void);
extern char lbl_802929C8[];
extern char lbl_80297A00[];
void fn_8009E0B0(Unk_DB0E2BAB *arg0, s32 arg1) {
    void *temp_r11;
    Unk_4E705049 *temp_r9;
    Unk_C8FEE62D *temp_r9_2;
    s32 temp_r3_1;
    s32 temp_r3_2;

    arg0->unk0x8 = (s32)lbl_80297A00;
    temp_r3_1 = arg0->unk0x24;
    if (temp_r3_1 != 0) {
        CStruct_delete(temp_r3_1, 3);
    }
    temp_r11 = arg0->unk0x10;
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_C7387A53 *)temp_r11)->unk0x2C;
        ((s32 (*)(void *, void *))temp_r9->unk0x1C)(temp_r11 + temp_r9->unk0x18, arg0);
    }
    temp_r3_2 = arg0->unk0x14;
    if (temp_r3_2 != 0) {
        fn_80132104();
        temp_r3_2 = arg0->unk0x14;
        if (temp_r3_2 != 0) {
            fn_8012EE64(temp_r3_2, 3);
        }
        arg0->unk0x14 = 0;
    }
    fn_80131AF4(arg0);
    CObject_dtor((char *)arg0 + 0x48, 2);
    temp_r9_2 = (char *)arg0 + 0x2C;
    temp_r9_2->unk0x14 = (s32)lbl_802929C8;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9_2) + 0x10) + 0xC) =  temp_r9_2->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9_2) + 0xC) + 0x10) =  temp_r9_2->unk0x10;
    temp_r9_2->unk0xC = temp_r9_2;
    temp_r9_2->unk0x10 = temp_r9_2;
    CObject_dtor(arg0, arg1);
}
