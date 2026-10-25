// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F4B98-0x800F4CC4 (300B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8029B99C[];
extern Unk_9994C3F5 *lbl_802FFE98;
extern s32 fn_8005570C(void);
extern s32 fn_800F39DC(void *, void *, s32, Unk_C7387A53 *, s32);
extern s32 fn_800F3690(s32);
extern void *fn_8001371C(Unk_C8FEE62D *, s32, s32);
extern s32 fn_800132A4(CStruct *);
extern s32 fn_8000F2F8(Unk_9994C3F5 *, s32);
extern s32 Mem_Alloc_3(s32);
extern s32 fn_8000F320(Unk_9994C3F5 *);
extern void fn_80013294(CStruct *, s32, void *, s32);
extern void fn_800132F8(Unk_DB0E2BAB *, void *, s32, s32);

s32 fn_800F4B98(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    char sp8[0x100];
    s32 temp_r30;
    void *temp_r3;
    Unk_2C7D9FAD *temp_r9;

    fn_800F3690(arg0);
    sprintf(sp8, (s32)lbl_8029B99C, arg1, fn_8005570C());
    temp_r3 = fn_8001371C(sp8, arg2 ^ 1, 0x64);
    arg0->unk0x20 = temp_r3;
    if (temp_r3 == NULL) {
        return -1;
    }
    {
        temp_r30 = fn_800132A4(temp_r3);
        fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->unk0x118);
        arg0->unk0x24 = Mem_Alloc_3(temp_r30);
        fn_8000F320(lbl_802FFE98);
        if (arg2 != 0) {
            *(s32 *)((char *)arg0->unk0x20 + 0x10) = 0;
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
        return 0;
    }
}
