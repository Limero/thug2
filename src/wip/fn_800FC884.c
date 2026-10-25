// WIP draft - PARKED. See notes below.
// family=m2c range=0x800FC884-0x800FCA10 size=396B
// PARKED: Paired-single PS interleaving + framed struct-copy
// WANT uses 4 paired-single loads/stores (psq_l/psq_st) interleaved with integer
// field loads in a specific scheduler order. See file header for full analysis.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
// FLAG: -mps-float -Os
extern void *Mem_Alloc2(s32);
extern void *Mem_NewZero(s32);
extern char lbl_8029C7B0[];
extern char lbl_8029C1F8[];
extern char lbl_8029C210[];
void *fn_800FC884(Unk_6AC87105 *arg0, s32 arg1) {
    Unk_6AC87105 *new1;
    Unk_C8FEE62D *new2;
    Unk_C8FEE62D *new3;
    CStruct *head;
    Unk_C7387A53 *head_next;
    CStruct *var_r31;
    CStruct *var_r9;
    CStruct *tmp11;
    Unk_C7387A53 *tmp11b;
    Unk_2C7D9FAD *r9;
    s32 var_r0;
    s32 tmp;
    s16 tmp16;
    new1 = Mem_Alloc2(0x48);
    {
        __ps_t *src = (__ps_t *)((char *)arg0 + 0x18);
        __ps_t *dst = (__ps_t *)((char *)new1 + 0x18);
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
    }
    tmp16 = *((s16 *)&arg0->unk0x4);
    *((s16 *)&new1->unk0x4) = tmp16 | (s16)0x8000;
    new1->unk0x0 = arg0->unk0x0;
    new1->unk0x6 = arg0->unk0x6;
    new1->unk0x8 = arg0->unk0x8;
    new1->unk0x10 = arg0->unk0x10;
    new1->unk0x38 = arg0->unk0x38;
    new1->unk0xC = (s32)lbl_8029C7B0;
    new1->unk0x3C = arg0->unk0x3C;
    new1->unk0x40 = arg0->unk0x40;
    new2 = Mem_NewZero(0x18);
    new2->unk0x4 = -1;
    new2->unk0x8 = 0;
    new2->unk0x14 = (s32)lbl_8029C1F8;
    new2->unk0xC = (s32)new2;
    new2->unk0x10 = (s32)new2;
    new1->unk0x10 = (s32)new2;
    tmp11 = *(void **)((char *)*((void * *)&arg0->unk0x10) + 0xC);
    var_r31 = tmp11;
    if (tmp11->unk0x4 == -1) var_r31 = 0;
    if (var_r31 != 0) {
        do {
            tmp11b = *((void * *)&var_r31->unk0x4);
            new3 = Mem_NewZero(0x18);
            r9 = *((void * *)&tmp11b->unk0xC);
            tmp = ((s32 (*)(void *, s32))*((void * *)&r9->unk0x6C))((char *)tmp11b + r9->unk0x68, arg1);
            new3->unk0xC = (s32)new3;
            new3->unk0x10 = (s32)new3;
            new3->unk0x4 = tmp;
            new3->unk0x14 = (s32)lbl_8029C210;
            new3->unk0x8 = 0;
            head = *((void * *)&new1->unk0x10);
            head_next = *((void * *)&head->unk0x10);
            new3->unk0xC = (s32)head;
            new3->unk0x10 = (s32)head_next;
            head_next->unk0xC = (s32)new3;
            head->unk0x10 = (s32)new3;
            var_r9 = *((void * *)&var_r31->unk0xC);
            var_r0 = var_r9->unk0x4;
            var_r31 = var_r9;
            if (var_r0 == -1) var_r31 = 0;
        } while (var_r31 != 0);
    }
    return new1;
}
