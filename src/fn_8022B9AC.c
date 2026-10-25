// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022B9AC-0x8022BA54 (168B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802B0020[];
extern char lbl_802B0060[];
extern char lbl_802B0410[];

void fn_8022B8E8(void *);

void fn_8022B9AC(Unk_C8FEE62D *arg0, s32 arg1) {
    Unk_2307D821 *sub;
    void *t1;
    Unk_C7387A53 *t2;
    CStruct *t3;
    void *t4;
    void *t5;
    Unk_C7387A53 *t6;
    void *t7;
    CStruct *t8;

    arg0->unk0x14 = (s32)lbl_802B0410;
    fn_8022B8E8(arg0);

    sub = (char *)arg0 + 0xAC;
    t1 = sub->unk0xC;
    t2 = sub->unk0x10;
    ((Unk_1D62F22E_2 *)sub)->unk0x14 = (s32)lbl_802B0060;
    t2->unk0xC = (s32)t1;
    t3 = sub->unk0xC;
    t4 = sub->unk0x10;
    t3->unk0x10 = (s32)t4;
    ((Unk_1D62F22E_2 *)sub)->unk0xC = (s32)sub;
    ((Unk_1D62F22E_2 *)sub)->unk0x10 = (s32)sub;

    arg0->unk0x14 = (s32)lbl_802B0020;
    t6 = *((void * *)&arg0->unk0x10);
    t5 = *((void * *)&arg0->unk0xC);
    t6->unk0xC = (s32)t5;
    t8 = *((void * *)&arg0->unk0xC);
    t7 = *((void * *)&arg0->unk0x10);
    t8->unk0x10 = (s32)t7;
    arg0->unk0xC = (s32)arg0;
    arg0->unk0x10 = (s32)arg0;

    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
