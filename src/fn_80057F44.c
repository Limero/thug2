// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057F44-0x80057FBC (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct VT_7A53 {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0x28];
    s16 unk0x38;
    char pad0x3A[0x2];
    s32 unk0x3C;
} VT_7A53;

void fn_8005F36C(s32, s32);

void fn_80057F44(void *arg0, s32 arg1) {
    void *temp_r11;
    VT_7A53 *temp_r9;
    s32 temp_r0;

    temp_r11 = *(void **)((char *)arg0 + 0x14);
    if (temp_r11 != NULL) {
        temp_r9 = *(VT_7A53 **)((char *)temp_r11 + 0xC);
        ((s32 (*)(void *))temp_r9->unk0x3C)((char *)temp_r11 + temp_r9->unk0x38);
        temp_r0 = *(s32 *)((char *)arg0 + 0x4);
        if (temp_r0 & 0x40) {
            *(s32 *)((char *)arg0 + 0x4) = (s32) (temp_r0 | 0x20);
        }
    }
    if (*(s32 *)((char *)arg0 + 0x10) != 0) {
        fn_8005F36C(*(s32 *)((char *)arg0 + 0x10), arg1);
    }
}
