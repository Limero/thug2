// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E914-0x8003E9B8 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802921F4[];
extern char lbl_80292200[];
void Mem_Free_3(s32 arg0);
s32 fn_80012E88(s32, s32, s32, s32);
void fn_8003E914(CStruct *arg0, s32 arg1, s32 arg2) {
    char sp8[0x200];
    s32 sp208;
    s32 temp_r3;

    if (arg2 != 0) {
        sprintf(sp8, (s32) lbl_802921F4, arg1);
    } else {
        sprintf(sp8, (s32) lbl_80292200, arg1);
    }
    temp_r3 = fn_80012E88((s32) sp8, (s32) &sp208, 0, 0);
    memcpy((char *) arg0 + 0x40, temp_r3, sp208);
    Mem_Free_3(temp_r3);
    arg0->unk0x4 = 1;
}
