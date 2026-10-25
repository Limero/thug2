// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801370C4-0x801371D4 (272B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void *lbl_802FFE98;
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern s32 fn_80137A84(Unk_F386DC9F * arg0);
extern void *fn_80139450(void *arg0, s32 arg1);
extern s32 fn_8013E2BC(Unk_440CB216 * arg0);
extern void fn_8013AC98(void *arg0, s32 arg1, s32 arg2);
extern void fn_80136F1C(s32 arg0, Unk_9C44AE00 * arg1);
extern void fn_8000F320(Unk_F12C5E01 * arg0);
extern char *strncpy(char *, char *, s32);

void *fn_801370C4(Unk_F386DC9F *arg0, s32 arg1, char *arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 var;
    void *p;
    CStruct *temp_r10;
    CStruct *temp_r11;
    void *temp_r3;
    Unk_B1B57F13 *temp_r9;

    fn_8000F2F8(lbl_802FFE98, ((Unk_FFAD6788 *)lbl_802FFE98)->unk0x134);
    if (fn_80137A84(arg0) != 0) {
        arg4 = 0;
    }
    temp_r3 = fn_80139450(Mem_Alloc2(0x2310), arg5);
    strncpy((char *)temp_r3 + 0x22B0, arg2, 0x40);
    temp_r9 = ((Unk_125EE9F6 *)temp_r3)->unk0x2300;
    ((Unk_125EE9F6 *)temp_r3)->unk0x1830 = (s32)arg0;
    ((s32 (*)(void *))temp_r9->unk0x2C)(
        temp_r3 + temp_r9->unk0x28);
    ((Unk_125EE9F6 *)temp_r3)->unk0x22AC = arg1;
    ((Unk_125EE9F6 *)temp_r3)->unk0x1848 = 1;
    temp_r10 = (char *)arg0 + 0x1C;
    temp_r11 = (char *)temp_r3 + 0x1808;
    temp_r11->unk0x10 = temp_r10->unk0x10;
    temp_r11->unk0xC = temp_r10;
    *(s32 *)(temp_r10->unk0x10 + 0xC) = temp_r11;
    temp_r10->unk0x10 = temp_r11;
    if (fn_8013E2BC(temp_r3) == 0) {
        fn_8013AC98(temp_r3, arg4, arg3);
    }
    fn_80136F1C(arg0, temp_r3);
    var = arg0->unk0x22E8;
    var = var + 1;
    p = lbl_802FFE98;
    arg0->unk0x22E8 = var;
    fn_8000F320(p);
    return temp_r3;
}
