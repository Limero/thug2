// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A3DC-0x8000A510 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8028FF88[];
extern void fn_8000A19C(void *, s32);
void fn_8000A3DC(void *arg0) {
    s32 sp8[4];
    char *bp;
    register s32 bp2s __asm__("r30");
    s32 temp_r10;
    void *temp_r10_2;
    void *temp_r8;
    void *temp_r9;
    void *var_r11;
    void *var_r9;

    bp = (char *)&sp8[0];
    temp_r10 = (s32)arg0 + 0xC;
    *(s32 *)((char *)bp + 8) = lbl_8028FF88;
    *(s32 *)((char *)bp + 4) = (void *)temp_r10;
    bp2s = (s32)bp;
    var_r11 = (void *)(*(s32 *)((char *)temp_r10 + (s32)0xC));
    if ((s32) *(s32 *)((char *)var_r11 + (s32)0x4) == -1) {
        var_r11 = NULL;
    }
    *(s32 *)((char *)bp2s + 4) = var_r11;
    if ( *(s32 *)((char *)arg0 + (s32)0x40) ==  *(s32 *)((char *)arg0 + (s32)0x3C)) {
        var_r9 = *(s32 *)((char *)var_r11 + (s32)0xC);
        if ((s32) *(s32 *)((char *)var_r9 + (s32)0x4) == -1) {
            var_r9 = NULL;
        }
        *(s32 *)((char *)bp2s + 4) = var_r9;
        if (var_r9 == NULL) {
            __asm__("" : "+r"(var_r9));
            var_r9 = NULL;
        } else {
            var_r9 = *(s32 *)((char *)var_r9 + (s32)0x4);
        }
        *(s32 *)((char *)arg0 + (s32)0x40) = var_r9;
    } else {
        *(s32 *)((char *)arg0 + (s32)0x44) = 0;
    }
    if ((s32) *(s32 *)((char *)arg0 + (s32)0x4) == 0) {
        if ( *(s32 *)((char *)arg0 + (s32)0x3C) != NULL) {
            fn_8000A19C(*(void **)((char *)arg0 + 0x3C), 3);
        }
    } else {
        temp_r8 = arg0 + 0x24;
        temp_r9 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x3C) + 0x28);
        *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0x10) + 0xC) =  *(s32 *)((char *)temp_r9 + (s32)0xC);
        *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0xC) + 0x10) =  *(s32 *)((char *)temp_r9 + (s32)0x10);
        *(s32 *)((char *)temp_r9 + (s32)0xC) = temp_r9;
        *(s32 *)((char *)temp_r9 + (s32)0x10) = temp_r9;
        temp_r10_2 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x3C) + 0x28);
        *(s32 *)((char *)temp_r10_2 + (s32)0x10) = temp_r8;
        *(s32 *)((char *)temp_r10_2 + (s32)0xC) =  *(s32 *)((char *)temp_r8 + (s32)0xC);
        *(s32 *)(*(s32 *)((char *)((char *)temp_r8) + 0xC) + 0x10) = temp_r10_2;
        *(s32 *)((char *)temp_r8 + (s32)0xC) = temp_r10_2;
    }
    *(s32 *)((char *)arg0 + (s32)0x3C) =  *(s32 *)((char *)arg0 + (s32)0x40);
    *(s32 *)((char *)arg0 + (s32)0x48) = 1;
    *(s32 *)((char *)bp2s + 8) = lbl_8028FF88;
}
