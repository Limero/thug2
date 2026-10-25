// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80068460-0x80068510 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { char _0[0x8]; s16 unk0x8; char _A[2]; s32 unk0xC; } VT;
typedef struct { char _0[0x14]; VT *unk0x14; } CH1;
typedef struct { char _0[0x18]; VT *unk0x18; } CH2;
typedef struct { CH2 *unk0x0; s32 unk0x4; char _8[8]; CH1 *unk0x10; char _14[0x14]; s32 unk0x28; } OB;
void fn_800685A4(OB *);
void fn_8000F9C4(s32, s32);
void Mem_Free(void *);
extern char lbl_802948D0[];
extern s32 lbl_802FFE98;
void fn_80068460(OB *arg0, s32 arg1) {
    CH1 *temp_r11;
    CH2 *temp_r11_2;
    VT *temp_r9;
    VT *temp_r9_2;
    temp_r11 = arg0->unk0x10;
    arg0->unk0x28 = (s32)lbl_802948D0;
    if (temp_r11 != NULL) {
        temp_r9 = temp_r11->unk0x14;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)((char *)temp_r11 + temp_r9->unk0x8, 3);
    }
    fn_800685A4(arg0);
    fn_8000F9C4(lbl_802FFE98, arg0->unk0x4);
    temp_r11_2 = arg0->unk0x0;
    if (temp_r11_2 != NULL) {
        temp_r9_2 = temp_r11_2->unk0x18;
        ((s32 (*)(void *, s32))temp_r9_2->unk0xC)((char *)temp_r11_2 + temp_r9_2->unk0x8, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
