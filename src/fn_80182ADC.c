// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182ADC-0x80182B5C (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801403CC(void *);
extern u8 fn_8021F6CC(Unk_2EC243AC *);
void fn_801815EC(Unk_667BA59C *, s32, s32, s32, s32 *, s32);
extern void* lbl_80305F9C;

bool fn_80182ADC(CScript *arg0) {
    register void *temp_r30 __asm__("r30");
    s32 temp_r29;

    temp_r30 = *(void **)arg0;
    temp_r29 = fn_801403CC(arg0->unk0x18);
    if (*(u8 *)temp_r30 == 1) {
        temp_r30 = *(void **)arg0;
        if (((Unk_C71E6DE1 *)temp_r30)->unk0x1 == fn_8021F6CC(lbl_80305F9C)) {
            fn_801815EC(temp_r29, ((Unk_C71E6DE1 *)temp_r30)->unk0x4, ((Unk_C71E6DE1 *)temp_r30)->unk0x8, ((Unk_C71E6DE1 *)temp_r30)->unk0xC, (s32)((char *)temp_r30 + 0x10), 0);
        }
    }
    return true;
}
