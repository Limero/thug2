// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184248-0x801842C0 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 fn_80184168(void *arg0);
extern void *fn_8018B4C0(void *arg0, s32 *arg1, s32 *arg2);
extern s32 fn_8018E3B8(void *arg0);

s32 fn_80184248(void *arg0) {
    s32 cnt = 0;
    s32 i = 0;
    s32 spC;

    while (i < fn_80184168(arg0)) {
        if (fn_8018E3B8(fn_8018B4C0((char *) arg0 + 4, &i, &spC)) != 0) {
            cnt++;
        }
        i++;
    }
    return cnt;
}
