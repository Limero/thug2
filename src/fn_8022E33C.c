// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022E33C-0x8022E414 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8024078C(s32 arg0);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8022DD54(s32, s32, s32);
void fn_8022E33C(CStruct *arg0, CStruct *arg1, s32 arg2) {
    s32 cur;
    CStruct *prev;
    Unk_C8FEE62D *temp_r9;

    if ((arg1->unk0x4 & 4) != 0) {
        goto skip_list;
    }
    cur = arg0->unk0x8;
    prev = 0;
    goto loop_test;
loop_adv:
    prev = (CStruct *) cur;
    cur = prev->unk0x8;
loop_test:
    if (cur == 0) {
        goto skip_list;
    }
    if (cur != (s32) arg1) {
        goto loop_adv;
    }
    if (prev != 0) {
        prev->unk0x8 = arg1->unk0x8;
    } else {
        arg0->unk0x8 = arg1->unk0x8;
    }
skip_list:
    if (arg2 == 0) {
        fn_8022DD54(arg0, arg1->unk0x0, arg1->unk0x4);
        fn_8005572C();
    }
    fn_8024078C(arg1);
    if (arg1 != NULL) {
        temp_r9 = arg1->unk0xC;
        ((s32 (*)(void *, s32))temp_r9->unk0x14)((char *)arg1 + *(s16 *)((char *)temp_r9 + 0x10), 3);
    }
    if (arg0->unk0x8 == 0) {
        arg0->unk0x0 = (s32) (arg0->unk0x0 & QB_UNKNOWN_0xFFFFFFF7);
    }
}