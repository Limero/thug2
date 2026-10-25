// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800132F8-0x800133B4 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFF10;
s32 fn_8000E014(void *arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct {
    char pad0x0[0x10];
    s16 unk0x10;
    char pad0x12[2];
    void (*unk0x14)(void *, void *, s32, void *, s32);
    char pad0x18[0x60];
    s16 unk0x78;
    char pad0x7A[2];
    s32 (*unk0x7C)(void *, void *, s32, s32);
} Vt_800132F8;
s32 fn_800132F8(Unk_DB0E2BAB *arg0, void *arg1, s32 arg2, s32 arg3) {
    Vt_800132F8 *temp_r8;
    Vt_800132F8 *temp_r9;
    s32 temp_r9_2;
    s32 temp_r11;
    char *self = (char *)arg0;
    *(s32 *)(self + 0x14) = 3;
    temp_r9_2 = *(s32 *)(self + 0x34);
    if (temp_r9_2 != 0) {
        *(s32 *)self = fn_8000E014(arg1, arg2, arg3, temp_r9_2);
        temp_r8 = *(Vt_800132F8 **)(self + 0x3C);
        temp_r11 = *(volatile s32 *)&lbl_802FFF10;
        temp_r11 = temp_r11 + 1;
        lbl_802FFF10 = temp_r11;
        (*(volatile s32 *)(self + 0x38))++;
        *(volatile s32 *)(self + 0x38);
        temp_r8->unk0x14((char *)self + temp_r8->unk0x10, arg0->unk0x14, 0, *(volatile s32 *)self, 0);
        return *(s32 *)self;
    }
    temp_r9 = *(Vt_800132F8 **)(self + 0x3C);
    return ((s32 (*)(void *, void *, s32, s32))*((void * *)&temp_r9->unk0x7C))((char *)self + temp_r9->unk0x78, arg1, arg2, arg3);
}
