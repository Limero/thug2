// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F5808-0x800F596C (356B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern void fn_80010D94(s32, s32);
extern s32 fn_800F3690(s32, s32, s32, s32, s32, s32);
extern void fn_800F5AD0(Unk_C7387A53 *, void *, CStruct *);
extern void sGenerateCollisionFilename(void *, void *);
extern void *fn_8001371C(Unk_C8FEE62D *, s32, s32);
extern void fn_8001075C(void *);
extern s32 fn_800132A4(CStruct *);
extern s32 Mem_Alloc_3(s32);
extern void fn_80010760(void);
extern void fn_80013294(CStruct *, s32, void *, s32);
extern void fn_800132F8(Unk_DB0E2BAB *, void *, s32, s32);
extern void fn_80010E78(s32);
extern void fn_800F39DC(void *, void *, s32, Unk_C7387A53 *, s32);

s32 fn_800F5808(Unk_C7387A53 *arg0, void *arg1, s32 arg2, s32 arg3, void *arg4, CStruct *arg5) {
    char sp8[0x100];
    s32 temp_r30;
    void *temp_r3;
    Unk_2C7D9FAD *temp_r9;

    temp_r9 = *(void **)&lbl_802FFE98;
    fn_80010D94(temp_r9->unk0x11C, 0x20);
    fn_800F3690(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_800F5AD0(arg0, arg4, arg5);
    strcpy(*((char * *)&arg0->unk0x54) + 4, arg1);
    sGenerateCollisionFilename(sp8, arg1);
    temp_r3 = fn_8001371C(sp8, arg2 ^ 1, 0x64);
    arg0->unk0x20 = temp_r3;
    if (temp_r3 == NULL) {
        return -1;
    }
    {
        fn_8001075C(sp8);
        temp_r30 = fn_800132A4(arg0->unk0x20);
        arg0->unk0x24 = Mem_Alloc_3(temp_r30);
        fn_80010760();
        if (arg2 != 0) {
            *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x20) + 0x10) = 0;
            temp_r9 = arg0->unk0x20;
            temp_r9->unk0x10 = (s32) (temp_r9->unk0x10 | 8);
            fn_80013294(arg0->unk0x20, (s32)fn_800F39DC, arg0, 0);
        }
        fn_800132F8(arg0->unk0x20, arg0->unk0x24, 1, temp_r30);
        if (arg2 == 0) {
            arg0->unk0x28 = temp_r30;
            temp_r9 = arg0->unk0x50;
            ((void (*)(void *))temp_r9->unk0x6C)((char *)arg0 + temp_r9->unk0x68);
        }
        fn_80010E78(*(s32 *)((char *)(*(void **)&lbl_802FFE98) + (s32)0x11C));
        return 0;
    }
}
