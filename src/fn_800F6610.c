// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F6610-0x800F67BC (428B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern Unk_9994C3F5 *lbl_802FFE98;
extern s32 fn_800F3690(s32, s32, s32, s32, s32, s32);
extern void fn_800F682C(void *, void *, void *);
extern s32 fn_8000F2F8(Unk_9F352E7C *, s32);
extern void LowerCase(u8 *);
extern s32 fn_8000A778(char *);
extern s32 fn_800127E4(Unk_C8FEE62D *, s32, void *, s32, s32);
extern s32 fn_80012AB4(s32);
extern void *fn_8001371C(Unk_C8FEE62D *, s32, s32);
extern s32 fn_800132A4(CStruct *);
extern void fn_80010D94(s32, s32);
extern s32 Mem_Alloc_3(s32);
extern void fn_80010E78(s32);
extern void fn_80013294(CStruct *, s32, void *, s32);
extern void fn_800132F8(Unk_DB0E2BAB *, void *, s32, s32);
extern void fn_8000F320(Unk_F12C5E01 *);
extern void fn_800F39DC(void *, void *, s32, Unk_C7387A53 *, s32);

s32 fn_800F6610(Unk_A9157FE7 *arg0, Unk_C8FEE62D *arg1, s32 arg2, s32 arg3, void *arg4, void *arg5) {
    char sp8[0x100];
    s32 temp_r30;
    void *temp_r3;
    Unk_2C7D9FAD *temp_r9;

    fn_800F3690(arg0, arg1, arg2, arg3, arg4, arg5);
    fn_800F682C(arg0, arg4, arg5);
    strcpy(*((char * *)&arg0->unk0x64), arg1);
    fn_8000F2F8((Unk_9F352E7C *)lbl_802FFE98, lbl_802FFE98->unk0x118);
    if (arg3 != 0) {
        strcpy(sp8, arg1);
        LowerCase(sp8);
        arg0->unk0x54 = fn_8000A778(sp8);
        arg0->unk0x24 = fn_800127E4((s32)arg1, 0, 0, 0, 0);
        temp_r30 = fn_80012AB4(arg1);
    } else {
        temp_r3 = fn_8001371C(arg1, arg2 ^ 1, 0x64);
        arg0->unk0x20 = temp_r3;
        if (temp_r3 == NULL) {
            return -1;
        }
        temp_r30 = fn_800132A4(temp_r3);
        fn_80010D94(lbl_802FFE98->unk0x11C, 0x20);
        arg0->unk0x24 = Mem_Alloc_3(temp_r30);
        fn_80010E78(lbl_802FFE98->unk0x11C);
        if (arg2 != 0) {
            *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x20) + 0x10) = arg3;
            temp_r9 = arg0->unk0x20;
            temp_r9->unk0x10 = (s32) (temp_r9->unk0x10 | 8);
            fn_80013294(arg0->unk0x20, (s32)fn_800F39DC, arg0, 0);
        }
        fn_800132F8(arg0->unk0x20, arg0->unk0x24, 1, temp_r30);
    }
    if (arg2 == 0) {
        *((s32 *)&arg0->unk0x28) = temp_r30;
        temp_r9 = arg0->unk0x50;
        ((void (*)(void *))temp_r9->unk0x6C)((char *)arg0 + temp_r9->unk0x68);
    }
    fn_8000F320((Unk_F12C5E01 *)lbl_802FFE98);
    return 0;
}
