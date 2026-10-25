// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F5414-0x800F551C (264B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern char lbl_8029BAF8[];
s32 fn_80010D94(s32, s32);
s32 fn_800F36C8(void *, s32, s32, s32, s32, s32);
void fn_800F551C(Unk_C7387A53 *, Unk_DB0E2BAB *, CStruct *);
s32 sprintf(s32, ...);
s32 Mem_Alloc_3(s32);
void fn_8001075C(s32);
void fn_80010760(void);
s32 fn_80010E78(s32);
void *memcpy(void *, const void *, s32);

bool fn_800F5414(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, Unk_DB0E2BAB *arg4, CStruct *arg5) {
    char sp8[0x100];
    Unk_0E2E8431 *temp_r9;
    s32 temp_r0;

    fn_80010D94(*(s32 *)((char *)(*(void **)&lbl_802FFE98) + (s32)0x11C), 0x20);
    fn_800F36C8(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_800F551C(arg0, arg4, arg5);
    if ((arg3 != 0) && (*(s32 *)(arg0->unk0x58 + (s32)0x14) == 0)) {
        sprintf(&sp8, (s32)lbl_8029BAF8);
        fn_8001075C(&sp8);
        temp_r0 = Mem_Alloc_3(arg2);
        arg0->unk0x24 = temp_r0;
        memcpy(temp_r0, arg1, arg2);
        arg1 = arg0->unk0x24;
        fn_80010760();
    }
    temp_r9 = *((void * *)&arg0->unk0x50);
    ((s32 (*)(void *, void *, void *))temp_r9->unk0x74)(
        (char *)arg0 + temp_r9->unk0x70, arg1, arg2);
    fn_80010E78(*(s32 *)((char *)(*(void **)&lbl_802FFE98) + (s32)0x11C));
    return false;
}
