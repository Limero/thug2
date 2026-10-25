// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80187B84-0x80187C14 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_80184168(Unk_9994C3F5 * arg0);
extern void *fn_8018B4C0(Unk_C8FEE62D * arg0, s32 *arg1, s32 *arg2);
extern s32 fn_8018BFAC(Unk_C7387A53 * arg0);
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern void fn_80195E0C(Unk_C8FEE62D * arg0, s32 arg1);

void fn_80187B84(s32 arg0, s32 arg1) {
    s32 spC;
    s32 sp8;
    s32 count;
    void *obj;

    count = fn_80184168((void *)arg0);
    sp8 = 0;
    while (sp8 < count) {
        obj = fn_8018B4C0(arg0 + 4, &sp8, &spC);
        if (ContainsFlag(fn_8018BFAC(obj), QB_TRICKOBJECTS) != 0) {
            fn_80195E0C(obj, arg1);
        }
        sp8++;
    }
}
