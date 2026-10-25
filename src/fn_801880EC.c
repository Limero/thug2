// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801880EC-0x80188190 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_801840F0(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_8018BFAC(Unk_C7387A53 * arg0);
extern s32 ContainsFlag(CStruct * arg0, u32 arg1);
extern void fn_80197B5C(void * arg0, CStruct * arg1);

void fn_801880EC(Unk_C7387A53 *arg0, CStruct *arg1) {
    CStruct *p;
    s32 count;
    s32 i;
    s32 obj;

    p = *((s32 * *)&arg0->unk0x2C);
    count = 0;
    goto check;
    do {
        p = *((s32 * *)&p->unk0xC);
        count += 1;
check:;
        if (p->unk0x4 == -1) {
            p = NULL;
        }
    } while (p != NULL);

    for (i = 0; i < count; i++) {
        obj = fn_801840F0(arg0, i);
        if (ContainsFlag(fn_8018BFAC((void *)obj), QB_TRICKBEAT) != 0) {
            fn_80197B5C(obj, arg1);
        }
    }
}
