// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024E1F0-0x8024E2C8 (216B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8024D61C(Unk_C7387A53 * tbl, s32 sh);

void fn_8024E1F0(CStruct *arg0, CStruct *arg1, CStruct *arg2) {
    Unk_0C4A6AB9 *t;
    s32 v;
    s32 adj;

    t = *((char * *)&arg0->unk0xC);
    arg1->unk0x0 = fn_8024D61C((s32)t + 0x48, t->unk0x50);
    t = *((char * *)&arg0->unk0xC);
    arg1->unk0x4 = fn_8024D61C((s32)t + 0x48, t->unk0x50);
    v = arg1->unk0x0 + arg2->unk0x0;
    arg1->unk0x0 = v;
    arg1->unk0x4 = arg1->unk0x4 + arg2->unk0x4;
    if (v < arg0->unk0x4) {
        adj = v + arg0->unk0x8;
        goto st0;
    }
    if (v > arg0->unk0x0) {
        adj = v - arg0->unk0x8;
    st0:
        arg1->unk0x0 = adj;
    }
    v = *((volatile s32 *)&arg1->unk0x4);
    if (v < arg0->unk0x4) {
        adj = v + arg0->unk0x8;
        goto st1;
    }
    if (v > arg0->unk0x0) {
        adj = v - arg0->unk0x8;
    st1:
        arg1->unk0x4 = adj;
    }
}
