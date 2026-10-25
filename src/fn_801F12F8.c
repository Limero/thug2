// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F12F8-0x801F1340 (72B). Byte-identical.
#include "types.h"
s32 fn_801F125C(s32);
typedef struct { char pad[0x190]; s32 arr[1]; } S;
void fn_801F12F8(S *arg0, s32 arg1) {
    s32 temp_r3;
    temp_r3 = fn_801F125C(arg1);
    if (temp_r3 != -1) {
        arg0->arr[temp_r3] = 1;
    }
}
