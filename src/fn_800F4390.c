// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F4390-0x800F4450 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_800F38B8(void *);
s32 fn_800549E0(void *, void *, s32, s32, s32, s32, s32);
void fn_800F3A6C(void *);
void fn_80013788(s32);
void fn_800F3794(void *, void *, s32);
void fn_800F4390(Unk_C7387A53 *arg0, Unk_5D1D68CC *arg1, s32 arg2) {
    s32 zero = 0;
    void *r;
    void *vt1;
    void *vt2;
    s32 vres1;
    s32 vres549;
    CStruct *b;
    r = fn_800F38B8(arg0);
    vt1 = *(void **)((char *)r + 0x50);
    vres1 = ((s32 (*)(void *))*(void **)((char *)vt1 + 0x14))((char *)r + *(s16 *)((char *)vt1 + 0x10));
    b = (CStruct *)arg0->unk0x54;
    vres549 = fn_800549E0((char *)b + 0x14, arg1, vres1, b->unk0x4, b->unk0x8, b->unk0xC, b->unk0x10);
    vt2 = *(void **)((char *)arg0 + 0x50);
    ((s32 (*)(void *, s32))*(void **)((char *)vt2 + 0x5c))((char *)arg0 + *(s16 *)((char *)vt2 + 0x58), vres549);
    fn_800F3A6C((void *)arg0->unk0x54);
    arg0->unk0x54 = zero;
    if (arg0->unk0x20 != 0) {
        fn_80013788(arg0->unk0x20);
        arg0->unk0x20 = zero;
    }
    fn_800F3794(arg0, arg1, arg2);
}
