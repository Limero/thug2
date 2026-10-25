// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012772C-0x80127798 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80127438(void *, void *);
#include "structs.h"
s32 fn_8009F4C4(s32);
CStruct *fn_801252BC(void);
void fn_8012772C(CStruct *arg0, s32 arg1, f32 farg0) {
    volatile double _dummy;
    CStruct *temp_r3;

    fn_8009F4C4(0x10);
    temp_r3 = fn_801252BC();
    temp_r3->unk0x4 = arg1;
    *(f32 *)&temp_r3->unk0x8 = farg0;
    ((struct { u32 a : 9; u32 b : 7; u32 c : 16; } *)&temp_r3->unk0x0)->b = 2;
    fn_80127438(arg0, temp_r3);
}
