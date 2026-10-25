// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80126468-0x8012653C (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFE54;
extern char lbl_802FFE98[];
extern char lbl_8029E5B0[];
void fn_8000F2F8(Unk_9F352E7C *arg0, s32 arg1);
s32 fn_800127E4(void *, s32, s32, s32, s32);
void fn_8000F320(Unk_F12C5E01 *self);
void *fn_80012AB4(void *);
void fn_80012A10(void *);
void fn_801263A0(u16 arg0, u8 *arg1);
void fn_8012653C(s32, void *, void (*)(u16, u8 *));
char *strcpy(char *, const char *);
void fn_80126468(char *arg0) {
    u8 sp8[0x100];
    u8 *p;
    s8 c;
    s32 temp_r30;
    Unk_C7387A53 *temp_r3;

    if (lbl_802FFE54 != 0) {
        strcpy((char *)sp8, arg0);
        p = sp8;
        c = sp8[0];
        while (c != 0 && c != 0x2E) {
            c = *++p;
        }
        temp_r3 = *(void **)lbl_802FFE98;
        *(u32 *)p = *(u32 *)lbl_8029E5B0;
        *(u8 *)(p + 4) = *(u8 *)(lbl_8029E5B0 + 4);
        fn_8000F2F8(temp_r3, temp_r3->unk0x12C);
        temp_r30 = fn_800127E4(sp8, 0, 0, 0, 0);
        fn_8000F320(*(void **)lbl_802FFE98);
        fn_8012653C(temp_r30, fn_80012AB4(sp8), fn_801263A0);
        fn_80012A10(sp8);
    }
}
