// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801251B4-0x80125230 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000F2F8(Unk_9F352E7C *, s32);
s32 strlen(char *);
void *Mem_Alloc_3(s32);
char *strcpy(char *, char *);
void fn_8000F320(Unk_F12C5E01 *);
s32 sAddToSpecialStringHeap(void *);
extern char lbl_802FFE98[];
extern bool lbl_80303184;
// CreateString @ 0x801251B4
s32 CreateString(char *arg0) {
    s32 temp_r29;
    Unk_C7387A53 *temp_r3;

    if (lbl_80303184 != 0) {
        return sAddToSpecialStringHeap(arg0);
    }
    temp_r3 = *(void * *)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x12C);
    temp_r29 = (s32)Mem_Alloc_3(strlen(arg0) + 1);
    strcpy((char *)temp_r29, arg0);
    fn_8000F320(*(void * *)&lbl_802FFE98);
    return temp_r29;
}
