// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5A9C-0x801A5C04 (360B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-sched-spec -fno-gcse
#include "types.h"
#include "structs.h"
void Mem_Free(void *);
void CStruct_delete(CStruct *, s32);
void fn_8003A7A4(CStruct *, s32);
s32 fn_801A65EC(Unk_C8FEE62D *, s32 *, s32 *);
void fn_801A6694(CStruct *, s32 *);
void fn_801A65AC(CStruct *, s32);
void fn_801A5A9C(Unk_C7387A53 *arg0, s32 arg1) {
    s32 spC;
    s32 sp8;
    s32 t;
    u32 i;
    u32 count;
    CStruct *base;
    CStruct *endbase;
    char *p;
    s32 zero2;
    s32 off;
    s32 cnt2;
    s32 i3;
    s32 zero3;
    char *w;
    s32 count3;

    i = 0U;
    base = (CStruct *)((char *)arg0 + 4);
    count = (u32)base->unk0x4;
    if (i < count) {
        CStruct *list = base;
        do {
            sp8 = 0;
            t = fn_801A65EC((Unk_C8FEE62D *)list, &sp8, &spC);
            if (t != 0) {
                CStruct_delete((CStruct *)((char *)t + 0x6C), 2);
                fn_8003A7A4((CStruct *)((char *)t + 4), 2);
                Mem_Free((void *)t);
            }
            fn_801A6694(list, &spC);
            i++;
        } while (i < count);
    }
    endbase = (CStruct *)((char *)arg0 + 4);
    p = (char *)arg0 + 0x1C;
    zero2 = 0;
    off = 4;
    cnt2 = 1;
    do {
        t = *(s32 *)((char *)off + (s32)p);
        if (t != 0) {
            CStruct_delete((CStruct *)((char *)t + 0x6C), 2);
            fn_8003A7A4((CStruct *)((char *)t + 4), 2);
            Mem_Free((void *)t);
        }
        *(s32 *)((char *)off + (s32)p) = zero2;
        cnt2--;
        off += 4;
    } while (cnt2 != 0);
    i3 = 0;
    count3 = arg0->unk0x2C;
    if (i3 < count3) {
        zero3 = 0;
        w = (char *)arg0 + 0x3C;
        do {
            t = *(s32 *)w;
            if (t != 0) {
                CStruct_delete((CStruct *)((char *)t + 0x6C), 2);
                fn_8003A7A4((CStruct *)((char *)t + 4), 2);
                Mem_Free((void *)t);
            }
            *(s32 *)w = zero3;
            i3++;
            w += 4;
            count3 = arg0->unk0x2C;
        } while (i3 < count3);
    }
    fn_801A65AC(endbase, 2);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
