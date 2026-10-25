// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C2548-0x801C26D4 (396B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_800F0598(s32 arg0);
extern s32 fn_800F0670(void * arg0, s32 arg1);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void fn_8009F310(CStruct * arg0, Unk_15EF4A35 * arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void fn_801C2B04(Unk_C7387A53 * arg0, CStruct * arg1, Unk_FFAD6788 * arg2);
void fn_801C3020(Unk_C7387A53 * arg0, CStruct * arg1, Unk_FFAD6788 * arg2);
void SkaterGapComponent_end_gap(Unk_C7387A53 * arg0, CStruct * arg1, Unk_FFAD6788 * arg2);
void fn_801C366C(s32 arg0, s32 arg1);
void fn_801C36F8(Unk_C7387A53 * arg0, CStruct * arg1);
s32 fn_801C2548(Unk_C7387A53 *arg0, u32 arg1, CStruct *arg2, Unk_FFAD6788 *arg3) {
    s32 sp8;
    s32 temp_r27;
    s32 temp_r30;
    s32 var_r31;
    register s32 z __asm__("r26");

    switch (arg1) {
    case QB_STARTGAP:
        fn_801C2B04(arg0, arg2, arg3);
        break;
    case QB_STARTGAPTRICK:
        fn_801C3020(arg0, arg2, arg3);
        break;
    case QB_ENDGAP:
        SkaterGapComponent_end_gap(arg0, arg2, arg3);
        break;
    case QB_CHECKGAPTRICKS:
        fn_801C366C(arg0, arg2);
        break;
    case 0x196772B:
        fn_801C36F8(arg0, arg2);
        break;
    case QB_DUPLICATETRIGGER:
        temp_r30 = arg3->unk0xB8;
        if (temp_r30 != 0) {
            temp_r27 = fn_800F0598(temp_r30);
            var_r31 = 0;
            __asm__("li %0,0" : "=r"(z));
            for (; var_r31 < temp_r27; var_r31++) {
                if (GetChecksum_2(fn_800F0670(temp_r30, var_r31), (sp8 = z, QB_TRIGGERSCRIPT), &sp8, 0) != 0) {
                    fn_8009F310(arg0->unk0xC, sp8, arg3->unk0xB8, 0, 0, 0);
                    break;
                }
            }
        }
        break;
    default:
        return 2;
    }
    return 1;
}
