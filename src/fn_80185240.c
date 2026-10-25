// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185240-0x80185380 (320B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802A94B0[];
extern s32 fn_80184168(Unk_9994C3F5 * arg0);
extern void *fn_8018B4C0(Unk_C8FEE62D * arg0, s32 *arg1, s32 *arg2);
extern s32 fn_8018EC90(Unk_C7387A53 * arg0);
extern s32 fn_8018BFAC(Unk_C7387A53 * arg0);
extern s32 fn_8018DE04(Unk_C7387A53 * arg0);
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern s32 fn_80128A90(CStruct * arg0, void * arg1);
extern s32 fn_8018DE30(void *arg0);
extern s32 fn_8018E24C(Unk_C7387A53 * arg0);
extern s32 fn_80183D68(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_8018DFB4(Unk_C7387A53 * arg0);
extern s32 fn_8019457C(Unk_C7387A53 * arg0);
extern s32 fn_80190700(Unk_C7387A53 * arg0);
extern s32 fn_80195668(Unk_C7387A53 * arg0);

void fn_80185240(s32 arg0) {
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    Unk_C8FEE62D *temp_r3;
    Unk_89391A04 *temp_r9;

    sp8 = 0;
    while (sp8 < fn_80184168((void *)arg0)) {
        temp_r3 = fn_8018B4C0((void *)(arg0 + 4), &sp8, &spC);
        temp_r9 = *((void * *)&temp_r3->unk0x14);
        if ((temp_r9->unk0x24((char *)temp_r3 + temp_r9->unk0x20) != 0) &&
            (fn_8018EC90(temp_r3) == 0)) {
            temp_r30 = fn_8018BFAC(temp_r3);
            if ((fn_8018DE04(temp_r3) != 0) || (ContainsFlag((void *)temp_r30, QB_CREATE_A_TRICK) != 0)) {
                if ((fn_80128A90((void *)temp_r30, (s32)lbl_802A94B0) == 0) && (fn_8018DE30(temp_r3) != 0)) {
                    fn_80183D68(arg0, fn_8018E24C(temp_r3));
                }
            } else if (fn_8018DFB4(temp_r3) != 0) {
                fn_8019457C(temp_r3);
            } else if (fn_80190700(temp_r3) != 0) {
                fn_80195668(temp_r3);
            }
        }
        sp8 += 1;
    }
}
