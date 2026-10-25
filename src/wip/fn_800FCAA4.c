// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-O1` -> 5.71% to 15.28%.
// family=m2c range=0x800FCAA4-0x800FCBB8 size=276B
// WIP draft - PARKED. See notes below.
// extra_cflags: -mps-float -O1
// range=0x800FCAA4-0x800FCBB8 size=276 B
// PARKED: -mps-float pair-copy construction idiom. WANT builds two 8B stack
// temps (r1+8..F, r1+0x10..0x17) member-wise via stfs (lfs f0=10M, lfs f13=1.0
// held in callee-saved f13 across the section), then copies them to obj fields
// 0x18/0x20/0x28/0x30 as psq_l+psq_st pairs ({A,A}->o18, {A,B}->o20, {C,B}->o30,
// {C,C}->o28; A=lbl_8029C154=1e7, B=lbl_8029C158=1.0, C=lbl_8029C15C=-1e7;
// note the F0-words are psq_st PAIR stores, not stfs). lwz r11,0x10(r29)
// (list load for the loop below) is interleaved mid-float-section.
// Best attempt (~struct S2 locals + __ps_t-cast pair copies + -mps-float)
// reproduces psq_l/psq_st but GCC materializes addi rX,r1,N address regs and
// int-forwards one copy through lwz/stw; no shape tried (union .ps/.flt,
// f32[2], whole-struct assign, __builtin_psq_l intrinsic, volatile, schedule
// flags) yields all-direct r1 displacements. Same wall class as parking doc
// 06 item 2 ("game fuses pair-load+single-lane store", fn_800CD7CC/CD83C at
// 85.7%) and plan-snaps-doc06 finding 3 (game spills PS products to stack,
// 3.9.3 keeps regs). Loop half (sentinel walk + or.-tested vcall @0xAC +
// s16@0xA8 + two fn_8000728C min4 calls with r28=o+0x18 recomputed in-body)
// is understood; only the float prologue blocks. Retry after a compiler or
// post-link breakthrough.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029C154;
extern f32 lbl_8029C158;
extern f32 lbl_8029C15C;
void fn_8000728C(Unk_DB0E2BAB *, CStruct *);
void fn_800FCAA4(void *arg0) {
    struct S2 { f32 hi, lo; } p1;
    struct S2 p2;
    Unk_C7387A53 *list;
    CStruct *elem;
    CStruct *chk;
    s32 ret;
    char *o = (char *)arg0;

    ((Unk_DB12A69C *)o)->unk0x3C = 1;
    p2.hi = lbl_8029C154;
    p1.hi = lbl_8029C154;
    p1.lo = lbl_8029C154;
    ((Unk_DB12A69C *)o)->unk0x18 = *(__ps_t *)&p1;
    p2.lo = lbl_8029C158;
    ((Unk_DB12A69C *)o)->unk0x20 = *(__ps_t *)&p2;
    list = ((Unk_DB12A69C *)o)->unk0x10;
    p2.lo = lbl_8029C158;
    p1.hi = lbl_8029C15C;
    p1.lo = lbl_8029C15C;
    p2.hi = lbl_8029C15C;
    ((Unk_DB12A69C *)o)->unk0x30 = *(__ps_t *)&p2;
    ((Unk_DB12A69C *)o)->unk0x28 = *(__ps_t *)&p1;

    elem = list;
    chk = *((void * *)&list->unk0xC);
    if (chk->unk0x4 == -1) {
        elem = NULL;
    }
    if (elem != NULL) {
        do {
            void *node;
            void *vt;
            s16 off;
            node = *((void * *)&elem->unk0x4);
            vt = *((void * *)&((Unk_C7387A53 *)node)->unk0xC);
            off = ((Unk_5BE2D2B7 *)vt)->unk0xA8;
            ret = ((s32 (*)(void *))(*((void * *)&((Unk_5BE2D2B7 *)vt)->unk0xAC)))((char *)node + off);
            if (ret == 0) {
                ((Unk_DB12A69C *)o)->unk0x3C = ret;
                return;
            }
            fn_8000728C(o + 0x18, (char *)ret);
            fn_8000728C(o + 0x18, (char *)ret + 0x10);
            chk = *((void * *)&elem->unk0xC);
            elem = chk;
            if (chk->unk0x4 == -1) {
                elem = NULL;
            }
        } while (elem != NULL);
    }
}
