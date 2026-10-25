// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80203440-0x80203574 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void *Mem_Alloc2(s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80126F88(s32, Unk_80577C09 *);
void AddChecksum(s32, s32, s32);
s32 ContainsFlag(s32, s32);
void fn_80131960(s32, s32, s32);
s32 fn_8009F27C(s32, s32, s32, s32, s32);
void CStruct_delete(s32, s32);

s32 fn_80203440(Unk_31DE137E *arg0, Unk_80577C09 *arg1) {
    volatile s32 stk[2];
    CStruct *mem8;
    CStruct *memC;
    s32 tmp;
    s32 ctor2;
    Unk_9994C3F5 *list;
    CStruct *base;

    mem8 = Mem_Alloc2(8);
    base = (CStruct *)((char *)arg0 + 0x1C);
    mem8->unk0x0 = 0;
    tmp = CStruct_ctor(CStruct_new(8));
    mem8->unk0x0 = tmp;
    fn_80126F88(tmp, arg1);
    list = (Unk_9994C3F5 *)arg0->unk0x1C;
    mem8->unk0x4 = 0;
    stk[0] = (s32)list;
    memC = Mem_Alloc2(0xC);
    memC->unk0x8 = list->unk0x8;
    memC->unk0x4 = (s32)list;
    memC->unk0x0 = (s32)mem8;
    base->unk0x4 = base->unk0x4 + 1;
    list->unk0x8 = (s32)memC;
    ((CStruct *)memC->unk0x8)->unk0x4 = (s32)memC;
    ctor2 = CStruct_ctor(CStruct_new(8));
    AddChecksum(ctor2, QB_ADDED, 1);
    if (ContainsFlag(mem8->unk0x0, QB_PRIORITY_MESSAGE) != 0) {
        AddChecksum(ctor2, 0, QB_PRIORITY_MESSAGE);
    }
    fn_80131960(arg0->unk0xC, QB_PAGER_MESSAGE_LIST_CHANGED, 0);
    fn_8009F27C(arg0->unk0xC, QB_PAGER_MESSAGE_LIST_CHANGED, ctor2, 0, 0);
    if (ctor2 != 0) {
        CStruct_delete(ctor2, 3);
    }
    return 1;
}
