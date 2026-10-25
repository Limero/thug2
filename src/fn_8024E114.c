// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024E114-0x8024E1F0 (220B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8024D61C(Unk_C7387A53 * tbl, s32 sh);

void fn_8024E114(Unk_C7387A53 *arg0, CStruct *arg1, s32 arg2, Unk_EA529D06 *arg3) {
    char *t;
    s32 v;
    s32 mn;
    s32 mx;
    s32 spn;
    s32 x;
    s32 y;
    s32 adj;

    *((s64 *)&arg1->unk0x0) = *((s64 *)&arg3->unk0x0);
    v = 1 << (arg2 - 1);
    mn = v * -0x20;
    spn = v << 6;
    mx = (v << 5) - 1;
    t = *((char * *)&arg0->unk0xC);
    arg1->unk0x0 += fn_8024D61C((s32)t + 0x48, arg2);
    t = *((char * *)&arg0->unk0xC);
    arg1->unk0x4 += fn_8024D61C((s32)t + 0x48, arg2);
    x = arg1->unk0x0;
    if (x < mn) {
        adj = x + spn;
        goto st0;
    }
    if (x > mx) {
        adj = x - spn;
    st0:
        arg1->unk0x0 = adj;
    }
    y = arg1->unk0x4;
    if (y < mn) {
        adj = y + spn;
        goto st1;
    }
    if (y > mx) {
        adj = y - spn;
    st1:
        arg1->unk0x4 = adj;
    }
}
