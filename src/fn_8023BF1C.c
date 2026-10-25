// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023BF1C-0x8023BFB8 (156B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802B0DD4[];
s32 fn_80125A6C(void *, s32);

void fn_8023BF1C(Unk_57D689B7 *arg0) {
    char *p;
    char *q;
    s32 temp_r3;
    u8 v;
    u8 t3;

    temp_r3 = fn_80125A6C(lbl_802B0DD4, 1);
    arg0->unk0x352A = 1;
    p = (char *)arg0 + 0x352A;
    v = (0x38 - temp_r3) / 2 + 1;
    *(p + 1) = -4;
    *(p + 3) = 0x38;
    *(p + 5) = 0x38;
    *(p + 4) = 8;
    *(p + 2) = 1;
    arg0->unk0x3524 = v;
    q = (char *)arg0 + 0x3524;
    t3 = temp_r3;
    *(q + 3) = t3;
    *(q + 1) = -4;
    *(q + 2) = v;
    *(q + 4) = 8;
    *(q + 5) = t3;
}
