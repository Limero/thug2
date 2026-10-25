// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F551C-0x800F55D8 (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_800F3A1C(s32);
extern void fn_800F5788(Unk_DB0E2BAB *);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 ContainsFlag(CStruct *, s32);
void fn_800F551C(Unk_C7387A53 *arg0, Unk_DB0E2BAB *arg1, CStruct *arg2) {
    register s32 temp_r0 __asm__("r0");
    register s32 temp_r11 __asm__("r11");
    Unk_DB0E2BAB *temp_r9;
    s32 temp_r10;
    s32 temp_r8;

    arg0->unk0x58 = fn_800F3A1C(0x18);
    fn_800F5788(*((void * *)&arg0->unk0x58));
    if (arg1 != NULL) {
        temp_r0 = arg1->unk0x0;
        temp_r11 = arg1->unk0x4;
        temp_r9 = arg0->unk0x58;
        temp_r10 = arg1->unk0x8;
        temp_r8 = arg1->unk0xC;
        temp_r9->unk0x0 = temp_r0;
        temp_r9->unk0x4 = temp_r11;
        temp_r9->unk0x8 = temp_r10;
        temp_r9->unk0xC = temp_r8;
        {
            register s32 temp_r0_2 __asm__("r0");
            register s32 temp_r11_2 __asm__("r11");

            temp_r11_2 = arg1->unk0x10;
            temp_r0_2 = arg1->unk0x14;
            temp_r9->unk0x14 = temp_r0_2;
            temp_r9->unk0x10 = temp_r11_2;
        }
    }
    if (arg2 != 0) {
        GetInteger(arg2, QB_TEX_DICT_OFFSET, arg0->unk0x58 + 4, 0);
        *(s32 *)(arg0->unk0x58) = ContainsFlag(arg2, QB_DO_SHADOW_VOLUME);
    }
}
