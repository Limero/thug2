// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012788C-0x80127934 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80127438(void *, void *);
void fn_80128F44(s32 arg0);
#include "structs.h"
s32 fn_8009F4C4(s32);
void fn_8012788C(CStruct *arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2) {
    volatile double _dummy;
    volatile double _dummy1;
    volatile double _dummy2;
    CStruct *temp_r3;
    CStruct *temp_r3_2;

    fn_8009F4C4(0x10);
    temp_r3 = fn_801252BC();
    temp_r3->unk0x4 = arg1;
    ((struct { u32 a:9; u32 b:7; u32 c:16; } *)&temp_r3->unk0x0)->b = 6;
    fn_80128F44(0x10);
    temp_r3_2 = fn_80124FDC();
    temp_r3->unk0x8 = temp_r3_2;
    *(f32 *)((char *)temp_r3_2 + 0x4) = farg0;
    *(f32 *)((char *)(*(s32 *)((char *)((char *)temp_r3) + 0x8)) + 0x8) = farg1;
    *(f32 *)((char *)(*(s32 *)((char *)((char *)temp_r3) + 0x8)) + 0xC) = farg2;
    fn_80127438(arg0, temp_r3);
}
