// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80026C44-0x80026CA0 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { u32 b:17; s32 f:8; u32 a:7; } F38;
s32 fn_8002D2A0(void *, s32);
s32 fn_8002D598(void *, void *, s32);
void fn_80026C44(char *arg0, s32 arg1) {
    F38 *p = (F38 *)(arg0 + 0x38);
    s32 n = p->f;
    if (n > 0) {
        n--;
        p->f = n;
        fn_8002D598((void *)fn_8002D2A0(arg0, arg1), arg0, arg1);
    }
}
