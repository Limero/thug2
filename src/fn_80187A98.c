// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80187A98-0x80187B0C (116B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80184168(Unk_9994C3F5 * arg0);
extern void *fn_8018B4C0(Unk_C8FEE62D * arg0, s32 *arg1, s32 *arg2);
extern void fn_80191E8C(s32 * arg0, s32 arg1);

void fn_80187A98(s32 arg0, s32 arg1) {
    s32 spC;
    s32 sp8 = 0;

    while (sp8 < fn_80184168((void *)arg0)) {
        fn_80191E8C(*(s32 *)((char *)fn_8018B4C0(arg0 + 4, &sp8, &spC) + 0x18), arg1);
        sp8++;
    }
}
