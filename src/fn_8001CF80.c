// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001CF80-0x8001D010 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80362760[];
void PADInit(void);
void PADSetAnalogMode(s32);
void fn_8001CF80(void) {
    s32 var_ctr;
    void *var_r9;

    PADSetAnalogMode(3);
    PADInit();
    var_ctr = 4;
    var_r9 = (void *)lbl_80362760;
    do {
        *(u16 *)((char *)var_r9 + (s32)0x0) = 0;
        *(u8 *)((char *)var_r9 + (s32)0x2) = 0;
        *(u8 *)((char *)var_r9 + (s32)0x3) = 0;
        *(u8 *)((char *)var_r9 + (s32)0x4) = 0;
        *(u8 *)((char *)var_r9 + (s32)0x5) = 0;
        *(u8 *)((char *)var_r9 + (s32)0x6) = 0;
        *(u8 *)((char *)var_r9 + (s32)0x7) = 0;
        *(u8 *)((char *)var_r9 + (s32)0x8) = 0;
        *(u8 *)((char *)var_r9 + (s32)0x9) = 0;
        *(u8 *)((char *)var_r9 + (s32)0xA) = 0;
        *(u16 *)((char *)var_r9 + (s32)0xC) = 0;
        *(u16 *)((char *)var_r9 + (s32)0xE) = 0;
        *(u16 *)((char *)var_r9 + (s32)0x10) = 0;
        *(u16 *)((char *)var_r9 + (s32)0x12) = 0;
        *(u16 *)((char *)var_r9 + (s32)0x14) = 0;
        *(u16 *)((char *)var_r9 + (s32)0x16) = 0;
        *(u16 *)((char *)var_r9 + (s32)0x18) = 0;
        *(u16 *)((char *)var_r9 + (s32)0x1A) = 0;
        *(u16 *)((char *)var_r9 + (s32)0x1C) = 0;
        var_r9 += 0x1E;
        var_ctr -= 1;
    } while (var_ctr != 0);
}
