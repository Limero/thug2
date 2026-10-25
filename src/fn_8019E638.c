// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019E638-0x8019E6F8 (192B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AAF6C[];
void sprintf(s32, ...);
void fn_8012EABC(void *, s32, s32);
s32 fn_80131714(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);

bool fn_8019E638(Unk_DB0E2BAB *arg0) {
    char sp10[0x100];
    s32 temp_r29;
    void *temp_r30;
    Unk_FFAD6788 *temp_r3;
    void *temp_r31;

    temp_r30 = arg0->unk0x0;
    temp_r29 = arg0->unk0x18;
    sprintf((s32)&sp10[0], (s32)lbl_802AAF6C, (s32)temp_r30);
    fn_8012EABC(&sp10[0], 0, 0);
    temp_r3 = fn_80131714((s32)temp_r30, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    temp_r31 = (void *)((char *)temp_r3 + (s32)0xBC);
    if (temp_r3->unk0xBC != 0) {
        CObject_RemoveRefLink(*(void **)temp_r31, temp_r31);
        temp_r3->unk0xBC = 0;
    }
    temp_r3->unk0xBC = temp_r29;
    if (temp_r29 != 0) {
        CObject_AddRefLink((void *)temp_r29, temp_r31);
    }
    return true;
}
