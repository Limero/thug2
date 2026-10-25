// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009B6AC-0x8009B9D4 (808B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
#include "qb_constants.h"

typedef union {
    s32 w;
    u8 b[4];
} Tok32;

typedef struct {
    s32 unk0x0;
    u8 unk0x4;
    u8 unk0x5;
    u8 unk0x6;
    u8 unk0x7;
    u8 unk0x8;
    u8 unk0x9;
    u16 unk0xA;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
} ImgDesc;

s32 fn_800146E0(s32 arg0);
s32 fn_800147E8(void *arg0, void *arg1);
s32 fn_80014898(s32 arg0);
s32 fn_80014904(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void *fn_8009B5D8(void *arg0);
void fn_80010D94(s32 arg0, s32 arg1);
void fn_80010E78(s32 arg0);
extern char lbl_8029766C[];
extern void *lbl_802FFE98;
extern s32 lbl_803018F8;

ImgDesc *fn_8009B6AC(void *arg0) {
    Tok32 sp28;
    Tok32 sp24;
    Tok32 sp20;
    Tok32 sp1C;
    Tok32 sp18;
    Tok32 sp14;
    Tok32 sp10;
    Tok32 spC;
    u16 spA;
    u16 sp8;
    ImgDesc *var_r24;
    s32 var_r25;
    s32 temp_r3;
    s32 temp_r0a;
    s32 temp_r0b;
    s32 var_r30;
    s32 var_r11;
    u16 var_r10;
    s32 var_r9;
    s32 temp_w;

    var_r24 = NULL;
    temp_r3 = (s32)fn_800147E8(arg0, lbl_8029766C);
    if (temp_r3 != 0) {
        var_r25 = fn_800146E0(temp_r3);
        var_r24 = (ImgDesc *)fn_8009B5D8(Mem_Alloc2(0x1C));
        fn_80014904(&spC, 4, 1, temp_r3);
        fn_80014904(&sp10, 4, 1, temp_r3);
        fn_80014904(&sp14, 4, 1, temp_r3);
        fn_80014904(&sp18, 4, 1, temp_r3);
        fn_80014904(&sp1C, 4, 1, temp_r3);
        fn_80014904(&sp20, 4, 1, temp_r3);
        fn_80014904(&sp24, 4, 1, temp_r3);
        fn_80014904(&sp28, 4, 1, temp_r3);
        fn_80014904(&sp8, 2, 1, temp_r3);
        fn_80014904(&spA, 2, 1, temp_r3);
        var_r24->unk0xA = 4;
        fn_80010D94(*(s32 *)((char *)lbl_802FFE98 + 0x11C), 0x20);
        var_r25 -= 0x24;
        if (var_r25 == (sp14.w * sp18.w * 4)) {
            var_r24->unk0x9 = 6;
            temp_r0a = (s32)Mem_Alloc(var_r25);
            var_r24->unk0xC = var_r25;
            var_r24->unk0x10 = temp_r0a;
            fn_80014904((void *)temp_r0a, 1, var_r25, temp_r3);
        } else {
            var_r24->unk0x9 = 0xE;
            if (sp8 != 0) {
                var_r25 = (s32) ((u32) var_r25 >> 1U);
            }
            var_r30 = var_r25;
            if (lbl_803018F8 != 0) {
                var_r30 = var_r25 * 8;
                var_r24->unk0xA |= 0x100;
            }
            temp_r0b = (s32)Mem_Alloc(var_r30);
            var_r24->unk0xC = var_r30;
            var_r24->unk0x10 = temp_r0b;
            fn_80014904((void *)temp_r0b, 1, var_r25, temp_r3);
            if (sp8 != 0) {
                if (var_r24->unk0xA & 0x100) {
                    var_r24->unk0x14 = (s32) ((var_r24->unk0x10 + (var_r30 >> 1)) & QB_UNKNOWN_0xFFFFFFE0);
                } else {
                    var_r24->unk0x14 = (s32)Mem_Alloc(var_r25);
                }
                fn_80014904((void *)var_r24->unk0x14, 1, var_r25, temp_r3);
                var_r24->unk0xA |= 0x22;
            }
        }
        fn_80010E78(*(s32 *)((char *)lbl_802FFE98 + 0x11C));
        var_r24->unk0x0 = sp10.w;
        temp_w = sp24.w;
        var_r9 = 3;
        if (temp_w > 8) {
            do {
                var_r9 += 1;
            } while ((s32) (1 << var_r9) < temp_w);
        }
        var_r24->unk0x6 = var_r9;
        temp_w = sp28.w;
        var_r9 = 3;
        if (temp_w > 8) {
            do {
                var_r9 += 1;
            } while ((s32) (1 << var_r9) < temp_w);
        }
        var_r24->unk0x7 = var_r9;
        var_r11 = 1;
        var_r10 = var_r24->unk0xA;
        var_r24->unk0x4 = sp24.b[3] - sp14.b[3];
        var_r24->unk0x5 = sp28.b[3] - sp18.b[3];
        var_r24->unk0x8 = sp20.b[3];
        if (spA == 0) {
            var_r11 = 0;
        }
        var_r11 |= var_r10;
        var_r24->unk0xA = (u16) var_r11;
        /* zero-byte scheduler barrier: keeps the fn_80014898 argument copy
           below the store above (see header).  DO NOT "clean this up". */
        while (0) {
        }
        fn_80014898(temp_r3);
    }
    return var_r24;
}
