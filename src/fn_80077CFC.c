// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077CFC-0x80077F7C (640B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void DCFlushRange(s32, s32);
s32 Mem_Alloc(s32);
void Mem_Free2(void *);
void fn_80010D94(s32, s32);
void fn_80010E78(s32);
extern void *lbl_802FFE98;

bool fn_80077CFC(void *arg0, void *arg1) {
    u8 staged;
    u16 temp_r10;
    u16 temp_r11;
    void *src;
    void *dst;

    fn_80010D94(*(s32 *)((char *)lbl_802FFE98 + 0x11C), 0x20);
    src = *(void **)((char *)arg1 + 0xC);
    dst = *(void **)((char *)arg0 + 0xC);
    if ((*(s32 *)((char *)src + 8) & 0x202) == 2) {
        if ((*(s32 *)((char *)dst + 8) & 0x3C) == 4) {
            *(s32 *)((char *)dst + 0x18) = *(s32 *)((char *)dst + 0x14);
            *(u16 *)((char *)dst + 0xA) = *(u16 *)((char *)dst + 0xA) | 0x40;
        }
        if (((u32) *(s32 *)((char *)dst + 0xC) < (u32) *(s32 *)((char *)src + 0xC)) ||
            ((*(s32 *)((char *)dst + 8) & 0x3C) != 0x24))
        {
            if ((*(s32 *)((char *)dst + 0x14) != 0) &&
                ((u32) *(s32 *)((char *)dst + 0xC) < (u32) *(s32 *)((char *)src + 0xC)) &&
                ((*(s32 *)((char *)dst + 8) & 0x3C) == 0x24))
            {
                Mem_Free2(*(void **)((char *)dst + 0x14));
            }
            temp_r11 = *(u16 *)((char *)dst + 0xA);
            if (temp_r11 & 0x100) {
                *(u16 *)((char *)dst + 0xA) = temp_r11 | 0x200;
                *(s32 *)((char *)dst + 0x14) = *(s32 *)((char *)dst + 0x10) + ((u32) *(s32 *)((char *)dst + 0xC) >> 1U);
            } else {
                *(s32 *)((char *)dst + 0x14) = Mem_Alloc(*(s32 *)((char *)src + 0xC));
            }
        }
    }
    if ((u32) *(s32 *)((char *)dst + 0xC) < (u32) *(s32 *)((char *)src + 0xC)) {
        if (*(s32 *)((char *)dst + 0x10) != 0) {
            Mem_Free2(*(void **)((char *)dst + 0x10));
        }
        *(void **)((char *)dst + 0x10) = (void *)Mem_Alloc(*(s32 *)((char *)src + 0xC));
        *(s32 *)((char *)dst + 0xC) = *(s32 *)((char *)src + 0xC);
    }
    *(u8 *)((char *)dst + 4) = *(u8 *)((char *)src + 4);
    *(u8 *)((char *)dst + 5) = *(u8 *)((char *)src + 5);
    *(u8 *)((char *)dst + 6) = *(u8 *)((char *)src + 6);
    *(u8 *)((char *)dst + 7) = *(u8 *)((char *)src + 7);
    *(u16 *)((char *)dst + 0xA) = (u16) ((*(u16 *)((char *)dst + 0xA) & 0xFFFE) | (*(u16 *)((char *)src + 0xA) & 1));
    if (*(u16 *)((char *)src + 0xA) & 0x200) {
        *(u16 *)((char *)dst + 0xA) = 3;
    }
    memcpy(*(void **)((char *)dst + 0x10), *(void **)((char *)src + 0x10), *(s32 *)((char *)src + 0xC));
    DCFlushRange(*(s32 *)((char *)dst + 0x10), *(s32 *)((char *)src + 0xC));
    if (!(*(u16 *)((char *)src + 0xA) & 0x200)) {
        if (*(s32 *)((char *)src + 0x14) != 0) {
            if (*(s32 *)((char *)dst + 0x14) != 0) {
                memcpy(*(void **)((char *)dst + 0x14), *(void **)((char *)src + 0x14), *(s32 *)((char *)src + 0xC));
                DCFlushRange(*(s32 *)((char *)dst + 0x14), *(s32 *)((char *)src + 0xC));
                *(u16 *)((char *)dst + 0xA) = (u16) ((((*(u16 *)((char *)dst + 0xA) & 0xFFFD) | (*(u16 *)((char *)src + 0xA) & 2)) & 0xFFE3) | 0x24);
            }
        }
    } else {
        *(s32 *)((char *)dst + 0x14) = 0;
    }
    if ((*(s32 *)((char *)dst + 0x14) != 0) && (*(s32 *)((char *)src + 0x14) == 0)) {
        *(u16 *)((char *)dst + 0xA) = *(u16 *)((char *)dst + 0xA) & 0xFFFD;
    }
    staged = 0;
    temp_r10 = *(u16 *)((char *)dst + 0xA);
    *(u8 *)((char *)dst + 8) = staged;
    staged = *(u8 *)((char *)src + 9);
    *(u16 *)((char *)dst + 0xA) = temp_r10 | 0x80;
    *(u8 *)((char *)dst + 9) = staged;
    if (*(u16 *)((char *)src + 0xA) & 0x100) {
        *(u16 *)((char *)dst + 0xA) = temp_r10 | 0x180;
    }
    if (*(u16 *)((char *)src + 0xA) & 0x200) {
        *(u16 *)((char *)dst + 0xA) = *(u16 *)((char *)dst + 0xA) | 0x200;
    }
    fn_80010E78(*(s32 *)((char *)lbl_802FFE98 + 0x11C));
    return true;
}
